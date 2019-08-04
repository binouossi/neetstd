//#include "func.h"

//display_file = stdout;

FILE *display_file=stdout;

/*
gss_buffer_desc string_to_gss(char* word)
{
    gss_buffer_desc gss_string;
    gss_string->length=strlen(word)+1;
    gss_string->value=word;
    return gss_string;
}
*/

int send_token(int s, gss_buffer_t tok)
{
    int len, ret;
    len = htonl((OM_uint32)tok->length);
    ret = write_all(s, (char *) &len, sizeof(int));
    if (ret < 0)
    {
        perror("sending token length");
        return -1;
    } else if (ret != 4)
    {
        if(display_file)
            fprintf(display_file,"sending token length: %d of %d bytes written\n",
                    ret, 4);
            return -1;
    }
    ret = write_all(s, (char*)tok->value, (OM_uint32)tok->length);
    if (ret < 0)
    {
        perror("sending token data");
        return -1;
    } else if (ret != tok->length)
    {
        if (display_file)
            fprintf(display_file,
                    "sending token data: %d of %d bytes written\n",
                    ret, tok->length);
        return -1;
    }
    return 0;
}

int recv_token(int s, gss_buffer_t tok)
{
    int ret, len;
    ret = read_all(s, (char *) &len, sizeof(int));
    if (ret < 0)
    {
        perror("reading token length");
        return -1;
    } else if (ret != 4)
    {
        if (display_file)
            fprintf(display_file,
                    "reading token length: %d of %d bytes read\n", ret, 4);
        return -1;
    }
    tok->length = ntohl(len);
    tok->value = (char *) malloc(tok->length);
    if (tok->value == NULL)
    {
        if (display_file)
            fprintf(display_file,
                    "Out of memory allocating token data\n");
        return -1;
    }
    ret = read_all(s, (char *) tok->value, (OM_uint32)tok->length);
    if (ret < 0)
    {
        perror("reading token data");
        free(tok->value);
        return -1;
    } else if (ret != tok->length)
    {
        fprintf(stderr, "sending token data: %d of %d bytes written\n",
                ret, tok->length);
        free(tok->value);
        return -1;
    }
    return 0;
}

static int read_all(int fildes, char *buf, unsigned int nbyte)
{
    int ret;
    char *ptr;
    for (ptr = buf; nbyte; ptr += ret, nbyte -= ret)
    {
        ret = read(fildes, ptr, nbyte);
        if (ret < 0)
        {
            if (errno == EINTR)
                continue;
            return(ret);
        } else if (ret == 0)
        {
            return(ptr-buf);
        }
    }
    return(ptr-buf);
}

static int write_all(int fildes, char *buf, unsigned int nbyte)
{
    int ret;
    char *ptr;
    for (ptr = buf; nbyte; ptr += ret, nbyte -= ret)
    {
        ret = write(fildes, ptr, nbyte);
        if (ret < 0)
        {
            if (errno == EINTR)
                continue;
            return(ret);
        } else if (ret == 0)
        {
            return(ptr-buf);
        }
    }
    return(ptr-buf);
}

void display_status(char *msg, OM_uint32 maj_stat,OM_uint32 min_stat)
{
display_status_1(msg, maj_stat, GSS_C_GSS_CODE);
display_status_1(msg, min_stat, GSS_C_MECH_CODE);
}

static void display_status_1(char *m, OM_uint32 code, int type)
{
    OM_uint32 maj_stat, min_stat;
    gss_buffer_desc msg = GSS_C_EMPTY_BUFFER;
    OM_uint32 msg_ctx;
    msg_ctx = 0;
    while(1)
    {
        maj_stat = gss_display_status(&min_stat, code,type, g_mechOid,\
                                      &msg_ctx, &msg);
        if (maj_stat != GSS_S_COMPLETE)
        {
            if (display_file)
            {
                fprintf(display_file, "error in gss_display_status"
                                  " called from <%s>\n", m);
            }
            break;
        }
        else if (display_file)
            fprintf(display_file, "GSS-API error %s: %s\n", m,
                        (char *)msg.value);
        if (msg.length != 0)
            (void) gss_release_buffer(&min_stat, &msg);
        if (!msg_ctx)
            break;
    }
}
//__gss_oid_to_mech
void display_ctx_flags(OM_uint32 flags)
{
    if (flags & GSS_C_DELEG_FLAG)
        fprintf(display_file, "context flag: GSS_C_DELEG_FLAG\n");
    if (flags & GSS_C_MUTUAL_FLAG)
        fprintf(display_file, "context  flag: GSS_C_MUTUAL_FLAG\n");
    if (flags & GSS_C_REPLAY_FLAG)
        fprintf(display_file, "context flag: GSS_C_REPLAY_FLAG\n");
    if (flags & GSS_C_SEQUENCE_FLAG)
        fprintf(display_file, "context flag: GSS_C_SEQUENCE_FLAG\n");
    if (flags & GSS_C_CONF_FLAG )
        fprintf(display_file, "context flag: GSS_C_CONF_FLAG \n");
    if (flags & GSS_C_INTEG_FLAG )
        fprintf(display_file, "context flag: GSS_C_INTEG_FLAG \n");
}



int connect_to_server(char *host, u_short port)
{
    struct sockaddr_in saddr;
    struct hostent *hp;
    int s;
    if ((hp = gethostbyname(host)) == NULL)
    {
        fprintf(stderr, "Unknown host: %s\n", host);
        return -1;
    }

    saddr.sin_family = hp->h_addrtype;

    memcpy((char *)&saddr.sin_addr, hp->h_addr, sizeof(saddr.sin_addr));

    saddr.sin_port = htons(port);

    if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("creating socket");
        return -1;
    }

    if (connect(s, (struct sockaddr *)&saddr, sizeof(saddr)) < 0)
    {
        perror("connecting to server");
        (void) close(s);
        return -1;
    }

    return s;
}

int client_establish_context(int s, char *service_name, gss_OID oid,\
                             OM_uint32 deleg_flag, gss_ctx_id_t *gss_context,\
                             OM_uint32 *ret_flags)
{
    gss_buffer_desc send_tok, recv_tok, *token_ptr;
    gss_name_t target_name;
    OM_uint32 maj_stat, min_stat;
    /*
    * Import the name into target_name.  Use send_tok to save
    * local variable space.
    */

//    send_tok=string_to_gss(service_name);
    send_tok.value = service_name;
    send_tok.length = strlen(service_name) + 1;
    maj_stat = gss_import_name(&min_stat, &send_tok,\
                               (gss_OID) GSS_C_NT_HOSTBASED_SERVICE,\
                               &target_name);
    if (maj_stat != GSS_S_COMPLETE) {
    display_status("parsing name", maj_stat, min_stat);
    return -1;
    }
    token_ptr = GSS_C_NO_BUFFER;
    *gss_context = GSS_C_NO_CONTEXT;
    do {
    maj_stat =gss_init_sec_context(&min_stat, GSS_C_NO_CREDENTIAL,\
                                   gss_context, target_name, oid,\
                                   GSS_C_MUTUAL_FLAG | GSS_C_REPLAY_FLAG |\
                                   deleg_flag, 0, NULL,/* no channel bindings */\
                                   token_ptr, NULL,/* ignore mech type */\
                                   &send_tok, ret_flags, NULL/* ignore time_rec */);

    if (gss_context == NULL)
    {
        printf("Cannot create context\n");
        return GSS_S_NO_CONTEXT;
    }

    if (token_ptr != GSS_C_NO_BUFFER)
        (void) gss_release_buffer(&min_stat, &recv_tok);

    if (maj_stat!=GSS_S_COMPLETE && maj_stat!=GSS_S_CONTINUE_NEEDED)
    {
        display_status("initializing context", maj_stat, min_stat);

        (void) gss_release_name(&min_stat, &target_name);

        return -1;
    }

    if (send_tok.length != 0)
    {
        fprintf(stdout, "Sending init_sec_context token (size=%ld)...",
        send_tok.length);
        if (send_token(s, &send_tok) < 0)
        {
            (void) gss_release_buffer(&min_stat, &send_tok);
            (void) gss_release_name(&min_stat, &target_name);
            return -1;
        }
    }

    (void) gss_release_buffer(&min_stat, &send_tok);

    if (maj_stat == GSS_S_CONTINUE_NEEDED)
    {
        fprintf(stdout, "continue needed...");

        if (recv_token(s, &recv_tok) < 0)
        {
            (void) gss_release_name(&min_stat, &target_name);
            return -1;
        }

        token_ptr = &recv_tok;
    }

    printf("\n");

    } while (maj_stat == GSS_S_CONTINUE_NEEDED);

    (void) gss_release_name(&min_stat, &target_name);

    return 0;
}
static void parse_oid(char *mechanism, gss_OID *oid)
{
    char *mechstr = 0, *cp;
    gss_buffer_desc tok;
    OM_uint32 maj_stat, min_stat;
    if (isdigit(mechanism[0]))
    {
        mechstr = (char*)malloc(strlen(mechanism)+5);
        if (!mechstr)
        {
            printf("Couldn't allocate mechanism scratch!\n");
            return;
        }

        sprintf(mechstr, "{ %s }", mechanism);

        for (cp = mechstr; *cp; cp++)
            if (*cp == '.')
                *cp = ' ';
        tok.value = mechstr;
    }else
    tok.value = mechanism;

    tok.length = strlen((char*)tok.value);

    maj_stat = gss_str_to_oid(&min_stat, &tok, oid);

    if (maj_stat != GSS_S_COMPLETE)
    {
        display_status("str_to_oid", maj_stat, min_stat);
        return;
    }

    if (mechstr)
        free(mechstr);
}

int call_server(char *host, u_short port, gss_OID oid, char *service_name,\
                OM_uint32 deleg_flag, char *msg, int use_file)
{
    gss_ctx_id_t context;
    gss_buffer_desc in_buf, out_buf, context_token;
    int s, state;
    OM_uint32 ret_flags;
    OM_uint32 maj_stat, min_stat;
    gss_name_t src_name, targ_name;
    gss_buffer_desc sname, tname;
    OM_uint32 lifetime;
    gss_OID mechanism, name_type;
    int is_local;
    OM_uint32 context_flags;
    int is_open;
    gss_qop_t qop_state;
    gss_OID_set mech_names;
    gss_buffer_desc oid_name;
    int i;
    int conf_req_flag = 0;
    int req_output_size = 1012;
    OM_uint32 max_input_size = 0;
    char *mechStr;

    /* Open connection */
    if ((s = connect_to_server(host, port)) < 0)
        return -1;
    /* Establish context */
    if (client_establish_context(s, service_name, oid, deleg_flag, &context,\
                                 &ret_flags) < 0)
    {
        (void) close(s);
        return -1;
    }

    /* Save and then restore the context */
    maj_stat = gss_export_sec_context(&min_stat, &context, &context_token);

    if (maj_stat != GSS_S_COMPLETE)
    {
        display_status("exporting context", maj_stat, min_stat);
        return -1;
    }

    maj_stat = gss_import_sec_context(&min_stat, &context_token, &context);

    if (maj_stat != GSS_S_COMPLETE)
    {
        display_status("importing context", maj_stat, min_stat);
        return -1;
    }

    (void) gss_release_buffer(&min_stat, &context_token);

    /* display the flags */
    display_ctx_flags(ret_flags);
    /* Get context information */
    maj_stat = gss_inquire_context(&min_stat, context, &src_name,\
                                   &targ_name, &lifetime, &mechanism,\
                                   &context_flags, &is_local, &is_open);

    if (maj_stat != GSS_S_COMPLETE)
    {
        display_status("inquiring context", maj_stat, min_stat);
        return -1;
    }

    if (maj_stat == GSS_S_CONTEXT_EXPIRED)
    {
        printf(" context expired\n");
        display_status("Context is expired", maj_stat, min_stat);
        return -1;
    }

    /* Test gss_wrap_size_limit */
    maj_stat = gss_wrap_size_limit(&min_stat, context, conf_req_flag,\
                                   GSS_C_QOP_DEFAULT, req_output_size,\
                                   &max_input_size);

    if (maj_stat != GSS_S_COMPLETE)
    {
        display_status("wrap_size_limit call", maj_stat, min_stat);
    }else
        fprintf(stderr, "gss_wrap_size_limit returned "\
                "max input size = %d \n"
                "for req_output_size = %d with Integrity only\n",
                max_input_size , req_output_size , conf_req_flag);

    conf_req_flag = 1;

    maj_stat = gss_wrap_size_limit(&min_stat, context, conf_req_flag,\
                                   GSS_C_QOP_DEFAULT, req_output_size,\
                                   &max_input_size);

    if (maj_stat != GSS_S_COMPLETE)
    {
        display_status("wrap_size_limit call", maj_stat, min_stat);
    }else
        fprintf (stderr, "gss_wrap_size_limit returned "
                " max input size = %d \n"
                "for req_output_size = %d with "
                "Integrity & Privacy \n",
                max_input_size , req_output_size );

    maj_stat = gss_display_name(&min_stat, src_name, &sname, &name_type);

    if (maj_stat != GSS_S_COMPLETE)
    {
        display_status("displaying source name", maj_stat, min_stat);
        return -1;
    }

    maj_stat = gss_display_name(&min_stat, targ_name, &tname, (gss_OID *) NULL);

    if (maj_stat != GSS_S_COMPLETE)
    {
        display_status("displaying target name", maj_stat, min_stat);
        return -1;
    }

    fprintf(stderr, "\"%.*s\" to \"%.*s\", lifetime %u, flags %x, %s, %s\n",
            (int) sname.length, (char *) sname.value, (int) tname.length,
            (char *) tname.value, lifetime, context_flags,\
            (is_local) ? "locally initiated" : "remotely initiated",
            (is_open) ? "open" : "closed");

    (void) gss_release_name(&min_stat, &src_name);

    (void) gss_release_name(&min_stat, &targ_name);

    (void) gss_release_buffer(&min_stat, &sname);

    (void) gss_release_buffer(&min_stat, &tname);

    maj_stat = gss_oid_to_str(&min_stat, name_type, &oid_name);

    if (maj_stat != GSS_S_COMPLETE)
    {
        display_status("converting oid->string", maj_stat, min_stat);
        return -1;
    }

    fprintf(stderr, "Name type of source name is %.*s.\n",
                    (int) oid_name.length, (char *) oid_name.value);

    (void) gss_release_buffer(&min_stat, &oid_name);

            /* Now get the names supported by the mechanism */
    maj_stat = gss_inquire_names_for_mech(&min_stat, mechanism,\
                                                  &mech_names);

    if (maj_stat != GSS_S_COMPLETE)
    {
        display_status("inquiring mech names", maj_stat, min_stat);
        return -1;
    }

    maj_stat = gss_oid_to_str(&min_stat, mechanism, &oid_name);

    if (maj_stat != GSS_S_COMPLETE)
    {
        display_status("converting oid->string", maj_stat, min_stat);
        return -1;
    }

    mechStr = (char *)__gss_oid_to_mech(mechanism);

    fprintf(stderr, "Mechanism %.*s (%s) supports %d names\n",
                    (int) oid_name.length, (char *) oid_name.value,
                    (mechStr == NULL ? "NULL" : mechStr),
                     mech_names->count);

    (void) gss_release_buffer(&min_stat, &oid_name);

    for (i=0; i < mech_names->count; i++)
    {
        maj_stat = gss_oid_to_str(&min_stat, &mech_names->elements[i],\
                                         &oid_name);

        if (maj_stat != GSS_S_COMPLETE)
        {
            display_status("converting oid->string", maj_stat, min_stat);
            return -1;
        }

        fprintf(stderr, " %d: %.*s\n", i,
                        (int) oid_name.length, (char *) oid_name.value);

        (void) gss_release_buffer(&min_stat, &oid_name);
      }

    (void) gss_release_oid_set(&min_stat, &mech_names);

    if (use_file)
    {
        read_file(msg, &in_buf);
    }else
      {
                /* Seal the message */
        in_buf.value = msg;
        in_buf.length = strlen(msg) + 1;
      }
        /*ret_flag||ret_flags*/
    if (ret_flags & GSS_C_CONF_FLAG)
        state = 1;
    else
        state = 0;

    maj_stat = gss_wrap(&min_stat, context, 1, GSS_C_QOP_DEFAULT,\
                                &in_buf, &state, &out_buf);

    if(maj_stat != GSS_S_COMPLETE)
    {
        display_status("wrapping message", maj_stat, min_stat);
        (void) close(s);
        (void) gss_delete_sec_context(&min_stat, &context, GSS_C_NO_BUFFER);
        return -1;
    }else if(! state)
    {
        fprintf(stderr, "Warning! Message not encrypted.\n");
    }

            /* Send to server */
    if (send_token(s, &out_buf) < 0)
    {
        (void) close(s);
        (void) gss_delete_sec_context(&min_stat, &context,\
                                              GSS_C_NO_BUFFER);
        return -1;
    }

    (void) gss_release_buffer(&min_stat, &out_buf);

            /* Read signature block into out_buf */

    if (recv_token(s, &out_buf) < 0)
    {
       (void) close(s);
       (void) gss_delete_sec_context(&min_stat, &context,\
                                              GSS_C_NO_BUFFER);
       return -1;
    }

            /* Verify signature block */
    maj_stat = gss_verify_mic(&min_stat, context, &in_buf,\
                                      &out_buf, &qop_state);
    if (maj_stat != GSS_S_COMPLETE)
    {
       display_status("verifying signature", maj_stat, min_stat);
       (void) close(s);
       (void) gss_delete_sec_context(&min_stat, &context,\
                                              GSS_C_NO_BUFFER);
        return -1;
     }

    (void) gss_release_buffer(&min_stat, &out_buf);

    if (use_file)
       free(in_buf.value);

    printf("Signature verified.\n");

            /* Delete context */
    maj_stat = gss_delete_sec_context(&min_stat, &context, &out_buf);

    if (maj_stat != GSS_S_COMPLETE)
    {
        display_status("deleting context", maj_stat, min_stat);
        (void) close(s);
        (void) gss_delete_sec_context(&min_stat, &context, GSS_C_NO_BUFFER);
        return -1;
    }

         (void) gss_release_buffer(&min_stat, &out_buf);

         (void) close(s);

         return 0;
}


void read_file(char *file_name, gss_buffer_t in_buf)
{
    int fd, bytes_in, count;
    struct stat stat_buf;
    if ((fd = open(file_name, O_RDONLY, 0)) < 0)
    {
        perror("open");
        fprintf(stderr, "Couldn't open file %s\n", file_name);
        exit(1);
    }

    if (fstat(fd, &stat_buf) < 0)
    {
        perror("fstat");
        exit(1);
    }

    in_buf->length = stat_buf.st_size;

    in_buf->value = malloc(in_buf->length);

    if (in_buf->value == 0)
    {
        fprintf(stderr, "Couldn't allocate %ld byte buffer for reading file\n",in_buf->length);
        exit(1);
    }

    memset(in_buf->value, 0, in_buf->length);

    for (bytes_in = 0; bytes_in < in_buf->length; bytes_in += count)
    {
        count = read(fd, in_buf->value, (OM_uint32)in_buf->length);
        if (count < 0)
        {
            perror("read");
            exit(1);
        }

        if (count == 0)
            break;
    }

    if (bytes_in != count)
    fprintf(stderr, "Warning, only read in %d bytes, expected %d\n",\
            bytes_in, count);
}
