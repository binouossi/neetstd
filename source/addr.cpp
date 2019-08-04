#include "addr.h"


addr_h::addr_h(struct sockaddr_in6 lo)
{
 //   this->local._6=lo;
}

addr_h::addr_h(struct sockaddr_in lo)
{
    //this->local._4=lo;
    //typedef this->local._4. addr_h;

  //  (sockaddr_in)(*this->addr_);



    typedef struct sockaddr_in addr_h;
}

addr_h::addr_h()
{}

addr_h addr_h::operator=(struct sockaddr_in6 lo)
{
//    this->local._6=lo;
    return *this;
}


addr_h addr_h::operator=(struct sockaddr_in lo)
{
    //this->local._4=lo;
    return *this;
}

/*addr_h::addr_h(sin_family)
{

}

*/







