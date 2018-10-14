
/* pushstats.h -- statistics push interface

 * generated automatically from .././imap/pushstats.snmp by snmpgen

 *

 * Copyright 2000 Carnegie Mellon University

 *

 * No warranty, yadda yadda

 */                                       

                                          

#ifndef pushstats_H    

#define pushstats_H



#define SNMPDEFINE_cmutree "1.3.6.1.4.1.3.2.2.3"
#define SNMPDEFINE_cmuimap "1.3.6.1.4.1.3.2.2.3.1"



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

    FETCH_COUNT,
    LIST_COUNT,
    DELETE_COUNT,
    ID_COUNT,
    EXAMINE_COUNT,
    IDLE_COUNT,
    CREATE_COUNT,
    STORE_COUNT,
    TOTAL_CONNECTIONS,
    SERVER_UPTIME,
    SERVER_NAME_VERSION,
    SETQUOTA_COUNT,
    THREAD_COUNT,
    SCAN_COUNT,
    SETANNOTATION_COUNT,
    DELETEACL_COUNT,
    SELECT_COUNT,
    AUTHENTICATE_COUNT,
    CLOSE_COUNT,
    CHECK_COUNT,
    STARTTLS_COUNT,
    SORT_COUNT,
    NAMESPACE_COUNT,
    COPY_COUNT,
    GETQUOTAROOT_COUNT,
    STATUS_COUNT,
    GETACL_COUNT,
    AUTHENTICATION_YES,
    ACTIVE_CONNECTIONS,
    SETACL_COUNT,
    LOGOUT_COUNT,
    UNSUBSCRIBE_COUNT,
    SEARCH_COUNT,
    NOOP_COUNT,
    GETANNOTATION_COUNT,
    LOGIN_COUNT,
    AUTHENTICATION_NO,
    BBOARD_COUNT,
    GETQUOTA_COUNT,
    APPEND_COUNT,
    MYRIGHTS_COUNT,
    COMPRESS_COUNT,
    CAPABILITY_COUNT,
    SUBSCRIBE_COUNT,
    EXPUNGE_COUNT,
    GETUIDS_COUNT,
    PARTIAL_COUNT,
    RENAME_COUNT,
    LISTRIGHTS_COUNT,
    LSUB_COUNT,
    UNSELECT_COUNT,
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



