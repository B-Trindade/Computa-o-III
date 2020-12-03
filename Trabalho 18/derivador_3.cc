/*
Usando o Derivador construído na parte 2, remova todos os parênteses desnecessários, e removendo multiplicação por 1, 0, adição com 0 e potenciação a 0 e 1.

                        Entrada: (x+3)->*2
                        Saída: f(x) = (x+3)^2, f'(x) = 2*(x+3) 

                        Entrada: (x)->*3
                        Saída: f(x) = x^3, f'(x) = 3*x^2 
*/

#include <iostream>
#include <cmath>
#include <string>
#include <sstream>

enum OPR {
    SOMA = 0,
    SUB,
    MULT,
    DIV,
    SIN,
    COS,
    POT,
    EXP,
    LOG,
    CTE,
    VAR
};

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

    std::string str() {
        return "x";
    }

    std::string dx_str() {
        return "1";
    }
public:
    const int opr = VAR;
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

    std::string str() {
        std::ostringstream st;
        st << m_c;
        return st.str();
    }

    std::string dx_str() {
        return "0";
    }

private:
    double m_c;
public:
    const int opr = CTE;
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

    double e ( double v ) {
        return m_f1(v) * m_f2(v);
    }

    //A derivada de uma multiplicacao obedece a regra da cadeia
    // ( f(x) * g(x) )' =   f(x)g'(x)  +  f'(x)g(x)
    double dx( double v ) {
        return m_f1(v)*m_f2.dx(v) + m_f1.dx(v)*m_f2(v);
    }
    
    std::string str() {
        std::string expr_1;
        std::string expr_2;

        switch ( m_f1.opr )
        {
        case SOMA: case SUB:
            expr_1 = "(" + m_f1.str() + ")";
            break;
        default:
            expr_1 = m_f1.str();
        }

        switch ( m_f2.opr )
        {
        case SOMA: case SUB:
            expr_2 = "(" + m_f2.str() + ")";
            break;
        default:
            expr_2 = m_f2.str();
        }

        return expr_1 + "*" + expr_2;      
    }

    std::string dx_str() {

        // Testa caso f1 ou f2 sejam constantes
        if( m_f1.dx_str() == "0" ) {
            if( m_f2.dx_str() == "0" )
                return "";
            else if ( m_f2.dx_str() == "1" )
                return m_f1.str();
            else
                return m_f1.str() + "*" + m_f2.dx_str();
        } else if ( m_f2.dx_str() == "0" ) {
            if( m_f1.dx_str() == "1" )
                return m_f2.str();
            else
                return m_f1.dx_str() + "*" + m_f2.str();
        }
        
        // Testa caso f1 ou f2 sejam x, sabendo que nao sao constantes
        if( m_f1.dx_str() == "1" ) {
            if( m_f2.dx_str() == "1" )
                return m_f2.str() + "+" + m_f1.str();
            else
                return m_f2.str() + "+" + m_f1.str() + "*" + m_f2.dx_str();
        } else if ( m_f2.dx_str() == "1" )
            return m_f1.dx_str() + "*" + m_f2.str() + "+" + m_f1.str();
        
        //Caso geral, nem dx(f1), nem dx(f2) sao 0 ou 1
        return m_f1.dx_str() + "*" + m_f2.str() + "+" + m_f1.str() + "*" + m_f2.dx_str();
    }

private:
    F1 m_f1;
    F2 m_f2;
public:
    const int opr = MULT;
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

    double e ( double v ) {
        return m_f1(v) / m_f2(v);
    }

    //A derivada de uma divisao obedece a regra da cadeia
    // ( f(x) / g(x) )' =  ( f'(x)g(x)  -  f(x)g'(x) )/ g2(x)
    double dx ( double v ) {
        return ( m_f1.dx(v)*m_f2(v) - m_f1(v)*m_f2.dx(v) ) / ( m_f2(v) * m_f2(v) );
    }

    std::string str() {
        std::string expr_1;
        std::string expr_2;

        switch ( m_f1.opr )
        {
        case SOMA: case SUB:
            expr_1 = "(" + m_f1.str() + ")";
            break;
        default:
            expr_1 = m_f1.str();
        }

        switch ( m_f2.opr )
        {
        case SOMA: case SUB:
            expr_2 = "(" + m_f2.str() + ")";
            break;
        default:
            expr_2 = m_f2.str();
        }

        return expr_1 + "/" + expr_2;     
    }

    std::string dx_str() {
        std::string exp_denominador = "";

        switch ( m_f2.opr )
        {
        case SOMA: case SUB: case MULT: case DIV: case POT:
            exp_denominador += "(" + m_f2.str() + ")^2";
            break;
        
        default:
            exp_denominador += m_f2.str() + "^2";
            break;
        }

        // Testa caso f1 ou f2 sejam constantes
        if( m_f1.dx_str() == "0" ) {

            if( m_f2.dx_str() == "0" )
                return "";
            else if ( m_f2.dx_str() == "1" && m_f2.str() != "1" )
                return "-" + m_f1.str() + "/" + exp_denominador;
            else if ( m_f2.dx_str() == "1" && m_f2.str() == "1" )
                return "-" + m_f1.str();
            else if ( m_f2.str() == "1" )
                return "-" + m_f1.str() + "*" + m_f2.dx_str();
            else if ( m_f1.str() == "1" )
                return "-" + m_f2.dx_str() + "/" + exp_denominador;
            else
                return "-(" + m_f1.str() + "*" + m_f2.dx_str() + ")/" + exp_denominador;

        } else if ( m_f2.dx_str() == "0" ) {

            if( m_f1.dx_str() == "1" && m_f2.str() != "1" )
                return m_f2.str() + "/" + exp_denominador;
            else if ( m_f1.dx_str() == "1" && m_f2.str() == "1" )
                return m_f2.str();
            else if ( m_f2.str() == "1" )
                return m_f1.dx_str() + "*" + m_f2.str();
            else
                return "(" + m_f1.dx_str() + "*" + m_f2.str() + ")/" + exp_denominador;

        }
        
        // Testa caso f1 ou f2 sejam x, sabendo que nao sao constantes
        if( m_f1.dx_str() == "1" ) {
            
            if( m_f2.dx_str() == "1" )
                return "(" + m_f2.str() + "-" + m_f1.str() + ")/" + exp_denominador;
            else 
                return "(" + m_f2.str() + "-(" + m_f1.str() + "*" + m_f2.dx_str() + "))/" + exp_denominador;

        } else if ( m_f2.dx_str() == "1" )
            return "(" + m_f1.dx_str() + "*" + m_f2.str() + "-" + m_f1.str() + ")/" + exp_denominador;
        
        //Caso geral, nem dx(f1), nem dx(f2) sao 0 ou 1


        return "(" + m_f1.dx_str() + "*" + m_f2.str() + "-(" + m_f1.str() + "*" + m_f2.dx_str() + "))/" + exp_denominador;
    }

private:
    F1 m_f1;
    F2 m_f2;
public:
    const int opr = DIV;    
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

    double e ( double v ) {
        return m_f1(v) + m_f2(v);
    }

    //A derivada de uma soma obedece a regra da cadeia
    // ( f(x) + g(x) )' =   f'(x) + g'(x)
    double dx ( double v ) {
        return m_f1.dx(v) + m_f2.dx(v);
    }

    std::string str() {
        return m_f1.str() + "+" + m_f2.str();
    }

    std::string dx_str() {
        if( m_f1.dx_str() == "0" && m_f2.dx_str() == "0" )
            return "";
        else if( m_f1.dx_str() == "0" )
            return m_f2.dx_str();
        else if( m_f2.dx_str() == "0" )
            return m_f1.dx_str();
        else
            return m_f1.dx_str() + "+" + m_f2.dx_str();
    }
private:
    F1 m_f1;
    F2 m_f2;
public:
    const int opr = SOMA;
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

    double e ( double v ) {
        return m_f1(v) - m_f2(v);
    }
    
    //A derivada de uma subtracao obedece a regra da cadeia
    // ( f(x) - g(x) )' =   f'(x) - g'(x)
    double dx ( double v ) {
        return m_f1.dx(v) - m_f2.dx(v);
    }

    std::string str() {
        switch ( m_f2.opr )
        {
        case SOMA: case SUB:
            return m_f1.str() + "-(" + m_f2.str() + ")";
        
        default:
            return m_f1.str() + "-" + m_f2.str();;
        }
        
    }

    std::string dx_str() {
        if( m_f1.dx_str() == "0" && m_f2.dx_str() == "0" )
            return "";
        else if( m_f1.dx_str() == "0" )
            return "(-" + m_f2.dx_str() + ")";
        else if( m_f2.dx_str() == "0" )
            return m_f1.dx_str();
        else
            return m_f1.dx_str() + "-" + m_f2.dx_str();
    }

private:
    F1 m_f1;
    F2 m_f2;
public:
    const int opr = SUB;
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

//Classe que uma template para generalizar as funcoes f(x) recebidas por sen()
template<typename F1>
class Seno
{
public:
    Seno( F1 f1 ) : m_f1(f1) {}

    double operator() ( double v ) {
        return std::sin( m_f1(v) );
    }

    double e ( double v ) {
        return std::sin( m_f1(v) );
    }

    //A derivada da funcao seno obedece a regra da cadeia
    // ( sen( f(x) ))' =   cos(f(x))* f'(x)
    double dx ( double v ) {
        return std::cos( m_f1(v) ) * m_f1.dx(v);
    }

    std::string str() {
        return "sin(" + m_f1.str() + ")";
    }

    std::string dx_str() {
        if( m_f1.dx_str() != "1" )
            return "cos(" + m_f1.str() + ")*" + m_f1.dx_str();
        else
            return "cos(" + m_f1.str() + ")";
    }

private:
    F1 m_f1;
public:
    const int opr = SIN;
};

//Definindo funcao seno de uma f(x)
template<typename F1>
Seno<F1> sin ( F1 f1 ) {
    return Seno<F1>( f1 );
}

///////////////////////////////////////////////////////////////////////////////////////////////

//Classe que uma template para generalizar as funcoes f(x) recebidas por cos()
template<typename F1>
class Cosseno
{
public:
    Cosseno( F1 f1 ) : m_f1(f1) {}

    double operator() ( double v ) {
        return std::cos( m_f1(v) );
    }

    double e ( double v ) {
        return std::cos( m_f1(v) );
    }

    //A derivada da funcao cosseno obedece a regra da cadeia
    // ( cos( f(x) ))' =   -sen(f(x)) * f'(x)
    double dx ( double v ) {
        return std::sin( m_f1(v) ) * -1.0 * m_f1.dx(v);
    }

    std::string str() {
        return "cos(" + m_f1.str() + ")";
    }

    std::string dx_str() {
        if( m_f1.dx_str() != "1" )
            return "-sin(" + m_f1.str() + ")*" + m_f1.dx_str();
        else
            return "-sin(" + m_f1.str() + ")";
    }

private:
    F1 m_f1;
public:
    const int opr = COS;
};

//Definindo funcao cosseno de uma f(x)
template<typename F1>
auto cos ( F1 f1 ) {
    return Cosseno<F1>( f1 );
}

///////////////////////////////////////////////////////////////////////////////////////////////

template<typename F1>
class Potenciacao
{
public:
    Potenciacao( F1 f1, int n ) : m_f1(f1), m_expoente(n) {}
    
    double operator() ( double v ) {
        return std::pow( m_f1(v), m_expoente );
    }

    double e ( double v ) {
        return std::pow( m_f1(v), m_expoente );
    }

    double dx ( double v ) {
        int novo_exp = (m_expoente - 1);
        return m_expoente * m_f1.dx(v) * std::pow( m_f1(v), novo_exp ); 
    }

    std::string str() {
        std::string e_str = std::to_string( m_expoente ) + "";

        //TODO : Adicionar casos expoente 0 e expoente 1

        switch ( m_f1.opr )
        {
        case SOMA: case SUB: case MULT: case DIV:
            return "(" + m_f1.str() + ")^" + e_str;  
        default:
            return m_f1.str() + "^" + e_str;
        }
    }

    std::string dx_str() {
        std::string e_str = std::to_string( m_expoente ) + "";
        std::string n_e_str = std::to_string( m_expoente - 1 ) + "";

        std::string res = "";

        //TODO : Adicionar casos expoente 0 e expoente 1

        if( m_f1.dx_str() != "1" ) {
            switch ( m_f1.opr )
            {
            case SOMA: case SUB: case MULT: case DIV: case POT:
                if( m_f1.dx_str() == "7" )
                    res += e_str + "*" + m_f1.dx_str() + "*(" + m_f1.str() + ")";
                else
                    res += e_str + "*(" + m_f1.dx_str() + ")*(" + m_f1.str() + ")";
                break;
            default:
                res += e_str + "*" + m_f1.dx_str() + "*" + m_f1.str();
                break;
            }
        } else
            res += e_str + "*" + m_f1.str();

        if ( m_expoente > 2 )
            res += "^" + n_e_str;

        return res;
    }

private:
    F1 m_f1;
    int m_expoente;
public:
    const int opr = POT;
};

template<typename F1>
Potenciacao<F1> operator ->* ( F1 f1, int n ) {
    return Potenciacao<F1>(f1, n);
}

///////////////////////////////////////////////////////////////////////////////////////////////

template<typename F1>
class Exponencial
{
public:
    Exponencial( F1 f1 ) : m_f1(f1) {}
    
    double operator() ( double v ) {
        return std::exp( m_f1(v) );
    }

    double e ( double v ) {
        return std::exp( m_f1(v) );
    }

    double dx ( double v ) {
        return std::exp( m_f1(v) ) * m_f1.dx(v);
    }

    std::string str() {
        return "exp(" + m_f1.str()  + ")";
    }

    std::string dx_str() {

        if( m_f1.dx_str() == "1" )
            return "exp(" + m_f1.str() + ")";
        else if (m_f1.dx_str() == "0")
            return "";
        else
            return "exp(" + m_f1.str() + ")*(" + m_f1.dx_str() + ")";
    }

private:
    F1 m_f1;
public:
    const int opr = EXP;
};

template<typename F1>
Exponencial<F1> exp ( F1 f1 ) {
    return Exponencial<F1>(f1);
}

///////////////////////////////////////////////////////////////////////////////////////////////

template<typename F1>
class Logaritmo
{
public:
    Logaritmo( F1 f1 ) : m_f1(f1) {}

    double operator() ( double v ) {
        return std::log( m_f1(v) );
    }

    double e ( double v ) {
        return std::log( m_f1(v) );
    }

    double dx ( double v ) {
        return 1/ m_f1(v);
    }

    std::string str() {
        return "log(" + m_f1.str() + ")";
    }

    std::string dx_str() {
        std::string exp_denominador = "";

        switch ( m_f1.opr )
        {
        case SOMA: case SUB: case MULT: case DIV: case POT:
            exp_denominador += "(" + m_f1.str() + ")";
            break;
        
        default:
            exp_denominador += m_f1.str();
            break;
        }

        if( m_f1.dx_str() == "1" )
            return "1/" + exp_denominador;
        else
            return "1/" + exp_denominador + "*" + m_f1.dx_str();
    }

private:
    F1 m_f1;
public:
    const int opr = LOG;
};

template<typename F1>
Logaritmo<F1> log ( F1 f1 ) {
    return Logaritmo<F1>(f1);
}

///////////////////////////////////////////////////////////////////////////////////////////////

// Erro
template <typename F1, typename F2>
Potenciacao<F1> operator ->* ( F1 f1, F2 f2 ) {
  static_assert(std::is_same<F2,int>::value, "Operador de potenciação definido apenas para inteiros");
  return Potenciacao<F1>( f1, f2 );
}
X x;
///////////////////////////////////////////////////////////////////////////////////////////////

// int main() {
//     X x;
//     double v = 3;
//     auto f =  2 * x->*1;

//     std::cout << f.str() << std::endl;
//     std::cout << f.dx_str() << std::endl;
    
//     return 0;
// }


// (exp(((((x)*(log(((x)-(8))))))+(1)))*((((1)*(log(((x)-(8))))+(x)*((1/(((x)-(8))))))+(0)))
// (exp(((((x)*(log(((x)-(8))))))+(1)))*((((1)*(log(((x)-(8))))+(x)*((1/(((x)-(8)))*((1)-(0))))))+(0)))
