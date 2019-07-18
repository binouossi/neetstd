#ifndef CLIENT_H
#define CLIENT_H


#define ADDR "127.0.0.1"
#define PORT 5000

#include"net.h"

#include "netstd_server_global.h"

class NETSTDSHARED_EXPORT client : public net
{

public:
    client(std::string conf ,int prot);

    ~client();

protected:

    std::string get_addr(char* path);

};

#endif // CLIENT_H
