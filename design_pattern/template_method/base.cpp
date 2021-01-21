#include "base.h"


Base::Base()
{

}

Base::~Base()
{

}

void Base::run()
{
    step1();
    step2();
    step3();
}

void Base::step1()
{
    cout << __FUNCTION__ << endl;
}

void Base::step3()
{
    cout << __FUNCTION__ << endl;
}
