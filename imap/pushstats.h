
/* pushstats.h -- statistics push interface

 * generated automatically from /home/ellie/fastmail/cyrus-imapd/imap/pushstats.snmp by snmpgen

 *

 * Copyright 2000 Carnegie Mellon University

 *

 * No warranty, yadda yadda

 */



#ifndef pushstats_H

#define pushstats_H



#define SNMPDEFINE_cmuimap "1.3.6.1.4.1.3.2.2.3.1"
#define SNMPDEFINE_cmutree "1.3.6.1.4.1.3.2.2.3"



#ifndef USING_SNMPGEN



#define snmp_connect()

#define snmp_close()

#define snmp_increment(a, b)

#define snmp_increment_args(a, b, c, d, e)

#define snmp_set(a, b)

#define snmp_set_str(a, b)

#define snmp_set_oid(a, b)

#define snmp_set_time(a, b)

#define snmp_getdescription(a)

#define snmp_getoid(a, b, c, d)

#define snmp_setvariable(a, b)



typedef void pushstats_t;



#else



typedef enum {

    SEARCH_COUNT,
    STATUS_COUNT,
    UNSUBSCRIBE_COUNT,
    AUTHENTICATE_COUNT,
    ACTIVE_CONNECTIONS,
    SORT_COUNT,
    DELETEACL_COUNT,
    SERVER_UPTIME,
    AUTHENTICATION_YES,
    SERVER_NAME_VERSION,
    SETQUOTA_COUNT,
    PARTIAL_COUNT,
    STARTTLS_COUNT,
    CREATE_COUNT,
    COPY_COUNT,
    UNSELECT_COUNT,
    LIST_COUNT,
    FETCH_COUNT,
    ID_COUNT,
    EXAMINE_COUNT,
    APPEND_COUNT,
    SETACL_COUNT,
    CLOSE_COUNT,
    MYRIGHTS_COUNT,
    SUBSCRIBE_COUNT,
    LISTRIGHTS_COUNT,
    CHECK_COUNT,
    RENAME_COUNT,
    GETQUOTAROOT_COUNT,
    SCAN_COUNT,
    COMPRESS_COUNT,
    STORE_COUNT,
    NOOP_COUNT,
    NAMESPACE_COUNT,
    GETANNOTATION_COUNT,
    SELECT_COUNT,
    GETQUOTA_COUNT,
    GETACL_COUNT,
    TOTAL_CONNECTIONS,
    LOGOUT_COUNT,
    CAPABILITY_COUNT,
    AUTHENTICATION_NO,
    IDLE_COUNT,
    EXPUNGE_COUNT,
    BBOARD_COUNT,
    LSUB_COUNT,
    GETUIDS_COUNT,
    DELETE_COUNT,
    SETANNOTATION_COUNT,
    LOGIN_COUNT,
    THREAD_COUNT,
    FIND_COUNT
} pushstats_t;



typedef enum {

    VARIABLE_LISTEND,
    VARIABLE_AUTH


} pushstats_variable_t;



int snmp_connect(void);



int snmp_close(void);



/* only valid on counters */

int snmp_increment(pushstats_t cmd, int);

int snmp_increment_args(pushstats_t cmd, int incr, ...);



/* only valid on values */

int snmp_set(pushstats_t cmd, int);



int snmp_set_str(pushstats_t cmd, char *value);



int snmp_set_oid(pushstats_t cmd, char *str);



int snmp_set_time(pushstats_t cmd, time_t t);



const char *snmp_getdescription(pushstats_t cmd);



const char *snmp_getoid(const char *name, pushstats_t cmd, char* buf, int buflen);



void snmp_setvariable(pushstats_variable_t, int);



#endif /* USING_SNMPGEN */



#endif /* pushstats_H */



