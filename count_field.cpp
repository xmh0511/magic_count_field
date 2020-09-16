#include <iostream>
#include <tuple>
#include <string>
struct any_type{
    std::size_t number_;
    template<typename Type>
    operator Type(){
        return Type{};
    }
};
template<std::size_t N>
struct Number{
    static const std::size_t value = N;
};

template<typename T, typename N,typename U = void>
struct fit_count{
    using type = int;
};

template<typename T,std::size_t...N>
struct fit_count<T,std::index_sequence<N...>,std::void_t<decltype(T{any_type{N}...})>>{
   using type = void;
};

template<typename T, std::size_t N = 100, typename U = void>
struct caculate_field_count{
   using type = typename caculate_field_count<T, N -1>::type;
};

template<typename T, std::size_t N>
struct caculate_field_count<T,N,typename fit_count<T,decltype(std::make_index_sequence<N>{})>::type>{
   //using type = typename caculate_field_count<T, N-1,fit_count<T,decltype(std::make_index_sequence<N -1>{})>::value>::type;
   using type = Number<N>;
};



struct Test{
   int c;
   std::string b;
   double d;
};




int main(){
    using type = typename caculate_field_count<Test>::type;
    std::cout<< type::value;
}
