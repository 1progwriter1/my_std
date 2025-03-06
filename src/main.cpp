#include <iostream>
#include "function.hpp"
#include <functional>

int factorial(int a)
{
    return (a <= 1) ? 1 : a * factorial(a - 1);
}

int main()
{
    my_std::function<int(int)> fact = factorial;
    my_std::function<int(int)> one_more = std::move(fact);

    std::cout << fact(5) << '\n';

    return 0;
}
