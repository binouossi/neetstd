#ifndef NETSTD_SERVER_H
#define NETSTD_SERVER_H

constexpr int THREAD = 1;
constexpr int PROCESS = 0;

// labrary
#include <stdarg.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <mutex>
#include <vector>
#include <wait.h>
#include <sstream>



#include "net.h"

#include "netstd_server_global.h"

class NTSTDSHARED_EXPORT server : public net
{

public:
    server(char* conf, char* prot, void *(*communicator)(server, va_list&), ...);

//    server(char* conf, char* prot, int deamon, void *(*communicator)(server, va_list&), ...);

//    server(char* conf, int deamon, void *(*communicator)(server, va_list&), ...);

//    server(char* conf, void *(*communicator)(server, va_list&), ...);

    ~server();

private:
    int deamon;
 //  struct sockaddr_storage  listen_addr;
//   char* service_name;

//    std::stringstream udp_data;

protected:

//    const struct sockaddr_in* addr;



};

#endif // NETSTD_SERVER_H
