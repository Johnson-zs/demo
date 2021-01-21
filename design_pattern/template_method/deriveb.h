#ifndef DERIVEB_H
#define DERIVEB_H

#include "base.h"

class DeriveB : public Base
{
public:
    DeriveB();

protected:
    void step2() override;
};

#endif // DERIVEB_H
