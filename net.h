#ifndef NET_H
#define NET_H



#define OUTPUT stderr

#define THREAD 1
#define PROCESS 0

#define TCP 0
#define UDP 1

#define CONFIG "/etc/Face_client" //just for who those want to use a config file to manage server's information


#include <arpa/inet.h>
#include <unistd.h>
#include <fstream>
#include <string.h>
#include <sstream>
#include<iostream>
#include"generique.h"


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

    con configuration;

    struct sockaddr_in local_addr;

    struct sockaddr_in peer_addr;

    int sock;
    int prot;



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
