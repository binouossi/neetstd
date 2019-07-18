#ifndef NETSTD_SERVER_H
#define NETSTD_SERVER_H

#define THREAD 1
#define PROCESS 0

// labrary
#include <stdarg.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <mutex>
#include <vector>
#include <wait.h>

#include "net.h"

#include "netstd_server_global.h"

class NETSTDSHARED_EXPORT server : public net
{

public:
    server(std::string conf,int prot,void *(*communicator)(server, va_list&), ...);

    ~server();

private:
    int deamon;

protected:

    const struct sockaddr_in* addr;



};

#endif // NETSTD_SERVER_H
