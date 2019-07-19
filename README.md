# ntstd

## c/c++ socket client/server library

### Author
**NAME: _TACOLODJOU Emmanuel_**
**Email: _tacolodjounini@gmail.com_**


## Presentation

This is a c++ library that content server and client class, which makes the utilization of socket easiest to be use. It contains the **class** to initiate communication and methods and operator to send and receive data, over the network. This library is make to be use as external library.



## Usage

To use this library, you just have to install the library and include our header file ntstd.h in your project. Something that is very needed for this library is the configuration file. The configuration file has to content some configuration option for the server or client.

## Configuration file

#### Configuration file synthase

ATTRIBUT value
EX: ADDR 127.0.0.1


* ###  Server
* ADDR option to set tu which address to bind the socket. The 0.0.0.0 is the default. On this, it wait for any connection


* PORT option to specifie on which port to listen


* ### Client

* ADDR option to set the server address. It the address to which the client will be connected. It will make the connection using the actuel of the server.


* PORT option to specifie which port is used to connect to the server


## Fonction and Methode

* ###     server(std::string conf,int prot,void *(*communicator)(server, va_list&), ...)

It create the socket, bind it, and listeen to request from client. It waiting for _any_ address to connect on default configuration. And the listen port are set up on Configuration file **PORT** defined variable. It take as parameter:
* The configuration file absolut path
* The second parameter is the protocol type use by the socket. It can be **TCP** or **UDP**. The value are defined on the library as preprocessing variable. But the default configuration is set to use TCP if no option is provided
* The third parameter is a fontion that is forcked on each process by the server. This fonction will be execute as the rotine. That _routine_ function have to receve a server object as parameters. The routine must return a **void** and can not take other parameters, than the server objet. If you need to send some parameters to the routine, you have a **var_list** that is send to the routine.
* The last argument, is a **var_list**. You can put on, all argument you want to send to the routine. 




* ### client(std::string conf ,int prot)

It create the socket, and connect it to the server. The server address and connection port can be set up on the **configuration file**.



### Operators

Thoses operator for client and server.


* ## template \<typename Type> std::string net::operator>> (Type& don)
{

This operator is similar to the standard output stream operator. It allows you to send data other the network. you could watch it as a network output stream. It allow you to send any type of data.

* ## template \<typename Type> std::string net::operator<<(Type data)

This operator is similar to the standard input stream operator. It allows you to receive data from the network. It allow you to receive any type of data.


## Version (0.001)
This is the beta version

# Licence

This library, is offert as **LGPL Licence**. Than, it's free usefull and shareless. You can sell a software maked with the library.

## Invitation

I invite everyone, to help me, in the development of this class, by sending feedback, and by proposing better algorithms.



