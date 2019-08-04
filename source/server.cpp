#include "server.h"


int sigflag;

int resquiescat(){wait(NULL);sigflag = 1;return 0;}


///constructor with a protocol argument set
server::server(std::string conf, std::string prot, void* (communicator)(server, va_list&),  ...):net(conf)
{
    this->prot=prot;
    this->deamon=PROCESS;
    this->ip=IPV4;

    va_list vars;
    va_start(vars,communicator);


    // ip version independant handle

    struct addrinfo hints;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;    // Allow IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM; // Datagram socket
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



                   if (bind(listenfd, rp->ai_addr, rp->ai_addrlen) == 0)
                   {
                       sigset(SIGCHLD, (sighandler_t)resquiescat);



                       if(this->prot==TCP)
                       {

                           //start listenning
                           if(listen(listenfd, 5) <0)
                           {
                               perror("Failed to listen\n");
                               exit(-1);
                           }

                           while(true)
                             {
                               sigflag = 0;

                               static int i=0;

                               // accept a waiting request

                                 if((/*this->sock = accept(listenfd, (struct sockaddr *)this->peer_addr4 ,&peer_size*/
                                    this->sock = accept(listenfd, (struct sockaddr*)NULL ,NULL))<0)
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

                                           close(listenfd);

                                           std::cout<<"hit"<<std::endl;

                      exit(0);
                                        // (*communicator)(*this, vars);

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

                       }



                   }


                   break;                  // Success

             //      close(listenfd);
     }

/*
    if (rp == NULL) {               // No address succeeded
                   fprintf(stderr, "Could not bind\n");
                   exit(EXIT_FAILURE);
               }




    //initialisation of local address
/*
    if(this->ip==IPV4)
    {
        sockaddr_in *tmp;
        memset(&tmp, 0, sizeof(struct sockaddr_in));


        tmp= (struct sockaddr_in*)&gi;
        tmp->sin_family=AF_INET; //familly set

        inet_pton(AF_INET,this->configuration.addr,&tmp->sin_addr); //address set

        tmp->sin_port=htons(this->configuration.port); //port set

//        this->local_addr.ss_family=AF_INET;

        this->local_addr=(sockaddr_storage*)memcpy(&gi,tmp,sizeof(*tmp));

  //      memcpy(&this->local_addr,tmp,sizeof(&tmp));


        delete &tmp;
    }

    if(this->ip==IPV6)
    {
        sockaddr_in6 *tmp;
        memset(&tmp, 0, sizeof(struct sockaddr_in));
        tmp->sin6_family=AF_INET6;
        inet_pton(AF_INET6,this->configuration.addr,&tmp->sin6_addr);
        tmp->sin6_port= htons(this->configuration.port);

        memcpy(&this->local_addr,tmp,sizeof(&tmp));

        delete &tmp;
    }

//    delete &gi;

//    std::cout<<std::length(va_list)<<std::endl;


 //   int listenfd = 0;
*/
 //     sigset(SIGCHLD, (sighandler_t)resquiescat);
/*
      if(prot==TCP)
      {// create a listinner socket for TCP connection
          if((listenfd = socket(//this->local_addr.ss_family
                                            AF_INET, SOCK_STREAM, 0))<0)
          {
              perror("socket error in serveur");
                        exit(-1);
          }
      }
*/
 /*     if(prot==UDP)
      {// create a socket for UDP connection
          //here, UDP dont need a listenner, cause it not connection oriented
          if((listenfd = socket(this->local_addr->ss_family, SOCK_DGRAM, 0))<0)
          {
              perror("socket error in serveur");
                        exit(-1);
          }
      }
*/

  /*

      if(this->ip==IPV4)
      {
          if(prot==TCP)
          {// create a listinner socket for TCP connection
              if((listenfd = socket(this->local_addr.ss_family, SOCK_STREAM, 0))<0)
              {
                  perror("socket error in serveur");
                            exit(-1);
              }
          }

          if(prot==UDP)
          {// create a socket for UDP connection
              //here, UDP dont need a listenner, cause it not connection oriented
              if((listenfd = socket(AF_INET, SOCK_DGRAM, 0))<0)
              {
                  perror("socket error in serveur");
                            exit(-1);
              }
          }
      }


      if(this->ip==IPV6)
      {
          if(prot==TCP)
          {// create a listinner socket for TCP connection
              if((listenfd = socket(AF_INET6, SOCK_STREAM, 0))<0)
              {
                  perror("socket error in serveur");
                            exit(-1);
              }
          }

          if(prot==UDP)
          {// create a socket for UDP connection
              //here, UDP dont need a listenner, cause it not connection oriented
              if((listenfd = socket(AF_INET6, SOCK_DGRAM, 0))<0)
              {
                  perror("socket error in serveur");
                            exit(-1);
              }
          }
      }

*/


      /*
     //Listenning information set
      struct sockaddr_in tmp;
      tmp.sin_family = AF_INET; //IPV4
      tmp.sin_port = htons(this->configuration.port); // connection port
 //     tmp.sin_addr = INADDR_ANY; //any address
//      this->listen_addr=tmp;
      delete &tmp;
*/

/*
      inet_pton(AF_INET,this->configuration.addr,&this->local_addr4.sin_addr);
      this->local_addr4.sin_port =htons(this->configuration.port);
      this->local_addr4.sin_family=AF_INET;


      //bind listenner socket to address and port
      if(bind(listenfd, (struct sockaddr*)&this->local_addr4,sizeof(this->local_addr4))<0)
      {
          perror("server bind fail");
          exit(-1);
      }


*/
      //This var_list to handle the argument passed to server routine



/*

      va_list vars;
      va_start(vars,communicator);

      if(this->prot==TCP)
      {

          //start listenning
          if(listen(listenfd, 5) <0)
          {
              perror("Failed to listen\n");
              exit(-1);
          }

*/

 //         socklen_t peer_size=sizeof(this->peer_addr4);
/*
          while(true)
            {
              sigflag = 0;

              static int i=0;

              // accept a waiting request
              if(this->ip==IPV4)
                if((//this->sock = accept(listenfd, (struct sockaddr *)this->peer_addr4 ,&peer_size
                   this->sock = accept(listenfd, (struct sockaddr*)NULL ,NULL))<0)
                  {
                      if(sigflag == 1)continue;
                      perror("Accept error in server:");
                      exit(-1);
                  }
 /*             if(this->ip==IPV6)
                if((//this->sock = accept(listenfd, (struct sockaddr*)&this->peer_addr ,&peer_size
                   this->sock = accept(listenfd, (struct sockaddr*)NULL ,NULL))<0)
                  {
                      if(sigflag == 1)continue;
                      perror("Accept error in server:");
                      exit(-1);
                  }
*/

    /*

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


                   close(this->sock);
              }
              else if(this->deamon==THREAD)
              {
       //           std::vector<pthread_t> threads(10);

    //              pthread_create(&threads[i], NULL,(communicator)(*this, vars), NULL);

    //              pthread_join(threads[i], NULL);
                  i++;
              }
           }


      }


      if(this->prot==UDP)
      {// Here, there no kids process that is need
          // UDP is a locking process
          //This socket is used to communicate directly with clients
          this->sock=listenfd;

 //         nin.flush();


//          this->UDP_data.flush();


  //        (*communicator)(*this, vars);

            close(this->sock);
      }
*/

      va_end(vars);

}

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
