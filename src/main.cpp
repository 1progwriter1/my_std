#include <iostream>
#include "function.hpp"
#include <functional>

int factorial(int a)
{
    return (a <= 1) ? 1 : a * factorial(a - 1);
}

class RandomFunctor
{
public:
    RandomFunctor() {std::srand(time(nullptr));}
    int operator()()
    {
        return std::rand();
    }
};

int main()
{
    my_std::function<int(int)> fact = factorial;
    my_std::function<int(int)> one_more(fact);

    int res = one_more(5) % 10;
    my_std::function<int(int)> another = [&res](int a)
    {
        res = 1;
        return a * res;
    };
    std::cout << another(10) << ' ' << res << '\n';

    my_std::function<int()> rand_func = RandomFunctor();
    another = one_more;


    std::cout << one_more(5) << ' ' << fact(5) << ' ' << rand_func() << ' ' << another(4) << '\n';

    return 0;
}
