
#ifndef GENERIQUE_H
#define GENERIQUE_H



#include<fstream>

#include <iostream>

#include<sstream>

#include<string.h>



// this struct content the values that will be read from configuration file
// it will be customized deppending on the demmands of parameters that
// will be read from config file
// Note that the stat here is to determine if  the operation has been done.
// it act as operation control variable

struct con{
    char* addr=NULL;
    char* port=NULL;
    bool stat=false;
};

// this function return the readed data struct
// It take the config file absolut path as parameter
con config_reader(std::string path);

void config_reader(std::string conf, auto &config);

auto get_value(con&,bool&,std::istringstream&);

void value_reader(std::string path,std::string key,auto &valu);


#endif // GENERIQUE_H
