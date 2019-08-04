#include "generique.h"

using namespace std;


con config_reader(string conf)
{

    std::ifstream cfg(conf);

    //struct that will conten file data
     con config;

     //open the config file
    if(cfg.is_open())
    {
        string txt;

        //those variable is called the control variables
        // there are one for each variable that is read from file ans is initialized to false
        bool addr=false;
        bool port=false;

        //read each line from file
        while(getline(cfg, txt))
        {
        istringstream line(txt);

          string key;

          //on the considered config file the ' ' act as the separator
          //it can be any other character
          // the  line key is read firstly
          if( getline(line, key, ' ') )
          {
             string value;
             //the readed key is tested with wished key from file
              if(key.find("ADDR")==0)
              {//if so, get key value and put it on the config container
                  if( getline(line, value) )
                  {
                    config.addr=strdup(value.c_str());
                    //pass this parameter controler to true;
                    addr=true;
                  }
              }

              if(key.find("PORT")==0)
              {
                  if( getline(line, value) )
                  {
                      stringstream ki(value);
                    ki>>config.port;
                    port=true;
                  }
              }
          }

        }
        //check if all data has been collected
        // and pass data controler to true if all right
        if(addr&&port)
            config.stat=true;

        //close config file
        cfg.close();
    }
    else
        cout<<"configure probleme"<<endl;


    return config;
}



void config_reader(string conf, auto &config)
{

    std::ifstream cfg(conf);

    //struct that will conten file data

     //open the config file
    if(cfg.is_open())
    {
        string txt;

        //those variable is called the control variables
        // there are one for each variable that is read from file ans is initialized to false
        bool addr=false;
        bool port=false;

        //read each line from file
        while(getline(cfg, txt))
        {
        istringstream line(txt);

          string key;

          //on the considered config file the ' ' act as the separator
          //it can be any other character
          // the  line key is read firstly
          if( getline(line, key, ' ') )
          {
             string value;
             //the readed key is tested with wished key from file
              if(key.find("ADDR")==0)
              {//if so, get key value and put it on the config container
                  if( getline(line, value) )
                  {
                    config.addr=strdup(value.c_str());
                    //pass this parameter controler to true;
                    addr=true;
                  }
              }

              if(key.find("PORT")==0)
              {
                  if( getline(line, value) )
                  {
                      stringstream ki(value);
                    ki>>config.port;
                    port=true;
                  }
              }
          }

        }
        //check if all data has been collected
        // and pass data controler to true if all right
        if(addr&&port)
            config.stat=true;

        //close config file
        cfg.close();
    }
    else
        cout<<"configure probleme"<<endl;
    return;
}

void value_reader(std::string path,std::string key,auto &valu)
{
    std::ifstream cfg(path);

    //struct that will conten file data

     //open the config file
    if(cfg.is_open())
    {
        string txt;

        //those variable is called the control variables
        // there are one for each variable that is read from file ans is initialized to false
        bool addr=false;

        //read each line from file
        while(getline(cfg, txt))
        {
        istringstream line(txt);

          string key;

          //on the considered config file the ' ' act as the separator
          //it can be any other character
          // the  line key is read firstly
          if( getline(line, key, ' ') )
          {
             string value;
             //the readed key is tested with wished key from file
              if(key.find(key)==0)
              {//if so, get key value and put it on the config container
                  if( getline(line, value) )
                  {
                    valu=strdup(value.c_str());
                    //pass this parameter controler to true;
                    addr=true;
                  }
              }

          }

        }


        //close config file
        cfg.close();
    }
    else
        cout<<"configure probleme"<<endl;
    return;
}




// not used
static auto get_value(bool &ef, istringstream &is_line)
{
    std::string value;
    if( getline(is_line, value) )
    {
      ef=true;
      cout<<value<<endl;
    }
    return;
}
