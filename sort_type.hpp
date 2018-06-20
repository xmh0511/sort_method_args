//
// Created by dy2018 on 18-6-20.
//

#ifndef UNTITLED42_SORT_TYPE_HPP
#define UNTITLED42_SORT_TYPE_HPP
#include <tuple>
struct void_type
{
    using element_type = void_type;
    static const int element_index= -1;
};
template<int index,typename T,typename...Args>
struct Find_Type
{
    using type = void_type;
};
template<int index,typename T,typename U,typename...Args>
struct Find_Type<index,T,U,Args...>
{
    using type = typename Find_Type<index+1,T,Args...>::type;
};

template<int index,typename T,typename...Args>
struct Find_Type<index,T,T,Args...>
{
    using type = Find_Type;
    using element_type = T;
    static const int element_index= index;
};
template<typename T>
struct is_void_type
{
    static const bool value = false;
};
template<>
struct is_void_type<void_type>
{
    static const bool value = true;
};
template<int N,typename U,typename T,typename Tuple>
typename std::enable_if<!is_void_type<T>::value,T>::type get_index_value(Tuple&& tup)
{
    return std::get<N>(tup);
};
template<int N,typename U,typename T,typename Tuple>
typename std::enable_if<is_void_type<T>::value,U>::type get_index_value(Tuple&& tup)
{
    return U{};
};
template<int N,typename...Args>
struct reduce_tuple
{

};
template<int N,typename T,typename...Args>
struct reduce_tuple<N,T,Args...>
{
    using type = typename reduce_tuple<N-1,Args...>::type;
};
template<typename T,typename...Args>
struct reduce_tuple<0,T,Args...>
{
    using type = std::tuple<T,Args...>;
};
template<>
struct reduce_tuple<0>
{
    using type = std::tuple<void_type>;
};
template<typename Tuple,typename...Args,typename...Arg2s>
auto sort_args(Tuple&& correct_tup,std::tuple<Args...>&&,std::tuple<Arg2s...>&& real_params)
{
    using T = typename std::tuple_element<0,std::tuple<Args...>>::type;
    constexpr int index = Find_Type<0,T,Arg2s...>::type::element_index;
    using element_type = typename Find_Type<0,T,Arg2s...>::type::element_type;
    using input_type = std::tuple<Arg2s...>;
    auto result = get_index_value<index,T,element_type>(real_params);
    auto new_tuple = std::tuple_cat(correct_tup,std::tuple<decltype(result)>(result));
    using now_sort_tuple_type = typename reduce_tuple<1,Args...>::type ;
    return sort_args(new_tuple,now_sort_tuple_type{},std::forward<std::tuple<Arg2s...>>(real_params));
};
template<typename Tuple,typename...Args>
auto sort_args(Tuple&& correct_tup,std::tuple<void_type>&&,std::tuple<Args...>&& real_params)
{
    return correct_tup;
};

template<int N,int Max>
struct each_tuple
{
    template<typename Tuple>
    static void show(Tuple tup)
    {
        std::cout<<std::get<N>(tup)<<std::endl;
        each_tuple<N+1,Max>::template show(tup);
    }
};
template<typename...Args,typename...Arg2s>
auto sort_args_help(std::tuple<Args...>&& order_params,std::tuple<Arg2s...>&& real_params)
{
    return sort_args(std::tuple<>(),std::forward<std::tuple<Args...>>(order_params),std::forward<std::tuple<Arg2s...>>(real_params));
}
template<int N>
struct each_tuple<N,N>
{
    template<typename Tuple>
    static void show(Tuple tup)
    {
        std::cout<<std::get<N>(tup)<<std::endl;
    }
};

template<typename...Args>
void show_tuple(std::tuple<Args...> tup)
{
    each_tuple<0,sizeof...(Args)-1>::template show(tup);
}
#endif //UNTITLED42_SORT_TYPE_HPP
