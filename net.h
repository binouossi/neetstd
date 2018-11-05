#ifndef NET_H
#define NET_H

#define OUTPUT stderr

#include <arpa/inet.h>
#include <unistd.h>
#include <fstream>
#include <string.h>
#include <sstream>

class net
{
public:

    template <typename Type>
    bool operator<<(Type &data);

    template <typename Type>
    std::stringstream& operator>>(Type &data);



protected:

    char* str_reader();

    char* str_reader(int size);

    int int_reader(int *num);

    int int_sender(int num);

    int str_sender(char *fi);

    int sock;



private:

    char* getall();

    int file_sender(char* path);

    bool file_reader(char* destination);

    std::string get_addr(char* path);

    int str_sender(char* fi, int size);

};



template <typename Type>
std::stringstream& net::operator>> (Type& don)
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
bool net::operator<<(Type &data)
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



#endif // NET_H
