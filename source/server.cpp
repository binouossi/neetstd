#include "server.h"


int sigflag;

int resquiescat(){wait(NULL);sigflag = 1;return 0;}


///constructor with a protocol argument set
server::server(char* conf, char* prot, void* (communicator)(server, va_list&),  ...):net(conf, prot, true)
{
//    this->prot=prot;
    this->deamon=PROCESS;
//    this->ip=IPV4;

    va_list vars;
    va_start(vars,communicator);

/*
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



    hints.ai_flags = AI_PASSIVE;    // For wildcard IP address
    hints.ai_protocol = 0;          // Any protocol
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;


    struct addrinfo *result, *rp;


    char port[]="5000";

    int s=getaddrinfo(NULL, port, &hints, &result);

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

    */

                   if (bind(this->p_sock, this->local_i_addr->ai_addr, this->local_i_addr->ai_addrlen) < 0)
                   {

                       perror("bind error:");
                                 exit(-1);

                   }
                       sigset(SIGCHLD, (sighandler_t)resquiescat);


                //       std::cout<<"fine"<<std::endl;

                       if(this->prot==TCP)
                       {

                           //start listenning
                           if(listen(this->p_sock, 5) <0)
                           {
                               perror("Failed to listen\n");
                               exit(-1);
                           }

                           while(true)
                             {
                               sigflag = 0;

                               static int i=0;

                               // accept a waiting request

                                 if((/*this->sock = accept(this->p_sock, (struct sockaddr *)this->peer_addr4 ,&peer_size*/
                                    this->sock = accept(this->p_sock, (struct sockaddr*)NULL ,NULL))<0)
                                   {
                                       if(sigflag == 1)continue;
                                       perror("Accept error in server:");
                                       exit(-1);
                                   }


                                   if(this->deamon==PROCESS)
                                   {
                                       int childpid;

                                       if((childpid = fork()) < 0)
                                       {
                                           perror("Fork error in serveur:");
                                           exit(-1);
                                       }
                                       else if(childpid == 0)
                                       {

                                           close(this->p_sock);

                                           std::cout<<"hit"<<std::endl;

                                            // exit(0);
                                         (*communicator)(*this, vars);

                                       }
                                   }


                                   if(this->deamon==THREAD)
                                   {

                                   }
                                    close(this->sock);
                              }

                       }


                       if(this->prot==UDP)
                       {
                           int size=NULL;

                           std::stringstream udp_data;

                           udp_data.flush();

                           this->int_reader(&size);

                           char* data= this->str_reader(size);

                           udp_data<<data;
                        //   auto data_u;
                         //  udp_data>>auto data_u;

                           if(this->deamon==PROCESS)
                           {
                               int childpid;

                               if((childpid = fork()) < 0)
                               {
                                   perror("Fork error in serveur:");
                                   exit(-1);
                               }
                               else if(childpid == 0)
                               {
                                   std::cout<<"hit"<<std::endl;

                                     exit(0);
                                // (*communicator)(*this, vars);

                               }
                           }
                       }

      va_end(vars);

}







/*
inline std::stringstream server::ko()
{
    std::stringstream dol;

}
*/

/*
auto server::UDP_data()
{
    //auto data;
    this>>data;
    return data;
}

*/


server::~server()
{

    return;
}
