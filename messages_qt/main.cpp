#include <QApplication>
#include <QPointer>

#include "testa/testa.h"
#include "testb/testb.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    TestA testa;
    TestB testb;
    testb.subMessage("test_id");
    testa.doSomething();

    TestA *abc = new TestA;
    QPointer p(abc);
    auto t = p.isNull();
    delete abc;
    t = p.isNull();

    return a.exec();
}
