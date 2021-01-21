#ifndef BASE_H
#define BASE_H

#include <iostream>

using namespace std;

class Base
{
public:
    Base();
    virtual ~Base();
    void run();

protected:
    void step1();
    virtual void step2() = 0;
    void step3();
};

#endif // BASE_H
