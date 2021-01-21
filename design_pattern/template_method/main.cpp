#include <iostream>

#include "derivea.h"
#include "deriveb.h"


using namespace std;

int main()
{
    Base *a = new DeriveA;
    Base *b = new DeriveB;
    a->run();
    b->run();
    delete a;
    delete b;

    return 0;
}
