#include <iostream>
#include <functional>

using namespace std;

template <class T>
void hash_combine(size_t &seed, const T &val)
{
    seed ^= std::hash<T>()(val) + 0x9e3779b9
            + (seed << 6) + (seed >> 2);
}

// 3
template <class T>
void hash_val(size_t &seed, const T &val)
{
    hash_combine(seed, val);
}

// 2
template <class T, class... Types>
void hash_val(size_t &seed, const T &val, const Types&... args)
{
    hash_combine(seed, val);
    hash_val(seed, args...);
}

// 1
template <class... Types>
size_t hash_value(const Types&... args)
{
    size_t seed = 0;
    hash_val(seed, args...);
    return seed;
}

int main()
{
    cout << hash_value(std::string("abcef"), std::string("defg"), 123) << endl;
    return 0;
}
