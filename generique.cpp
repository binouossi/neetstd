#include "generique.h"



using namespace std;

con nt_config(string conf)
{
    std::ifstream cfg(conf);

            con config;

    if(cfg.is_open())
    {
        string txt;

        bool addr=false;
        bool port=false;

        while(getline(cfg, txt))
        {
        istringstream line(txt);

          string key;

          if( getline(line, key, ' ') )
          {
             string value;
              if(key.find("ADDR")==0)
              {
                  if( getline(line, value) )
                  {
                    config.addr=value;
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
        if(addr&&port)
            config.stat=true;


        cfg.close();
    }
    else
        cout<<"configure probleme"<<endl;


    return config;
}



auto get_value(bool &ef, istringstream &is_line)
{
    std::string value;
    if( getline(is_line, value) )
    {
      ef=true;
      cout<<value<<endl;
    }
    return;
}
