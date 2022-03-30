/* lock_fcntl.c -- Lock files using fcntl()
 $Id: lock_fcntl.c,v 1.16 2003/02/13 20:15:40 rjs3 Exp $
 
 * Copyright (c) 1998-2003 Carnegie Mellon University.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer. 
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. The name "Carnegie Mellon University" must not be used to
 *    endorse or promote products derived from this software without
 *    prior written permission. For permission or any other legal
 *    details, please contact  
 *      Office of Technology Transfer
 *      Carnegie Mellon University
 *      5000 Forbes Avenue
 *      Pittsburgh, PA  15213-3890
 *      (412) 268-4387, fax: (412) 268-7395
 *      tech-transfer@andrew.cmu.edu
 *
 * 4. Redistributions of any form whatsoever must retain the following
 *    acknowledgment:
 *    "This product includes software developed by Computing Services
 *     at Carnegie Mellon University (http://www.cmu.edu/computing/)."
 *
 * CARNEGIE MELLON UNIVERSITY DISCLAIMS ALL WARRANTIES WITH REGARD TO
 * THIS SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS, IN NO EVENT SHALL CARNEGIE MELLON UNIVERSITY BE LIABLE
 * FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN
 * AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING
 * OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 *
 */
#include <config.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <syslog.h>
#include <signal.h>

#include "lock.h"

const char *lock_method_desc = "fcntl";

int lock_wait_time = LOCK_GIVEUP_TIMER_DEFAULT;

/* Signal handling. We REQUIRE SYSV abort-syscall behaviour */

static volatile int lock_gotsigalrm = 0;
void lock_sigalrm_handler(int sig __attribute__((unused)))
{
    lock_gotsigalrm = 1;
}

static int setsigalrm(int enable)
{
    struct sigaction action;

    sigemptyset(&action.sa_mask);
    action.sa_flags = SA_RESETHAND;

    if(enable) {
	action.sa_handler = lock_sigalrm_handler;
    } else {
	action.sa_handler = SIG_IGN;
    }
    if (sigaction(SIGALRM, &action, NULL) < 0) {
	syslog(LOG_ERR, "installing SIGALRM handler: sigaction: %m");
	return -1;
    }
    lock_gotsigalrm = 0;
    return 0;
}

/*
 * Block until we obtain an exclusive lock on the file descriptor 'fd',
 * opened for reading and writing on the file named 'filename'.  If
 * 'filename' is replaced, will re-open it as 'fd' and acquire a lock
 * on the new file.
 *
 * On success, returns 0.  If a pointer to a struct stat is given as
 * 'sbuf', it is filled in.
 *
 * On failure, returns -1 with an error code in errno.  If
 * 'failaction' is provided, it is filled in with a pointer to a fixed
 * string naming the action that failed.
 *
 * We use POSIX semanthics and alarm() to avoid deadlocks
 *
 */
int lock_reopen (int fd, const char *filename, struct stat *sbuf, const char **failaction)
{
    int r;
    struct flock fl;
    struct stat sbuffile, sbufspare;
    int newfd;

    if (!sbuf) sbuf = &sbufspare;

    setsigalrm(1);
    alarm(lock_wait_time);
    for (;;) {
	fl.l_type= F_WRLCK;
	fl.l_whence = SEEK_SET;
	fl.l_start = 0;
	fl.l_len = 0;
	r = fcntl(fd, F_SETLKW, &fl);
	if (r == -1) {
	    if (errno == EINTR && !lock_gotsigalrm) continue;
 	    if (failaction) *failaction = "locking";
	    alarm(0);
	    setsigalrm(0);
	    return -1;
	}

	fstat(fd, sbuf);
	r = stat(filename, &sbuffile);
	if (r == -1) {
	    if (failaction) *failaction = "stating";
	    fl.l_type= F_UNLCK;
	    fl.l_whence = SEEK_SET;
	    fl.l_start = 0;
	    fl.l_len = 0;
	    r = fcntl(fd, F_SETLKW, &fl);
	    alarm(0);
	    setsigalrm(0);
	    return -1;
	}

	if (sbuf->st_ino == sbuffile.st_ino) {
	    alarm(0);
	    setsigalrm(0);
	    return 0;
	}

	newfd = open(filename, O_RDWR);
	if (newfd == -1) {
	    if (failaction) *failaction = "opening";
	    fl.l_type= F_UNLCK;
	    fl.l_whence = SEEK_SET;
	    fl.l_start = 0;
	    fl.l_len = 0;
	    r = fcntl(fd, F_SETLKW, &fl);
	    alarm(0);
	    setsigalrm(0);
	    return -1;
	}
	dup2(newfd, fd);
	close(newfd);
    }
    alarm(0);
    setsigalrm(0);
}

/*
 * Obtain an exclusive lock on 'fd'.
 * Returns 0 for success, -1 for failure, with errno set to an
 * appropriate error code.
 */
int lock_blocking(int fd)
{
    int r;
    struct flock fl;

    setsigalrm(1);
    alarm(lock_wait_time);
    for (;;) {
	fl.l_type= F_WRLCK;
	fl.l_whence = SEEK_SET;
	fl.l_start = 0;
	fl.l_len = 0;
	r = fcntl(fd, F_SETLKW, &fl);
	if (r != -1) {
	    alarm(0);
	    setsigalrm(0);
	    return 0;
	}
	if (errno == EINTR && !lock_gotsigalrm) continue;
	alarm(0);
	setsigalrm(0);
	return -1;
    }
    alarm(0);
    setsigalrm(0);
    return 0;
}

/*
 * Obtain a shared lock on 'fd'.
 * Returns 0 for success, -1 for failure, with errno set to an
 * appropriate error code.
 */
int lock_shared(int fd)
{
    int r;
    struct flock fl;

    setsigalrm(1);
    alarm(lock_wait_time);
    for (;;) {
	fl.l_type= F_RDLCK;
	fl.l_whence = SEEK_SET;
	fl.l_start = 0;
	fl.l_len = 0;
	r = fcntl(fd, F_SETLKW, &fl);
	if (r != -1) {
	    alarm(0);
	    setsigalrm(0);
	    return 0;
	}
	if (errno == EINTR && !lock_gotsigalrm) continue;
	alarm(0);
	setsigalrm(0);
	return -1;
    }
    alarm(0);
    setsigalrm(0);
    return 0;
}

/*
 * Attempt to get an exclusive lock on 'fd' without blocking.
 * Returns 0 for success, -1 for failure, with errno set to an
 * appropriate error code.
 */
int lock_nonblocking(int fd)
{
    int r;
    struct flock fl;

    for (;;) {
	fl.l_type= F_WRLCK;
	fl.l_whence = SEEK_SET;
	fl.l_start = 0;
	fl.l_len = 0;
	r = fcntl(fd, F_SETLK, &fl);
	if (r != -1) return 0;
	if (errno == EINTR) continue;
	return -1;
    }
    return 0;
}

/*
 * Release any lock on 'fd'
 * Returns 0 for success, -1 for failure, with errno set to an
 * appropriate error code.
 */
int lock_unlock(int fd)
{ 
    struct flock fl;
    int r;

    fl.l_type= F_UNLCK;
    fl.l_whence = SEEK_SET;
    fl.l_start = 0;
    fl.l_len = 0;

    for (;;) {
        r = fcntl(fd, F_SETLKW, &fl);
        if (r != -1) return 0;
        if (errno == EINTR) continue;
        /* xxx help! */
        return -1;
    }
    return 0;
}

