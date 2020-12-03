#include <iostream>
#include <cmath>
#include <vector>
#include <iterator>
#include <type_traits>
#include <functional>

using namespace std;

class X
{
public:

    //Metodo para possibilitar a passagem de valor nas classes de
    //operadors, no caso de uma variavel classe X X::(v) inicializa a variavel.
    double operator()( double v ) {
        return v;
    }
    
    double e ( double v ) {
        return v;
    }

    //A derivada de uma variavel em relacao a ela mesma sempre retorna 1.
    double dx( double v ) {
        return 1;
    }
};

class Cte
{
public:
    Cte( double c ): m_c(c) {}
    
    //Metodo para possibilitar a passagem de valor nas classes de
    //operadores, no caso Cte o valor v deve ser ignorado.
    double operator()( double v ) {
        return m_c;
    }
  
    double e ( double v ) {
        return m_c;
    }

    //A derivada de uma constante sempre retorna 0.
    double dx( double v ) {
        return 0;
    }
private:
    double m_c;
};

///////////////////////////////////////////////////////////////////////////////////////////////

//Classe que recebe 2 templates para generalizar 
//as funcoes f(x) & g(x) de uma multiplicacao.
template <typename F1, typename F2>
class Multiplica
{
public:
    Multiplica( F1 f1, F2 f2 ): m_f1(f1), m_f2(f2) {}
  
    double operator() ( double v ) {
        return m_f1(v) * m_f2(v);
    }

private:
    F1 m_f1;
    F2 m_f2;
};


//Definindo operacao de multiplicacao entre funcoes derivaveis
template <typename F1, typename F2> 
Multiplica<F1,F2> operator * ( F1 f1, F2 f2 ) {
    return Multiplica<F1,F2>( f1, f2 );
}

template <typename F2> 
Multiplica<Cte,F2> operator * ( double n, F2 f2 ) {
    return Multiplica<Cte,F2>( n, f2 );
}

//Typecast de int para double no parametro F1
template <typename F2> 
Multiplica<Cte,F2> operator * ( int n, F2 f2 ) {
    return Multiplica<Cte,F2>( double(n), f2 );
}

template <typename F1> 
Multiplica<F1,Cte> operator * ( F1 f1, double n ) {
    return Multiplica<F1,Cte>( f1, n );
}

//Typecast de int para double no parametro F2
template <typename F1> 
Multiplica<F1,Cte> operator * ( F1 f1, int n ) {
    return Multiplica<F1,Cte>( f1, double(n) );
}

///////////////////////////////////////////////////////////////////////////////////////////////

//Classe que recebe 2 templates para generalizar 
//as funcoes f(x) & g(x) de uma divisao.
template<typename F1, typename F2>
class Divide
{
public:
    Divide( F1 f1, F2 f2 ) : m_f1(f1), m_f2(f2) {}

    double operator() ( double v ) {
        return m_f1(v) / m_f2(v);
    }

private:
    F1 m_f1;
    F2 m_f2;
};

//Definindo operacao de divisao entre funcoes derivaveis
template<typename F1, typename F2>
Divide<F1,F2> operator / ( F1 f1, F2 f2 ) {
    return Divide<F1,F2>( f1, f2 );
}

template<typename F1>
Divide<F1,Cte> operator / ( F1 f1, double n ) {
    return Divide<F1,Cte>( f1, n );
}

//Typecast de int para double no parametro F2
template<typename F1>
Divide<F1,Cte> operator / ( F1 f1, int n ) {
    return Divide<F1,Cte>( f1, double(n) );
}

template<typename F2>
Divide<Cte,F2> operator / ( double n, F2 f2 ) {
    return Divide<Cte,F2>( n, f2 );
}

//Typecast de int para double no parametro F1
template<typename F2>
Divide<Cte,F2> operator / ( int n, F2 f2 ) {
    return Divide<Cte,F2>( double(n), f2 );
}

///////////////////////////////////////////////////////////////////////////////////////////////

//Classe que recebe 2 templates para generalizar 
//as funcoes f(x) & g(x) de uma soma.
template<typename F1, typename F2>
class Soma
{
public:
    Soma( F1 f1, F2 f2 ) : m_f1(f1), m_f2(f2) {}

    double operator() ( double v ) {
        return m_f1(v) + m_f2(v);
    }

private:
    F1 m_f1;
    F2 m_f2;
};

//Definindo operacao de adicao entre funcoes derivaveis
template<typename F1, typename F2>
Soma<F1,F2> operator + ( F1 f1, F2 f2 ) {
    return Soma<F1,F2>( f1, f2 );
}

template<typename F1>
Soma<F1,Cte> operator + ( F1 f1, double n ) {
    return Soma<F1,Cte>( f1, n );
}

//Typecast de int para double no parametro F2
template<typename F1>
Soma<F1,Cte> operator + ( F1 f1, int n ) {
    return Soma<F1,Cte>( f1, double(n) );
}

template<typename F2>
Soma<Cte,F2> operator + ( double n, F2 f2 ) {
    return Soma<Cte,F2>( n, f2 );
}

//Typecast de int para double no parametro F1
template<typename F2>
Soma<Cte,F2> operator + ( int n, F2 f2 ) {
    return Soma<Cte,F2>( double(n), f2 );
}

///////////////////////////////////////////////////////////////////////////////////////////////

//Classe que recebe 2 templates para generalizar 
//as funcoes f(x) & g(x) de uma subtracao.
template<typename F1, typename F2>
class Subtracao
{
public:
    Subtracao( F1 f1, F2 f2 ) : m_f1(f1), m_f2(f2) {}

    double operator() ( double v ) {
        return m_f1(v) - m_f2(v);
    }

private:
    F1 m_f1;
    F2 m_f2;
};

//Definindo operacao de subtracao entre funcoes derivaveis
template<typename F1, typename F2>
Subtracao<F1,F2> operator - ( F1 f1, F2 f2 ) {
    return Subtracao<F1,F2>( f1, f2 );
}

template<typename F1>
Subtracao<F1,Cte> operator - ( F1 f1, double n ) {
    return Subtracao<F1,Cte>( f1, n );
}

//Typecast de int para double no parametro F2
template<typename F1>
Subtracao<F1,Cte> operator - ( F1 f1, int n ) {
    return Subtracao<F1,Cte>( f1, double(n) );
}

template<typename F2>
Subtracao<Cte,F2> operator - ( double n, F2 f2 ) {
    return Subtracao<Cte,F2>( n, f2 );
}

//Typecast de int para double no parametro F1
template<typename F2>
Subtracao<Cte,F2> operator - ( int n, F2 f2 ) {
    return Subtracao<Cte,F2>( double(n), f2 );
}
///////////////////////////////////////////////////////////////////////////////////////////////

template<typename F1, typename F2>
class Modulo
{
    public:
    Modulo( F1 f1, F2 f2 ) : m_f1(f1), m_f2(f2) {}

    double operator() ( double v ) {
        auto m_res = ( m_f1(v) % m_f2(v) );
        return m_res;
    }

    int operator == ( int n ) {
        return m_res == double(n);
    }

private:
    double m_res;
    F1 m_f1;
    F2 m_f2;
};

template<typename F1>
Modulo<F1,Cte> operator % ( F1 f1, int n ) {
    return Modulo<F1,Cte>( f1, n );
}

template<typename F2>
Modulo<Cte,F2> operator % ( int n , F2 f2 ) {
    return Modulo<Cte,F2>( n, f2 );
}

template<typename F1, typename F2>
Modulo<F1,F2> operator % ( F1 f1, F2 f2 ) {
    return Modulo<F1,F2>( f1, f2 );
}


///////////////////////////////////////////////////////////////////////////////////////////////
template <typename F1>
class Print {
    public:
        Print(ostream& o, F1 f1, bool b): stream(o.rdbuf()), f1(f1), hasEndl(b) {}

        template <typename V>
        void operator () (V v) {
            if constexpr (is_same_v<F1, char>) {
                // using std::operator <<;
                // stream << f1;
            } else {
                stream << f1(v);
                if(hasEndl)
                    stream << '\n';
            }
        }

        void addEndl() {
            hasEndl = true;
        }

    // private:
    public:
        ostream stream;
        F1 f1;
        bool hasEndl = false;
};

// Overload de << para print
template <typename F1>
Print<F1> operator << (ostream& o, F1 f) {
    return Print<F1>(o, f, false);
}

template <typename F1, typename F2>
Print<F2> operator << (Print<F2> p, F1 f) {
    return Print<F2>(p.stream, p.f1, true);
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

X x;

int main() {

    int tab[10] =  { 1, 2, 3, 2, 3, 4, 6, 0, 1, 8 };
    vector<int> v;
    tab | cout << x*x << '\n';
    tab | [ &v ]( int x ) { v.push_back( x ); };
    v | x % 2 == 0 | cout << x*x + 1 << '\n';
    v | x % 2 == 1 | x*x | cout << x << '\n';
}