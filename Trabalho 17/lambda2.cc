/*

Usando as Expressões Lambda Simplificadas da tarefa anterior, faça com que o código abaixo rode também:

                                vector m< vector<int> >;
                                m | x[0] != 0 | ( x | cout << x << '\n' );

Nesse caso m é um vetor de vetores, e então o primeiro x é um vetor. Logo, podemos escrever um pipe para ele.
E será necessário redefinir o operador "[]" para Expressões Lambda.

*/



#include <iostream>
#include <type_traits>
#include <functional>
#include <vector>
#include <initializer_list>

using namespace std;

template <typename Functor>
class Lambda {
public:
    Lambda( Functor f ): _f(f) {}

    template <typename V>
    invoke_result_t< Functor, V > operator()( V v ) const {
        return _f( v );
    }
    
    // Permite uso de operador [] com objeto do tipo Lambda
    auto operator [] ( int index ) {
        auto arr_element =  [this,index]( auto v ){ return _f(v)[index]; };
        return Lambda<decltype( arr_element )>{ arr_element };
    }

private:
  Functor _f;
};

auto aux = []( auto v ){ return v; };

Lambda x{aux};

template<typename F>
auto operator != ( Lambda<F> l, int i ) {
    return Lambda{
        [l,i]( auto v ) { return l(v) != i; }
    };
}

template <typename A>
auto operator << ( ostream& o, Lambda<A> opr ) { 
 return Lambda{ [&o,opr]( auto v ) -> decltype( o << opr(v) )
                { return o << opr(v); } };
}

#define DEFINE_LAMBDA( opr )                                           \
template <typename A, typename B>                                      \
auto operator opr ( Lambda<A> a, Lambda<B> b ) {                       \
  return Lambda{ [a,b]( auto v ) -> decltype( a(v) opr b(v) )          \
                 { return a(v) opr b(v); } };                          \
}                                                                      \
                                                                       \
template <typename A, typename B>                                      \
auto operator opr ( Lambda<A> a, B b ) {                               \
  return Lambda{ [a,b]( auto v ) -> decltype( a(v) opr b    )          \
                 { return a(v) opr b; } };                             \
}                                                                      \
                                                                       \
template <typename A, typename B>                                      \
auto operator opr ( A a, Lambda<B> b ) {                               \
 return Lambda{ [a,b]( auto v ) -> decltype( a opr b(v)    )           \
                { return a opr b(v); } };                              \
}                                                                      \

DEFINE_LAMBDA( + )
DEFINE_LAMBDA( - )
DEFINE_LAMBDA( * )
DEFINE_LAMBDA( / )
DEFINE_LAMBDA( % )
DEFINE_LAMBDA( == )
DEFINE_LAMBDA( != )
DEFINE_LAMBDA( << )


template<typename F, typename T>
auto operator | ( Lambda<F> l, T t) {
    return Lambda{
        [l,t]( auto v ) { l(v) | t; }
    };
}

template<typename T, typename F>
auto operator | ( const T& iterable, F function ) {
    if constexpr ( is_same_v< bool, invoke_result_t< F, decltype( *begin(iterable) ) > > ) {
        vector< decay_t< decltype( *begin(iterable) ) > > result;

        for( auto element : iterable ) 
            if( invoke( function, element ) )
                result.push_back( element );
        
        return result;
    }
    else if constexpr ( is_same_v< void, invoke_result_t< F, decltype( *begin(iterable) ) > > ||
                        is_reference_v< invoke_result_t< F, decltype( *begin(iterable) ) > > ) {
        for( auto element : iterable ) 
            invoke( function, element );
    }
    else {
        std::vector< decay_t< invoke_result_t< F, decltype( *begin(iterable) ) > > > result;

        for( auto element : iterable ) 
            result.push_back( invoke( function, element ) );
        
        return result;
    }
}