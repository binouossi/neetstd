//#include<net.conf>

#include <netstd.h>

#include<iostream>

#include<stdio.h>

#include<stdlib.h>

using namespace std;



int main()
{
    client net("/etc/Face_client",TCP);

    string msg;
/*
    cout<<"Bienvenu dans votre application de Chart"<<endl
       <<"Veillez choisi votre Pseudo"<<endl;*/

 //   string pseudo;

//    cin>>msg;
//    cout<<msg<<endl;

   net>>msg;

    cout<<msg<<endl;

    net<<msg+" is online\n";

    cout<<"goodbye connard"<<endl;




//     getline(cin,msg);

//    cout<<(net>>msg)<<endl;

//   cout<<"Vous pouvez discuter "+msg<<endl;

/*    while(msg.compare("Quit$"))
    {
        cin.sync();

        getline(cin,msg);

        net<<msg;
    }*/

 //   cout<<(net>>msg)<<endl;

    return 0;
}


