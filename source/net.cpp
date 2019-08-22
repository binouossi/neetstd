#include "net.h"



net::net(char* conf, char* prot, bool server)
{

    this->config_set(conf, NULL,NULL);

    //clear address structus
    memset(&this->local_addr, 0, sizeof(struct sockaddr_in));
    memset(&this->peer_addr, 0, sizeof(struct sockaddr_in));

    //socket creation

    this->ip_v=IPV4;
    this->prot=prot;

    // ip version independant handle

    struct addrinfo *result, *rp, hints;
    memset(&hints, 0, sizeof(struct addrinfo));
    memset(&result, 0, sizeof(struct addrinfo*));
    memset(&rp, 0, sizeof(struct addrinfo*));


    // control used address family
    if(this->ip_v==IPV4)
        hints.ai_family = AF_INET;    // Allow IPv4
    if(this->ip_v==IPV6)
        hints.ai_family = AF_INET6;    // Allow IPv6
    if(this->ip_v==_4_6)
        hints.ai_family = AF_UNSPEC;    // Allow IPv4 or IPv6

    // controle socket type: TCP or UDP
    if(this->prot==TCP)
        hints.ai_socktype = SOCK_STREAM; // connected socket
    if(this->prot==UDP)
        hints.ai_socktype = SOCK_DGRAM; // Datagram socket


    if(server)
        hints.ai_flags = AI_PASSIVE;    // For wildcard IP address

    hints.ai_protocol = 0;          // Any protocol
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;
/*
    if(server)
        this->configuration.addr=NULL;
*/



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

                   //suit=rp;
                   if(server)
                       this->local_addr=rp;
                   else
                       this->peer_addr=rp;


                   this->sock=listenfd;
                   break;
    }

//    freeaddrinfo(result);
 //   freeaddrinfo(hints);
 //   freeaddrinfo(rp);
}



net::~net()
{
    freeaddrinfo(this->local_addr);
    freeaddrinfo(this->peer_addr);
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

int net::unit_data_sender(int q, char* buf)
{
    char tmp[q];
    for(int k=0;k<=q;k++)
    {
        //tmp[k]=buf[j];
     //   j++;
    }
    int y=sizeof(tmp);
    this->str_sender(tmp,y);
    return 0;
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

  //      if(this->prot==TCP)
  //      {

            a=recv(this->sock,lu,n,0);
//        }
//        if(this->prot==UDP)
//        {
                a = recvfrom(this->sock, lu, n,
                            MSG_WAITALL, this->peer_addr->ai_addr,
                            &this->peer_addr->ai_addrlen);
//        }

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
 //   if(this->prot==TCP)
 //   {

//    char lu[n];
        char* lu=NULL;

///        if(n==0||n==NULL)
//        {
//            return NULL;
//        }

        lu=(char*)std::realloc(lu,(n*sizeof(char)));

        if(lu==NULL)
        {
            std::fprintf(OUTPUT,"Allocation error" , strerror(errno));

            return NULL;
        }

 //       memset(&lu, 0, n*sizeof(char));

        lu[0]='\0';

    //    int a=this->readLine(lu,n);
//        int a;
/*
        if(this->prot==TCP)
        {

            a=recv(this->sock,lu,n,0);
        }
        if(this->prot==UDP)
        {*/
//            int len;
         //       a = recvfrom(this->sock, lu, n,
         //                   MSG_WAITALL, this->peer_addr->ai_addr,
         //                   &this->peer_addr->ai_addrlen);
 //       }

          if( recvfrom(this->sock, lu, n,
                          0, this->peer_addr->ai_addr,
                          &this->peer_addr->ai_addrlen) < 0)
          {
//                std::cout<<lu<<std::endl;

              perror("Read Error");

            return NULL;
          }

          lu[n]='\0';

//          std::cout<<lu<<std::endl;

          return lu;

  //  }

  /*  if(this->prot==UDP)
    {

    }*/
    return NULL;
}

int net::str_sender(char* fi)
{
    if(this->prot==TCP)
    {

        int a=strlen(fi);

        this->int_sender(strlen(fi));

        int n=send(this->sock,fi,a,0);

       // if(n<0)
         //   perror("Error while sending");
        return n;
    }

    if(this->prot==UDP)
    {

    }
    return 0;
}

int net::str_sender(char* fi,int size)
{

    int n;

            if((n=sendto(this->sock, fi, sizeof fi,
                     0, (const struct sockaddr *) &this->peer_addr->ai_addr,
                         NULL))<0)
            {
                perror("Error while sending");
            }
        return n;

}

int net::int_reader(int* num)
{

 /*   if(this->prot==TCP)
    {

        char buf[10] = "";

        int rest=recv( this->sock , buf , sizeof buf , 0 );

        sscanf( buf , "%d" , num );

        return rest;
    }

    if(this->prot==UDP)
    {*/
        char buf[10] = "";

        int rest=0;
        if((rest=recvfrom( this->sock , buf , sizeof buf , MSG_WAITALL,
                           this->peer_addr->ai_addr, &this->peer_addr->ai_addrlen))<0)
        {
            perror("Error while receving: ");
        }

        sscanf( buf , "%d" , num );

        return rest;
  //  }


}

int net::int_sender(int num)
{

//    if(this->prot==TCP)
//    {

        char buf[10] = "";

        sprintf( buf , "%d" , num );

        int rest=0;

        if((rest=sendto( this->sock , buf , sizeof(buf) , 0 ,
                         this->peer_addr->ai_addr, this->peer_addr->ai_addrlen))<0)
        {
            perror("Eroor while sending");
        }

        return rest;
  //  }
/*
    if(this->prot==UDP)
    {

    }
*/

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

