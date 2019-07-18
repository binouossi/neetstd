#include "client.h"


client::client(std::string conf, int prot=TCP):net(conf)
{
    this->prot=prot;

    if(this->prot==TCP)
    {

      if((this->sock = socket(AF_INET, SOCK_STREAM, 0))< 0)
        {
          perror("Error : Could not create socket \n");
        }
    }else
        if(this->prot==UDP)
        {
            if((this->sock = socket(AF_INET, SOCK_DGRAM, 0))< 0)
              {
                perror("Error : Could not create socket \n");
              }
        }

      this->peer_addr.sin_family = AF_INET;
      this->peer_addr.sin_port = htons(PORT);
     this->peer_addr.sin_addr.s_addr = inet_addr( ADDR);


      if(connect(this->sock, (struct sockaddr *)&this->peer_addr, sizeof(this->peer_addr))<0)
        {
          perror("Error : Connect Failed");
          exit(-1);
        }


}

std::string client::get_addr(char* path)
{
        std::ifstream monFlux(path);
        if(monFlux)
        {
            std::string ligne;
            std::getline(monFlux, ligne);
            return ligne;
        }
        else
        {
            fprintf(stderr,"ERREUR: Impossible d'ouvrir le fichier de configuration.");
            exit(1);
        }

    return '\0';
}

client::~client()
{
    if(close(this->sock)==0)
    {
        std::fprintf(OUTPUT,"connection ended\n" , strerror(errno));

    }

}

