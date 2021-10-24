#include <iostream>

using namespace std;

// 最后接收一个空的‘包’
void Print()
{

}

template <class T, class... Types>
void Print(const T &first, const Types&... args)
{
    cout << first << endl;
    Print(args...);
}

int main()
{
    Print(1, 2, 3, "a", "b", "c", "abcd");
    return 0;
}
