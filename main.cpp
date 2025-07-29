#include <iostream>
#include "Event.h"
int main() {
    //std::cout << "Hello, World!" << std::endl;


    unsigned int id;

    std::string titlu;
    std::string descriere;
    std::string data, ora;
    std::string locatie;

    std::cin>>id>>titlu>>descriere>>data>>ora>>locatie;

    Event eveniment(id,titlu, descriere, data, ora, locatie);

    eveniment.print();

    std::cout<<'\n'<<'\n'<<eveniment.toString();
    return 0;
}