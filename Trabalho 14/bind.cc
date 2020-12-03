#include <functional>
#include <iostream>
#include <utility>
#include <type_traits>

template <typename F, typename ...Args>
class Bind 
{
private:
    F m_f;

public:
    Bind( F func, Args... args ): m_f(func) {}

    template <typename ...Args2>
    auto operator()( Args... args, Args2... new_args ) {
        return bind( m_f, args..., new_args...);
    }
};

template<typename F, typename ...Args, typename ...Args2>
auto bind ( F func, Args... args) {
    if constexpr( std::is_invocable_v< decltype(func), decltype(args)... > ) {
        //Chama func com os argumentos args...
        return std::invoke( func, args...);
    } else {
        // func nao e invocavel atraves de args, realizar outro bind
        
        return [func,args...](auto... new_args) { return bind( func, args..., new_args...); };
    }
}

// int main() {

//     auto f2 = bind( mdc );
//     auto f1 = bind( f2, 12 );
//     for( int i = 2; i <= 12; i++ )
//         std::cout << f1( i ) <<  " ";
// }