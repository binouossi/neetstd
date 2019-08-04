#ifndef NET_H
#define NET_H



#define OUTPUT stderr

constexpr int IPV4 = 4;
constexpr int IPV6 = 6;

constexpr char* TCP = "TCP";
constexpr char* UDP = "UDP";




//library list

#include <arpa/inet.h>
#include <unistd.h>
#include <fstream>
#include <string.h>
#include <sstream>
#include<iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>



//local header

#include"addr.h"
#include"generique.h"


typedef enum family{
    ipv4=4,
    ipv6=6
}family;

class net// : public istringstream
{
public:

    net(std::string);
    template <typename Type>
    std::string operator<<(Type data);

    template <typename Type>
    std::string operator>>(Type& data);



protected:

    char* str_reader();

    char* str_reader(int size);

    int int_reader(int *num);

    int int_sender(int num);

    int str_sender(char *fi);

    auto get_addr_l();//return address usefull for socket struct


    con configuration;

    char ip;

    //addr
    sockaddr_storage *peer_addr;
    sockaddr_storage *local_addr;


//ipv4 address
   struct sockaddr_in local_addr4;

    struct sockaddr_in peer_addr4;

    //ipv6 address
    struct sockaddr_in6 local_addr6;

    struct sockaddr_in6 peer_addr6;



    int sock;
    std::string prot;



private:

    char* getall();

    int file_sender(char* path);

    bool file_reader(char* destination);

    std::string get_addr(char* path);

    int str_sender(char* fi, int size);




};



template <typename Type>
std::string net::operator>> (Type& don)
{
    int size=NULL;

    std::stringstream nin;

    nin.flush();

    this->int_reader(&size);

    char* data= this->str_reader(size);

//    std::cout<<data<<std::endl;

    nin<<data;

    nin>>don;

    return nin.str();
}


template <typename Type>
std::string net::operator<<(Type data)
{
    std::stringstream nout;

    nout<<data;

    char* buf=const_cast<char*>(nout.str().c_str());

    int size=strlen(buf);

    std::cout<<buf<<std::endl;

    if(this->str_sender(buf,size)<0)
    {
        buf=NULL;
        return buf;
    }

    return buf;
}



#endif // NET_H
