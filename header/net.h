#ifndef NET_H
#define NET_H



#define OUTPUT stderr

constexpr int IPV4 = 4;
constexpr int IPV6 = 6;
constexpr int _4_6 = 46;


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

#include<string>



//local header

//#include"addr.h"
#include"generique.h"

/*
typedef enum family{
    ipv4=4,
    ipv6=6
}family;
*/
/*template <class charT,
class traits = char_traits<charT>,
class Allocator = allocator<charT> >*/

//template <typename _CharT, typename _Traits, typename _Alloc>
class net //: protected std::stringstream
{
public:

    net(char*, char*, bool);
    ~net();
 //   template <typename Type>
 //   std::string operator<<(Type data);

    template <typename Type>
    std::stringstream operator>>(Type& data);

    template <typename Type>
    std::stringstream operator<<(Type& data);

//    template <class charT, class Traits>
//    std::basic_iostream<charT, Traits> &operator<<(
//    std::basic_iostream<charT, Traits> &flux);


    void config_set(char*,char*, char*);



protected:

    char* str_reader();

    char* str_reader(int size);

    int int_reader(int *num);

    int int_sender(int num);

    int str_sender(char *fi);

    auto get_addr_l();//return address usefull for socket struct

//    struct addrinfo *local_addr;

    // bool server;

    con configuration;

    char ip_v;



    //addr
    struct addrinfo *peer_addr;
    struct addrinfo *local_addr;


 //   int p_sock;


//ipv4 address
 //  struct sockaddr_in local_addr4;

  //  struct sockaddr_in peer_addr4;

    //ipv6 address
 //   struct sockaddr_in6 local_addr6;

//    struct sockaddr_in6 peer_addr6;



    int sock;

    std::string prot;



private:

    char* getall();

    int file_sender(char* path);

    bool file_reader(char* destination);

    std::string get_addr(char* path);

    int str_sender(char* fi, int size);

    int unit_data_sender(int q, char* buf);

};



// network communication operator

/*
template <class charT, class Traits>
std::basic_iostream<charT, Traits> &net::operator<<(
std::basic_iostream<charT, Traits> &flux)
{
    // Inialisation du flux de sortie :
    typename std::basic_iostream<charT, Traits>::sentry init(flux);
    if (init)
    {
    // Écriture des données :
//        int Metres = p.Taille / 100;
  //      int Reste = p.Taille % 100;
    //    flux << p.Prenom << " " << p.Nom <<
      //  " mesure " << Metres <<
        //"m" << Reste << " (" <<
 //       p.Age << " an";
   //     if (p.Age > 1) flux << "s";
     //   flux << ")";

        char* buf=strdup(flux.str().c_str());

        int size=strlen(buf);

    //    std::cout<<buf<<std::endl;

        if(this->str_sender(buf,size)<0)
        {
          //  buf=NULL;
          //  return buf;
        }


    }
    return flux;
}
*/





template <typename Type>
std::stringstream net::operator>> (Type& don)
{
    int tour=0;

    std::stringstream nin;

    nin.flush();

    char* data_tmp;

    this->int_reader(&tour);

    for(int i=0; i<tour; i++)
    {
        data_tmp=this->str_reader(BUFFER_SIZE);
//        std::cout<<data_tmp<<std::endl;
        nin<<data_tmp;
    }

 //   char* data= this->str_reader(size);

//    std::cout<<data<<std::endl;

//    nin<<data;

    strchr(data_tmp,' ')==NULL ? nin>>don : getline(nin,don);

    nin>>don;

//    std::cout<<don<<std::endl;

    return nin;
}


template <typename Type>
std::stringstream net::operator<<(Type& data)
{
    std::stringstream nout(data);

//    nout<<data;

    char* buf=const_cast<char*>(nout.str().c_str());

    int size=strlen(buf);
    int t=0, j=0;

    t=(int)(size%BUFFER_SIZE==0 ? size/BUFFER_SIZE : (size/BUFFER_SIZE)+1);

    int_sender(t);


    char tmp[BUFFER_SIZE];

    if(int(size/BUFFER_SIZE)>0)
    {
        for(int i=0;i<t;i++)
        {
            for(int k=0;k<=BUFFER_SIZE;k++)
            {
                tmp[k]=buf[j];
                j++;
            }
            int y=sizeof(tmp);
            this->str_sender(tmp,y);
        }
    }


    int y=size%BUFFER_SIZE;
    char tm[y];

    for(int k=0;k<=y;k++)
    {
        tm[k]=buf[j];
        j++;
    }

    this->str_sender(tm,y);

    return nout;
}





#endif // NET_H
