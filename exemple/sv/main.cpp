#include<iostream>
#include <ntstd.h>

using namespace std;


void* A(server lo, va_list &y)
{
    static int i;
    i++;
    cout<<"Process "+i<<endl;

    string msg="gildas";

    lo<<msg;
    cout<<msg<<endl;

    lo>>msg;
    cout<<msg<<endl;;

//        cout<<(lo>>msg)<<endl;

        msg="good bye connard";

        lo<<msg;

//    cout<<(lo<<"good bye connard")<<endl;

    exit(0);
}

int main()
{
 //   cout<<"Bienvenu dans votre Serveur de Chart"<<endl;

    new server("/etc/Face_client",TCP,A);
    return 0;
}
