#ifndef CLIENT_H
#define CLIENT_H


#include"net.h"

#include "netstd_server_global.h"

class NTSTDSHARED_EXPORT client : public net
{

public:
    client(char* conf ,char* prot);

    ~client();

protected:

    std::string get_addr(char* path);

};

#endif // CLIENT_H
