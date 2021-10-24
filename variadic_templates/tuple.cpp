#include <iostream>

using namespace std;

template <class... Values> class Tuple;
template <> class Tuple<> {};

template <class Head, class... Tail>
class Tuple<Head, Tail...>
        : private Tuple<Tail...>
{
    using Inherited = Tuple<Tail...>;
public:
    Tuple() {}
    Tuple(const Head &v, const Tail&... vtail)
        : Inherited(vtail...), head_(v)
    {

    }

    Head head() { return head_; }
    Inherited &tail() { return *this; }

protected:
    Head head_;
};

int main()
{
    Tuple<int, double, string> t(1, 3.14, "hello");
    cout << t.head() << endl;
    cout << t.tail().head() << endl;
    cout << t.tail().tail().head() << endl;

    return 0;
}
