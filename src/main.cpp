#include <iostream>
#include "function.hpp"
#include <functional>

int factorial(int a)
{
    return (a <= 1) ? 1 : a * factorial(a - 1);
}

int sum(int a, int b)
{
    return a + b;
}

class RandomFunctor
{
public:
    RandomFunctor() { std::srand(time(nullptr)); }
    int operator()()
    {
        return std::rand();
    }
};

struct Foo
{
    Foo(int num) : num_(num) {}
    void print_add(int i) const { std::cout << num_ + i << '\n'; }
    int num_;
};

int main()
{
    my_std::function<int(int)> fact = factorial;
    std::function<int(int)> std_fact = factorial;

    my_std::function<int(int)> one_more(fact);
    std::function<int(int)> std_one_more(fact);

    my_std::function<int(int, int)> sum_of_two(sum);
    std::function<int(int, int)> std_sum_of_two(sum);

    int res = one_more(5) % 10;

    my_std::function<int()> func(std::nullptr_t);
    std::function<int()> std_func(std::nullptr_t);

    my_std::function<int(int)> another = [&res](int a)
    {
        res = 1;
        return a * res;
    };
    std::cout << another(10) << ' ' << res << '\n';

    my_std::function<int()> rand_func = RandomFunctor();
    another = one_more;

    std::cout << one_more(5) << ' ' << fact(5) << ' ' << rand_func() << ' ' << another(4) << '\n';

//     my_std::function<void(const Foo *, int)> f_add_display = &Foo::print_add;
//
//
//     Foo foo(10);
//     f_add_display(&foo, 5);

    return 0;
}
