#include "net.h"



net::net(char* conf, char* prot, bool server)
{
/*    if(this->configuration.stat==false)
        if(!conf.find("$\/\no data")==0)
            this->configuration=config_reader(conf);
*/

    this->server=server;

    this->config_set(conf, NULL,NULL);

    //clear address structus
    memset(&this->local_addr, 0, sizeof(struct sockaddr_in));
    memset(&this->peer_addr, 0, sizeof(struct sockaddr_in));


    //socket creation

    this->ip=IPV4;
    this->prot=prot;

    // ip version independant handle

    struct addrinfo hints;
    memset(&hints, 0, sizeof(struct addrinfo));

    // control used address family
    if(this->ip==IPV4)
        hints.ai_family = AF_INET;    // Allow IPv4
    if(this->ip==IPV6)
        hints.ai_family = AF_INET6;    // Allow IPv6
    if(this->ip==_4_6)
        hints.ai_family = AF_UNSPEC;    // Allow IPv4 or IPv6

    // controle socket type: TCP or UDP
    if(this->prot==TCP)
        hints.ai_socktype = SOCK_STREAM; // connected socket
    if(this->prot==UDP)
        hints.ai_socktype = SOCK_DGRAM; // Datagram socket


    if(this->server)
        hints.ai_flags = AI_PASSIVE;    // For wildcard IP address
    hints.ai_protocol = 0;          // Any protocol
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;
/*
    if(this->server)
        this->configuration.addr=NULL;
*/

    struct addrinfo *result, *rp;


 //   char port[]="5000";

    int s=getaddrinfo(this->configuration.addr, this->configuration.port, &hints, &result);

    if (s != 0)
    {
                   fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
                   exit(EXIT_FAILURE);
    }

    int listenfd=-1;

    for (rp = result; rp != NULL; rp = rp->ai_next)
    {
                  listenfd  = socket(rp->ai_family, rp->ai_socktype,
                           rp->ai_protocol);
                   if (listenfd == -1)
                       continue;

                   this->local_i_addr=rp;
                   this->p_sock=listenfd;
                   break;
    }


}



// this function is to set network configuration value
// if the first argument is provided, the others is useless and have to be set to NULL
// otherwise, depending on what you want to do, one or all of other argument
void net::config_set(char* path,char* addr, char* port)
{
    if(path==NULL)
    {
        bool tic=false;
        if(addr!=NULL)
        {
            this->configuration.addr=addr;
            tic=true;
        }
        if(port!=NULL)
        {
            this->configuration.port=port;
            tic=true;
        }
        this->configuration.stat=tic;
        return;
    }
    else
    {
        this->configuration=config_reader(path);
    }

}



/*
template <typename T>
T net::get_addr_l()
{
    if(this->configuration.stat)
        return htonl(*this->configuration.addr);

     if(this->ip==IPV4)
         return htonl(INADDR_ANY);

     if(this->ip==IPV6)
         return (const struct in6_addr)in6addr_any;
}
*/

char* net::str_reader()
{
        int n = NULL;

        this->int_reader(&n);

        if(n==0||n==NULL)
        {
            return NULL;
        }

        char lu[n];

    //    lu=(char*)std::realloc(lu,(n*sizeof(char)));

        if(lu==NULL)
        {
            std::fprintf(OUTPUT,"Allocation error" , strerror(errno));

            return NULL;
        }

        lu[0]='\0';

    //    int a=this->readLine(lu,n);
        int a;

        if(this->prot==TCP)
        {

            a=recv(this->sock,lu,n,0);
        }
        if(this->prot==UDP)
        {
                a = recvfrom(this->sock, lu, n,
                            MSG_WAITALL, ( struct sockaddr *) &peer_addr,
                            NULL);
        }

          if( a < n-1)
          {
              std::fprintf(OUTPUT,"Read Error" , strerror(errno));

            return NULL;
          }

          lu[n]='\0';
          return lu;
}

char* net::str_reader(int n)
{
    if(this->prot==TCP)
    {

        char* lu=NULL;

        if(n==0||n==NULL)
        {
            return NULL;
        }

        lu=(char*)std::realloc(lu,(n*sizeof(char)));

        if(lu==NULL)
        {
            std::fprintf(OUTPUT,"Allocation error" , strerror(errno));

            return NULL;
        }

        lu[0]='\0';

    //    int a=this->readLine(lu,n);
        int a;

        if(this->prot==TCP)
        {

            a=recv(this->sock,lu,n,0);
        }
        if(this->prot==UDP)
        {
//            int len;
                a = recvfrom(this->sock, lu, n,
                            MSG_WAITALL, ( struct sockaddr *) &peer_addr,
                            NULL);
        }

          if( a < n-1)
          {

              std::fprintf(OUTPUT,"Read Error" , strerror(errno));

            return NULL;
          }

          lu[n]='\0';
          return lu;

    }

    if(this->prot==UDP)
    {

    }
    return NULL;
}

int net::str_sender(char* fi)
{
    if(this->prot==TCP)
    {

        int a=strlen(fi);

        this->int_sender(strlen(fi));

        int n=send(this->sock,fi,a,0);

        if(n<0)
            perror("Error while sending");
        return n;
    }

    if(this->prot==UDP)
    {

    }
    return 0;
}

int net::str_sender(char* fi,int size)
{


        this->int_sender(size);
    int n;
    if(this->prot==TCP)
    {
        n=send( this->sock , fi , size, 0 );
    }else
        if(this->prot==UDP)
        {
            n=sendto(this->sock, fi, size,
                     MSG_CONFIRM, (const struct sockaddr *) &this->peer_addr,
                         NULL);
        }

        if(n<0)
            perror("Error while sending");
        return n;

}

int net::int_reader(int* num)
{

    if(this->prot==TCP)
    {

        char buf[10] = "";

        int rest=recv( this->sock , buf , sizeof buf , 0 );

        sscanf( buf , "%d" , num );

        return rest;
    }

    if(this->prot==UDP)
    {

    }


}

int net::int_sender(int num)
{

    if(this->prot==TCP)
    {

        char buf[10] = "";

        sprintf( buf , "%d" , num );

        int rest=send( this->sock , buf , sizeof buf , 0 );

        return rest;
    }

    if(this->prot==UDP)
    {

    }


}

int net::file_sender(char* path)
{
    if(this->prot==TCP)
    {

        std::fstream file(path);

            std::stringstream hi;
        if(file.is_open())
        {

            hi<<file.rdbuf();

            file.close();
        }
        else
            return -2;
        std::string kol=hi.str();

    char* bi=const_cast<char*>(kol.c_str());

        if(this->str_sender(bi)<0)
            return -1;

         return 0;
    }

    if(this->prot==UDP)
    {

    }

}

bool net::file_reader(char* destination)
{

    if(this->prot==TCP)
    {

        char*gi=this->getall();

        std::ofstream file(destination);

        if(!file.is_open())
        {
            return false;
        }

        file<<gi;

        return true;

    }

    if(this->prot==UDP)
    {

    }

}

char* net::getall()
{
    if(this->prot==TCP)
    {

    }

    if(this->prot==UDP)
    {

    }

    int size=NULL;

    this->int_reader(&size);

    if(size<=0)
    {
        return NULL;
    }

    char* data= this->str_reader(size);

    return data;
}

