#include "mammal.hh"
#include <iostream>

Mammal::Mammal() : Animal("Kip kop kip kop")
{

}
void Mammal::suckle(std::ostream& output) {
    output<< "Mus mus" << std::endl;
}
