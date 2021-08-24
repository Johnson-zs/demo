#include <QApplication>

#include "testa/testa.h"
#include "testb/testb.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    TestA testa;
    TestB testb;

    testa.doSomething();

    return a.exec();
}
