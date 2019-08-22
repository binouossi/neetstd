#include "client.h"


client::client(char* conf, char* prot):net(conf, prot, false)
{

//    this->sock=this->p_sock;

    if(this->prot==TCP)
    {
        //this->local_addr= this->local_i_addr;
          if(connect(this->sock, this->peer_addr->ai_addr, this->peer_addr->ai_addrlen)<0)
            {
              perror("Error : Connect Failed");
              exit(-1);
            }
    }

    if(this->prot==UDP)
    {
        addrinfo hi;

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
//        std::fprintf(OUTPUT,"connection ended\n" , strerror(errno));

    }

}

