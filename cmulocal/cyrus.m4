dnl
dnl Additional macros for configure.in packaged up for easier theft.
dnl $Id: cyrus.m4,v 1.4 2003/10/08 20:35:24 rjs3 Exp $
dnl tjs@andrew.cmu.edu 6-may-1998
dnl
dnl Debian fix (hmh@debian.org): We don't want runpath set in Debian

dnl It would be good if ANDREW_ADD_LIBPATH could detect if something was
dnl already there and not redundantly add it if it is.

dnl add -L(arg), and possibly (runpath switch)(arg), to LDFLAGS
dnl (so the runpath for shared libraries is set).
AC_DEFUN([CMU_ADD_LIBPATH], [
  # this is CMU ADD LIBPATH
  if test "$andrew_runpath_switch" = "none" ; then
	LDFLAGS="-L$1 ${LDFLAGS}"
  else
	LDFLAGS="-L$1 $andrew_runpath_switch$1 ${LDFLAGS}"
  fi
])

dnl add -L(1st arg), and possibly (runpath switch)(1st arg), to (2nd arg)
dnl (so the runpath for shared libraries is set).
AC_DEFUN([CMU_ADD_LIBPATH_TO], [
  # this is CMU ADD LIBPATH TO
  if test "$andrew_runpath_switch" = "none" ; then
	$2="-L$1 ${$2}"
  else
	$2="-L$1 ${$2} $andrew_runpath_switch$1"
  fi
])

dnl runpath initialization
dnl (disabled by hmh@debian.org
AC_DEFUN([CMU_GUESS_RUNPATH_SWITCH], [
   # CMU GUESS RUNPATH SWITCH
    andrew_runpath_switch="none"
])
