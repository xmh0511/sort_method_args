#include <iostream>
#include "sort_type.hpp"
template<typename...Args>
auto func(Args...args)
{
    auto res = sort_args_help(std::tuple<int,char,double>(),std::tuple<Args...>(args...));
    show_tuple(res);
}

int main()
{
    func(2.01,'c');
    return 0;
}