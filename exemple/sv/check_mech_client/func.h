#ifndef FUNC_H
#define FUNC_H


/** headers */
#include <iostream>
#include <stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<sys/time.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<error.h>
#include<sys/stat.h>
#include<fcntl.h>
#include <gss.h>
//#include <gssapi.h>
//#include <gssapi/gssapi_ext.h>
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif
//#include <mit-krb5/gssapi.h>
using namespace std;

/** variable */

gss_OID g_mechOid = GSS_C_NULL_OID;


/** fonction */

int send_token(int s, gss_buffer_t tok);

void display_ctx_flags(OM_uint32 flags);

int recv_token(int s, gss_buffer_t tok);

static int read_all(int fildes, char *buf, unsigned int nbyte);

static int write_all(int fildes, char *buf, unsigned int nbyte);


void read_file(char *file_name, gss_buffer_t in_buf);

int call_server(char *host, u_short port, gss_OID oid, char *service_name,\
                OM_uint32 deleg_flag, char *msg, int use_file);

static void parse_oid(char *mechanism, gss_OID *oid);

gss_buffer_desc string_to_gss(char*);

void display_status(char *msg, OM_uint32 maj_stat,OM_uint32 min_stat);

static void display_status_1(char *m, OM_uint32 code, int type);


int client_establish_context(int s, char *service_name, gss_OID oid,\
                             OM_uint32 deleg_flag, gss_ctx_id_t *gss_context,\
                             OM_uint32 *ret_flags);

int connect_to_server(char *host, u_short port);

const char *
__gss_oid_to_mech(
    const gss_OID oid		/* mechanism oid */
);

std::string getrhostname();

#endif FUNC_H
