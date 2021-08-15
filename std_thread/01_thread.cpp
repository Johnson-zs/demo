#include <iostream>
#include <thread>
#include <string>

using namespace std;


void hello()
{
    cout << "hello" << endl;
}


void hello2(const string &name)
{
    cout << "hello" << name << endl;
}

int main()
{
    // basic
    thread t1(hello);
    t1.join();

    // lambda
    thread t2([]() {
        cout << "lambda" << endl;
    });
    t2.detach();

    // arguments
    thread t3(hello2, " thread!");
    t3.join();

    return 0;
}
