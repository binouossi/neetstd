#include "client.h"


client::client()
{

      if((this->sock = socket(AF_INET, SOCK_STREAM, 0))< 0)
        {
          perror("Error : Could not create socket \n");
        }
      this->serv_addr.sin_family = AF_INET;
      this->serv_addr.sin_port = htons(PORT);
      serv_addr.sin_addr.s_addr = inet_addr( ADDR);

/* to read address from file
      const char* addr;
      ADDR=this->getaddr(CONFIG).c_str();
      this->serv_addr.sin_addr.s_addr = inet_addr(addr);*/

      if(connect(this->sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0)
        {
          perror("Error : Connect Failed");
          exit(1);
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
}

client::~client()
{
    if(close(this->sock)==0)
    {
        std::fprintf(OUTPUT,"connection ended\n" , strerror(errno));

    }

}

