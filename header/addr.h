#ifndef ADDR_H
#define ADDR_H

#include<netinet/in.h>


//#define ip(type)

/*



#define IPV6_REST( hi ) \
 //   hi==AF_INET6? : uint32_t sin6_flowinfo \ 	// IPv6 flow information
 //   &&       uint32_t sin6_scope_id;	/* IPv6 scope-id ;
/*
#define IPV6_REST( hi )\
        hi == AF_INET6 ?  :
        uint32_t sin6_flowinfo;	// IPv6 flow information
 //       uint32_t sin6_scope_id;	// IPv6 scope-id



/*
typedef union addr_
{
    struct sockaddr_in6  _6;
    struct sockaddr_in  _4;
} addr_;



class addr_h
{
public:
    addr_h(struct sockaddr_in6);
    addr_h(struct sockaddr_in);
    addr_h();
    addr_h operator=(struct sockaddr_in6 lo);
    addr_h operator=(struct sockaddr_in lo);


private:
 //   addr_ addr; //addr contener

//    sin_ sin;

//    in_port_t &sin_port;    //port number


    typedef union addr_
    {
        struct sockaddr_in6 addr_6;
        struct sockaddr_in  addr_4;
    } addr_;



    typedef union sin_
    {
        __SOCKADDR_COMMON (sin_);
        __SOCKADDR_COMMON (sin6_);
    }sin_;





    //ipv4
 //   __SOCKADDR_COMMON (sin_);
//    in_port_t sin_port;			// Port number.
//    struct in_addr sin_addr;		// Internet address.

    // Pad to size of `struct sockaddr'.  //
  //  unsigned char sin_zero[sizeof (struct sockaddr) -
               __SOCKADDR_COMMON_SIZE -
               sizeof (in_port_t) -
               sizeof (struct in_addr)];


    IPV6_REST(sin)

//sockaddr_storage.

//ipv6

//    __SOCKADDR_COMMON (sin6_);
//    in_port_t sin6_port;	// Transport layer port #
//    struct in6_addr sin6_addr;	// IPv6 address

//    uint32_t sin6_flowinfo;	// IPv6 flow information
//    uint32_t sin6_scope_id;	// IPv6 scope-id




};
*/
#endif // ADDR_H
