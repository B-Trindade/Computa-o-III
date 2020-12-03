#include <iostream>
#include <type_traits>
#include <functional>
#include <vector>

using namespace std;

template <typename Functor>
class Lambda {
public:
  Lambda( Functor f ): f(f) {}

  template <typename V>
  invoke_result_t< Functor, V > operator()( V v ) const {
    return f( v );
  }
  
  auto operator[]( int n ) const {
    auto opr =  [this,n]( auto v ){ return f(v)[n]; };
    return Lambda< decltype(opr) >{ opr };
  }

private:
  Functor f;
};

auto aux = []( auto v ){ return v; };

Lambda x{aux};

template <typename A>
auto operator << ( ostream& o, Lambda<A> opr ) { 
 return Lambda{ [&o,opr]( auto v ) -> ostream& { return o << opr(v); } };
}

template <typename A, typename B>
auto operator << ( Lambda<A> a, Lambda<B> b ) { 
 return Lambda{ [a,b]( auto v ) ->ostream& { return a(v) << b(v); } };
}

template <typename A, typename B>
auto operator << ( Lambda<A> a, B b ) { 
 return Lambda{ [a,b]( auto v ) ->ostream& { return a(v) << b; } };
}
template <typename A, typename B>
auto operator << ( A a, Lambda<B> b ) { 
 return Lambda{ [a,b]( auto v ) ->ostream& { return a << b(v); } };
}

template <typename A, typename B>
auto operator + ( Lambda<A> a, Lambda<B> b ) { 
 return Lambda{ [a,b]( auto v ) { return a(v) + b(v); } };
}

template <typename A, typename B>
auto operator + ( Lambda<A> a, B b ) { 
 return Lambda{ [a,b]( auto v ) { return a(v) + b; } };
}

template <typename A, typename B>
auto operator + ( A a, Lambda<B> b ) { 
 return Lambda{ [a,b]( auto v ) { return a + b(v); } };
}

template <typename A, typename B>
auto operator * ( Lambda<A> a, Lambda<B> b ) { 
 return Lambda{ [a,b]( auto v ) { return a(v) * b(v); } };
}

template <typename A, typename B>
auto operator * ( Lambda<A> a, B b ) { 
 return Lambda{ [a,b]( auto v ) { return a(v) * b; } };
}

template <typename A, typename B>
auto operator * ( A a, Lambda<B> b ) { 
 return Lambda{ [a,b]( auto v ) { return a * b(v); } };
}

template <typename A, typename B>
auto operator % ( Lambda<A> a, Lambda<B> b ) { 
 return Lambda{ [a,b]( auto v ) { return a(v) % b(v); } };
}

template <typename A, typename B>
auto operator % ( Lambda<A> a, B b ) { 
 return Lambda{ [a,b]( auto v ) { return a(v) % b; } };
}

template <typename A, typename B>
auto operator % ( A a, Lambda<B> b ) { 
 return Lambda{ [a,b]( auto v ) { return a % b(v); } };
}

template <typename A, typename B>
auto operator == ( Lambda<A> a, Lambda<B> b ) { 
 return Lambda{ [a,b]( auto v ) { return a(v) == b(v); } };
}

template <typename A, typename B>
auto operator == ( Lambda<A> a, B b ) { 
 return Lambda{ [a,b]( auto v ) { return a(v) == b; } };
}

template <typename A, typename B>
auto operator == ( A a, Lambda<B> b ) { 
 return Lambda{ [a,b]( auto v ) { return a == b(v); } };
}

template <typename A, typename B>
auto operator != ( Lambda<A> a, Lambda<B> b ) { 
 return Lambda{ [a,b]( auto v ) { return a(v) != b(v); } };
}

template <typename A, typename B>
auto operator != ( Lambda<A> a, B b ) { 
 return Lambda{ [a,b]( auto v ) { return a(v) != b; } };
}

template <typename A, typename B>
auto operator != ( A a, Lambda<B> b ) { 
 return Lambda{ [a,b]( auto v ) { return a != b(v); } };
}

template <typename A, typename B>
auto operator | ( Lambda<A> a, B b ) { 
 return Lambda{ [a,b]( auto v ) { return a(v) | b; } };
}

// pipe
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
