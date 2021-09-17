#include <QApplication>
#include <QPointer>
#include <QDebug>
#include <QThread>

#include "message.h"
#include "testa/testa.h"
#include "testb/testb.h"

#include <malloc.h>

static TestA testa;

void test_send()
{
    TestB b;
    message::Receiver r("test_id");
    r.bind(&b, &TestB::testSlot);
    testa.sync();
}

void test_destruct()
{
    TestB b;
    {
    message::Receiver r("test_id");
    r.bind(&b, &TestB::testSlot);
    }
    testa.sync();
}

void test_rebind()
{
    TestB b;
    message::Receiver r("test_id");
    r.bind(&b, &TestB::testSlot);
    r.rebind(&b, &TestB::testSlot1);
    testa.sync();
}

void test_obj_destruct()
{
    message::Receiver r("test_id");
    TestB *b = new TestB;
    r.bind(b, &TestB::testSlot);
    delete b;
    testa.sync();
}

void test_sig()
{
    message::Receiver r("test_id");
    TestB *b = new TestB;
    r.bind(b, &TestB::testSig);
    testa.sync();
}

void test_async_send()
{
    qDebug() << QThread::currentThreadId();
    TestB b;
    message::Receiver r("test_id");
    r.bind(&b, &TestB::testSlot);
    r.rebind(&b, &TestB::testSlot1);
    testa.async();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    test_send();
    test_destruct();
    test_rebind();
    test_obj_destruct();
    test_sig();
    test_async_send();

    return a.exec();
}
