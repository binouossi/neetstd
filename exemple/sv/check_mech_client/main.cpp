#include "func.h"
#include "fonction.cpp"


using namespace std;



//display_file=stdout;


/*
void print_mecanism(gss_OID_set *mec)
{
    return;
}*/
/*gss_buffer_t init_gss_buffer_t(gss_buffer_t *string=NULL)
{

    *(string->length)=NULL;
    *(string->value)=NULL;
    return string;
}*/

/*
void G_import_name(OM_uint32 *out,gss_buffer_t in_name, \
                   gss_OID name_type, gss_name_t *out_name,\
                   bool act=false)
{
    printf("wtf\n");
   OM_uint32 output=0;
   output=gss_import_name(out,in_name,name_type,out_name);
    if(act)
    {
        switch (output) {
        case GSS_S_COMPLETE:
            printf("Successful completion");
            break;
        case GSS_S_BAD_NAMETYPE:
            printf(" The  input_name_type  was unrecognized");
            break;
        case GSS_S_BAD_NAME:
            printf("The input_name parameter could  not  be\
                   interpreted as a name of the specified type.");
            break;
        case GSS_S_BAD_MECH:
        printf("The input name-type was GSS_C_NT_EXPORT_NAME\
               , but the mechanism contained  within the\
               input-name is not supported.");
        break;
        default:
            break;
        }
    }
}
*/ /*
gss_cred_id_t get_cred(char* nom=NULL, gss_OID name_type=NULL)
{
   printf("nobody\n");

    OM_uint32 *out,*tmp;
    gss_name_t *out_name;

    gss_buffer_t in_name=string_to_gss(nom);

    G_import_name(out,in_name,name_type,out_name);
    gss_cred_id_t *cred;
    gss_OID_set *mec;
   /*switch (gss_acquire_cred(out,*name,GSS_C_INDEFINITE,GSS_C_NO_OID_SET,\
                            GSS_C_BOTH,cred,NULL,NULL))*/
/*   switch (gss_acquire_cred(out,*name,GSS_C_INDEFINITE,GSS_C_NO_OID_SET,\
                                GSS_C_BOTH,cred,mec,tmp))
   {

        case GSS_S_COMPLETE:
            printf("success");
            print_mecanism(mec);
            printf("dure: %d",tmp);
            return *cred;
        case GSS_S_BAD_MECH:
            printf("Unavailable mechanism requested");
            break;
//            return false;
        case GSS_S_BAD_NAMETYPE:
            printf("Type contained within desired_name  parameter  is \
              not supported");
                   break;
//            return false;
        case GSS_S_BAD_NAME:
            printf("Value  supplied  for  desired_name  parameter is ill\
                  formed.");
                   break;
//            return false;
        case GSS_S_CREDENTIALS_EXPIRED:
            printf(" The  credentials  could  not  be  acquired\
              Because they have expired.");
                   break;
//            return false;
        case GSS_S_NO_CRED:
            printf("No credentials were found for the specified name.\n");
            break;
//            return false;
   default:
                   break;
//       return false;

   }


return GSS_C_NO_CREDENTIAL;
}*/




string getrhostname()
{

}

int main()
{
//    const char /**service_name,*/ *hostname;/*, *msg*/;
    char msg[2000];
    char service_name[128];
    char hostname[128];
    char *mechanism = 0;
    u_short port = 4444;
    int use_file = 0;
    OM_uint32 deleg_flag = 0, min_stat;

  //  hostname=getrhostname().c_str();


    std::cout<<"service name"<<std::endl;
    std::cin>>service_name;
    std::cout<<"hostname:"<<std::endl;
    std::cin>>hostname;
    std::cout<<"message:"<<std::endl;
    std::cin>>msg;

    strcat(service_name, "@");
    strcat(service_name, hostname);

    gss_OID g_mechOid = GSS_C_NULL_OID;

    if(call_server(hostname, port, g_mechOid, service_name,\
                   deleg_flag, msg, use_file) < 0)
            exit(1);


    if (g_mechOid != GSS_C_NULL_OID)
    (void) gss_release_oid(&min_stat, &g_mechOid);
    //get_cred("cani",GSS_C_NT_HOSTBASED_SERVICE);

    std::cout<<"lui meme"<<std::endl;

    return 0;
}


