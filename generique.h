
#ifndef GENERIQUE_H
#define GENERIQUE_H



#include<fstream>

#include <iostream>

#include<sstream>



struct con{
    std::string addr;
    int port;
    bool stat=false;
};

con nt_config(std::string config_f);

auto get_value(con&,bool&,std::istringstream&);




#endif // GENERIQUE_H
