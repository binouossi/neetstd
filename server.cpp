#include "server.h"

int sigflag;

int resquiescat(){wait(NULL);sigflag = 1;return 0;}

server::server(void (communicator)(server, va_list&), ...)
{
    int listenfd = 0;

    va_list vars;
    va_start(vars,communicator);

      struct sockaddr_in serv_addr;

      sigset(SIGCHLD, (sighandler_t)resquiescat);

      listenfd = socket(AF_INET, SOCK_STREAM, 0);// creation de la socket serveur
      printf("socket retrieve success\n");

      serv_addr.sin_family = AF_INET;
      serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
      serv_addr.sin_port = htons(PORT);

      if(bind(listenfd, (struct sockaddr*)&serv_addr,sizeof(serv_addr))<0)
      {// on attache la socket a l'address du serveur
          perror("Face_server bind fail");
          exit(1);
      }

      if(listen(listenfd, 10) == -1)
      {// starting listen
          perror("Failed to listen\n");
          exit(1);
      }

      while(1)
        {
          sigflag = 0;
          int childpid;
          // accept awaiting request
          this->sock = accept(listenfd, (struct sockaddr*)NULL ,NULL);
          if(this->sock<0)
          {
              if(sigflag == 1)continue;
              perror("accept error in Face_serverd");
              exit(1);
          }

          if((childpid = fork()) < 0)
          {
              perror("fork error in Face_serveurd");
              exit(1);
          }
          else if (childpid == 0)
          {
              close(listenfd);
            (*communicator)(*this, vars);
          }

          close(this->sock);
       }
      va_end(vars);
}

/*char* server::str_reader()
{

    int n = NULL;
    this->int_reader(&n);

    if(n==0||n==NULL)
    {
        return NULL;
    }

//    std::cout<<n<<std::endl;
    char lu[n];

//    lu=(char*)std::realloc(lu,(n*sizeof(char)));

    if(lu==NULL)
    {
        fprintf(OUTPUT,"Allocation error" , strerror(errno));

        return NULL;
    }

    lu[0]='\0';

//    int a=this->readLine(lu,n);

    int a=recv(this->sock,lu,n,0);

      if( a < n-1)
      {
          fprintf(OUTPUT,"Read Error" , strerror(errno));

        return NULL;
      }

      lu[n]='\0';
      return lu;
}

char* server::str_reader(int n)
{

    char* lu=NULL;

    if(n==0||n==NULL)
    {
        return NULL;
    }

    lu=(char*)std::realloc(lu,(n*sizeof(char)));

    if(lu==NULL)
    {
        fprintf(OUTPUT,"Allocation error" , strerror(errno));

        return NULL;
    }

    lu[0]='\0';

//    int a=this->readLine(lu,n);

    int a=recv(this->sock,lu,n,0);


      if( a < n-1)
      {

          fprintf(OUTPUT,"Read Error" , strerror(errno));

        return NULL;
      }

      lu[n]='\0';
      return lu;
}

int server::str_sender(char* fi)
{

    int a=strlen(fi);

    this->int_sender(strlen(fi));

    int n=send(this->sock,fi,a,0);

    if(n<0)
        perror("Error while sending");
    return n;
}

int server::str_sender(char* fi,int size)
{
    this->int_sender(size);

    int n=send( this->sock , fi , size, 0 );

    if(n<0)
        perror("Error while sending");
    return n;
}

int server::int_reader(int* num)
{
    char buf[10] = "";

    int rest=recv( this->sock , buf , sizeof buf , 0 );

    sscanf( buf , "%d" , num );

    return rest;
}

int server::int_sender(int num)
{
    char buf[10] = "";

    sprintf( buf , "%d" , num );

    int rest=send( this->sock , buf , sizeof buf , 0 );

    return rest;
}

int server::file_sender(char* path)
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

bool server::file_reader(char* destination)
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

char* server::getall()
{
    int size=NULL;

    this->int_reader(&size);

    if(size<=0)
    {
        return NULL;
    }

    char* data= this->str_reader(size);

    return data;
}







*/






/*


int server::stringsender(char fi[])
{
    int a=strlen(fi);

    this->send_int(a);

    int n=write(this->sock,fi,std::strlen(fi));

    if(n<0)
        std::cout<<"error while sending"<<std::endl;
    return n;
}


char* server::lire()
{

    int n = NULL;
    this->receive_int(&n);
//    this->receive_int(n);

    if(n==0||n==NULL)
    {
        return NULL;
    }

//    std::cout<<n<<std::endl;

    this->lu=(char*)std::realloc(this->lu,(n*sizeof(char)));

    if(this->lu==NULL)
    {
        std::cout<<"Allocation error"<<std::endl;
        return NULL;
    }

    this->lu[0]='\0';

    int a=this->readLine(this->lu,n);

      if( a < n-1)
      {
        cout<<"Read Error"<<endl;
        return NULL;
      }

      this->lu[n]='\0';
      return this->lu;
}

int server::send_int(int num)
{
    char buf[10] = "";

    sprintf( buf , "%d" , num );

    send( this->sock , buf , sizeof buf , 0 );

//    send(this->sock, &num, sizeof(int), 0);


    return 0;
}

int server::receive_int(int* num)
{
    char buf[10] = "";

    recv( sock , buf , sizeof buf , 0 );

    sscanf( buf , "%d" , num );


//    recv(this->sock, num, sizeof(int), NULL);

    return 0;
}

int server::readLine(char data[],int maxlen)
{
   size_t len = 0;
   while (len < maxlen)
   {
      char c;
      int ret = read(this->sock, &c, 1);
      if (ret < 0)
      {
          data[len] = 0;
          return len; // EOF reached
      }
      if (c == '\n')
      {
          data[len] = 0;
          return len; // EOF reached
      }
      data[len++] = c;
   }
}
*/
