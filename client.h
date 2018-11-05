#ifndef CLIENT_H
#define CLIENT_H


#define ADDR "127.0.0.1"
#define PORT 5000
#define CONFIG "/etc/Face_client" //just for who those want to use a config file to manage server's information

#include"net.h"

#include "netstd_server_global.h"

class NETSTDSHARED_EXPORT client : net
{

public:
    client();

    ~client();


//private:
  //  int sock;

protected:
    struct sockaddr_in serv_addr;

    std::string get_addr(char* path);

};
/*


template <typename Type>
std::stringstream& client::operator>> (Type& don)
{
    int size=NULL;

    std::stringstream nin;

    nin.flush();

    this->int_reader(&size);

    char* data= this->str_reader(size);

    nin<<data;

    nin>>don;

    return nin;
}

template <typename Type>
bool client::operator<<(Type &data)
{
    std::stringstream nout;

    nout<<data;

    char* buf=const_cast<char*>(nout.str().c_str());

    int size=strlen(buf);

    if(this->str_sender(buf,size)<0)
    {
        return false;
    }

    return true;
}


*/
#endif // CLIENT_H
