#ifndef DERIVEA_H
#define DERIVEA_H

#include "base.h"

class DeriveA : public Base
{
public:
    DeriveA();

protected:
    void step2() override;
};

#endif // DERIVEA_H
