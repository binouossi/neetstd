#include "server.h"


int sigflag;

int resquiescat(){wait(NULL);sigflag = 1;return 0;}


///constructor with a protocol argument set
server::server(char* conf, char* prot,void *(*communicator)(server, va_list&),  ...):net(conf, prot, true)
{
    this->deamon=PROCESS;

    va_list vars;
    va_start(vars,communicator);

                   if (bind(this->sock, this->local_addr->ai_addr, this->local_addr->ai_addrlen) < 0)
                   {

                       perror("bind error:");
                                 exit(-1);

                   }
                       sigset(SIGCHLD, (sighandler_t)resquiescat);


                //       std::cout<<"fine"<<std::endl;

                       if(this->prot==TCP)
                       {

                           //start listenning
                           if(listen(this->sock, 5) <0)
                           {
                               perror("Failed to listen\n");
                               exit(-1);
                           }

                             int tmp_sock=-1;
                           while(true)
                             {
                               sigflag = 0;

                               static int i=0;

                               // accept a waiting request

                               socklen_t t;
                               sockaddr_storage peer_tmp;
                               if(this->local_addr->ai_family==AF_INET)
                                     t=(socklen_t)sizeof(sockaddr_in);

                               if(this->local_addr->ai_family==AF_INET6)
                                     t=(socklen_t)sizeof(sockaddr_in6);

                                 if((tmp_sock = accept(this->sock, (struct sockaddr*)&peer_tmp ,
                                                         &t
                                   /* tmp_sock = accept(this->sock, (struct sockaddr*)NULL ,NULL*/))<0)
                                   {
                                       if(sigflag == 1)continue;
                                       perror("Accept error in server:");
                                       exit(-1);
                                   }

                                 //put peer information to addrinfo
                                 char host_str[NI_MAXHOST];
                                 char port_str[NI_MAXSERV];

                             //    sockaddr_storage *kit=&peer_tmp;
                                 int s;
                           //     kit->ss_family=this->local_addr->ai_family;
                                 if((s=getnameinfo((struct sockaddr*)&peer_tmp, sizeof(peer_tmp),host_str,
                                             NI_MAXHOST,port_str,NI_MAXSERV,NI_NUMERICSERV))!=0)
                                 {
                                          fprintf(stderr, "getnameinfo: %s\n", gai_strerror(s));
                                 }

                                 addrinfo hi;
                                 memset(&hi,0,sizeof(addrinfo));
                                 hi.ai_family=this->local_addr->ai_family;
                                 hi.ai_socktype=this->local_addr->ai_socktype;
                                 hi.ai_protocol = 0;          // Any protocol
                                 hi.ai_canonname = NULL;
                                 hi.ai_addr = NULL;
                                 hi.ai_next = NULL;
                                 hi.ai_flags = this->local_addr->ai_flags;

                                 ;

                                  if ((s=getaddrinfo(host_str, port_str, &hi, &this->peer_addr)) != 0)
                                  {
                                                 fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
                                         //        exit(EXIT_FAILURE);
                                  }

                                    //freeaddrinfo(&hi);

                                   if(this->deamon==PROCESS)
                                   {
                                       int childpid;

                  /*                     if((childpid = fork()) < 0)
                                       {
                                           perror("Fork error in serveur:");
                                           exit(-1);
                                       }
                                       else if(childpid == 0)
                                       {*/
                                           this->sock=tmp_sock;

                                //           close(this->p_sock);

                //                           std::cout<<"hit"<<std::endl;

                                         (*communicator)(*this, vars);

//                                       }
                                   }


                                   if(this->deamon==THREAD)
                                   {

                                   }
                                    //close(this->sock);
                              }

                       }


                       if(this->prot==UDP)
                       {

                           while(true)
                           {
                               /* int size=NULL;

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
                                    {*/
               //                         std::cout<<"hit"<<std::endl;

              //                            exit(0);
                                      (*communicator)(*this, vars);

     /*                               }
                                }

                                if(this->deamon==THREAD)
                                {

                                }*/
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
