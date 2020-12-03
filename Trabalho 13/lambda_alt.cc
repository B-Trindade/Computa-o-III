#include <iostream>
#include <vector>
#include <cmath>
#include <type_traits>
#include <functional>

using namespace std;

// Classe de expressao lambda que recebe functor f
// Fazendo dessa forma substitui-se outras classes, como X
template <typename Functor>
class Lambda 
{
public:
    Lambda( Functor f ): f(f) {}

    template <typename T>
    std::invoke_result_t< Functor, T > operator()( T v ) const {
        return f( v );
    }

    template <typename I>
    auto operator [] (I i) {
        return Lambda {  [i]( auto v ) { return v[i]; }  };
    }

private:
  Functor f;
};

// Functor inicial que recebe v e retorna v para inicializar Lambda x
auto aux = []( auto v ){ return v; };

// Substitui a declaracao global X x; obrigatoria
Lambda x{aux};

// Redefine o operador | para funcoes lambda e arg template
template <typename F1, typename Y>
auto operator | ( Lambda<F1> x, Y y ) {
    // Aplica o functor lambda "x.f" em v e aplica o operador | com y em seguida
    return Lambda { [x,y]( auto v ) { return x(v) | y; } };
}

// Define o operador << para operar a Lambda x em v e redirecionar para a saida ostream
// Esse operador tbm e redefinido no define para operadores "opr", mas e necessario um overload para ostream
template <typename F1>
auto operator << ( ostream& o, Lambda<F1> x ) { 
    // Nesse caso o decltype se faz necessario para o auto em tempo de compilacao
    return Lambda { [&o,x]( auto v )->decltype( o << x(v) ) { return o << x(v); } };
}

///////////////////////////////////////////////////////////////////////////////////////////////
////////////////////// Serie de redefinicoes de operadores para Lambda ////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
                                          
template <typename F1, typename F2>                                    
auto operator + ( Lambda<F1> x, Lambda<F2> y ) {                     
  return Lambda{ [x,y]( auto v )->decltype( x(v) + y(v) ) { return x(v) + y(v); } };                          
}                                                                      
                                                                       
template <typename F1, typename Y>                                     
auto operator + ( Lambda<F1> x, Y y ) {                              
  return Lambda{ [x,y]( auto v ) -> decltype( x(v) + y    ) { return x(v) + y; } };                             
}                                                                      
                                                                       
template <typename Y, typename F1>                                     
auto operator + ( Y y, Lambda<F1> x ) {                              
 return Lambda{ [y,x]( auto v ) -> decltype( y + x(v)    )           
                { return y + x(v); } };                              
}                                                                      

///////////////////////////////////////////////////////////////////////////////////////////////


template <typename F1, typename F2>                                    
auto operator - ( Lambda<F1> x, Lambda<F2> y ) {                     
  return Lambda{ [x,y]( auto v )->decltype( x(v) - y(v) ) { return x(v) - y(v); } };                          
}                                                                      
                                                                       
template <typename F1, typename Y>                                     
auto operator - ( Lambda<F1> x, Y y ) {                              
  return Lambda{ [x,y]( auto v )->decltype( x(v) - y ) { return x(v) - y; } };                             
}                                                                      
                                                                       
template <typename Y, typename F1>                                     
auto operator - ( Y y, Lambda<F1> x ) {                              
 return Lambda{ [y,x]( auto v )->decltype( y - x(v) ) { return y - x(v); } };                              
}   

///////////////////////////////////////////////////////////////////////////////////////////////


template <typename F1, typename F2>                                    
auto operator * ( Lambda<F1> x, Lambda<F2> y ) {                     
  return Lambda{ [x,y]( auto v )->decltype( x(v) * y(v) ) { return x(v) * y(v); } };                          
}                                                                      
                                                                       
template <typename F1, typename Y>                                     
auto operator * ( Lambda<F1> x, Y y ) {                              
  return Lambda{ [x,y]( auto v )->decltype( x(v) * y ) { return x(v) * y; } };                             
}                                                                      
                                                                       
template <typename Y, typename F1>                                     
auto operator * ( Y y, Lambda<F1> x ) {                              
 return Lambda{ [y,x]( auto v )->decltype( y * x(v) ) { return y * x(v); } };                              
} 

///////////////////////////////////////////////////////////////////////////////////////////////


template <typename F1, typename F2>                                    
auto operator / ( Lambda<F1> x, Lambda<F2> y ) {                     
  return Lambda{ [x,y]( auto v )->decltype( x(v) / y(v) ) { return x(v) / y(v); } };                          
}                                                                      
                                                                       
template <typename F1, typename Y>                                     
auto operator / ( Lambda<F1> x, Y y ) {                              
  return Lambda{ [x,y]( auto v )->decltype( x(v) / y ) { return x(v) / y; } };                             
}                                                                      
                                                                       
template <typename Y, typename F1>                                     
auto operator / ( Y y, Lambda<F1> x ) {                              
 return Lambda{ [y,x]( auto v )->decltype( y / x(v) ) { return y / x(v); } };                              
} 

///////////////////////////////////////////////////////////////////////////////////////////////


template <typename F1, typename F2>                                    
auto operator % ( Lambda<F1> x, Lambda<F2> y ) {                     
  return Lambda{ [x,y]( auto v )->decltype( x(v) % y(v) ) { return x(v) % y(v); } };                          
}                                                                      
                                                                       
template <typename F1, typename Y>                                     
auto operator % ( Lambda<F1> x, Y y ) {                              
  return Lambda{ [x,y]( auto v )->decltype( x(v) % y ) { return x(v) % y; } };                             
}                                                                      
                                                                       
template <typename Y, typename F1>                                     
auto operator % ( Y y, Lambda<F1> x ) {                              
 return Lambda{ [y,x]( auto v )->decltype( y % x(v) ) { return y % x(v); } };                              
} 


///////////////////////////////////////////////////////////////////////////////////////////////


template <typename F1, typename F2>                                    
auto operator == ( Lambda<F1> x, Lambda<F2> y ) {                     
  return Lambda{ [x,y]( auto v )->decltype( x(v) == y(v) ) { return x(v) == y(v); } };                          
}                                                                      
                                                                       
template <typename F1, typename Y>                                     
auto operator == ( Lambda<F1> x, Y y ) {                              
  return Lambda{ [x,y]( auto v )->decltype( x(v) == y ) { return x(v) == y; } };                             
}                                                                      
                                                                       
template <typename Y, typename F1>                                     
auto operator == ( Y y, Lambda<F1> x ) {                              
 return Lambda{ [y,x]( auto v )->decltype( y == x(v) ) { return y == x(v); } };                              
} 

///////////////////////////////////////////////////////////////////////////////////////////////

template <typename F1, typename F2>                                    
auto operator << ( Lambda<F1> x, Lambda<F2> y ) {                     
  return Lambda{ [x,y]( auto v )->decltype( x(v) << y(v) ) { return x(v) << y(v); } };                          
}                                                                      
                                                                       
template <typename F1, typename Y>                                     
auto operator << ( Lambda<F1> x, Y y ) {                              
  return Lambda{ [x,y]( auto v )->decltype( x(v) << y ) { return x(v) << y; } };                             
}                                                                      
                                                                       
template <typename Y, typename F1>                                     
auto operator << ( Y y, Lambda<F1> x ) {                              
 return Lambda{ [y,x]( auto v )->decltype( y << x(v) ) { return y << x(v); } };                              
} 

///////////////////////////////////////////////////////////////////////////////////////////////

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


int main() {
    string v1[] = { "a", "b2", "cc3", "saci" };
    v1 | []( string n ) { return n.length() % 2 == 0; } | (x+x) | cout << x << ' ';

    int tab[10] =  { 1, 2, 3, 2, 3, 4, 6, 0, 1, 8 };
    vector<int> v;
    tab | cout << x*x << '\n';
    tab | [ &v ]( int x ) { v.push_back( x ); };
    v | x % 2 == 0 | cout << x*x + 1 << '\n';
    v | x % 2 == 1 | x*x | cout << x << '\n';

}