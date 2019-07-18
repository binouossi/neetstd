#include "server.h"


int sigflag;

int resquiescat(){wait(NULL);sigflag = 1;}

server::server(std::string conf, int prot,void* (communicator)(server, va_list&), ...):net(conf)
{
    this->prot=prot;
    this->deamon=PROCESS;

//    std::cout<<std::length(va_list)<<std::endl;

    int listenfd = 0;

      struct sockaddr_in serv_addr;

      sigset(SIGCHLD, (sighandler_t)resquiescat);

     if((listenfd = socket(AF_INET, SOCK_STREAM, 0))<0) // creation de la socket serveur
     {
         perror("socket error in serveur");
                   exit(-1);
     }
     
      serv_addr.sin_family = AF_INET;
      serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
      serv_addr.sin_port = htons(this->configuration.port);

      if(bind(listenfd, (struct sockaddr*)&serv_addr,sizeof(serv_addr))<0)
      {
          // on attache la socket a l'address du serveur
          perror("server bind fail");
          exit(-1);
      }

      if(listen(listenfd, 10) <0)
      {// starting listen
          perror("Failed to listen\n");
          exit(-1);
      }

      va_list vars;
      va_start(vars,communicator);

      while(true)
        {

          sigflag = 0;

          static int i=0;

          // accept awaiting request
          if((this->sock = accept(listenfd, (struct sockaddr*)NULL ,NULL))<0)
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
              else if(childpid == 0){

                (*communicator)(*this, vars);

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
      va_end(vars);

}


server::~server()
{

    return;
}
