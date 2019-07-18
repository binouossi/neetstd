#include "net.h"



net::net(std::string conf)
{
    this->configuration=nt_config(conf);
}

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
            int len;
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

