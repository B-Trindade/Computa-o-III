#include <iostream>
#include <vector>

using namespace std;

template <int N, typename T>
class Vetor
{
private:
    vector<T> m_vec;
public:

    class DuranteProdVetorial
    {
    private:
        DuranteProdVetorial(Vetor* v) : m_vetor(v) {}
        Vetor *m_vetor;
        friend class Vetor;

    public:
        T valorAt(int pos) {
            return (*m_vetor).m_vec.at(pos);
        }
    };

    class DuranteAtr 
    {
    private:
        DuranteAtr(Vetor* v) : m_vetor(v) {}
        Vetor *m_vetor;
        friend class Vetor;

    public:
        DuranteAtr operator , (T num) {
            *m_vetor = num;
            return *this;
        }
    };

    DuranteProdVetorial operator * () {
        return DuranteProdVetorial(this);
    }

    /* Define a atribuicao pelo operador = para o primeiro valor a direita num  
    e chama a classe intermediaria para inserir os valores restantes no vetor */
    DuranteAtr operator = (T num) {
        m_vec.push_back(num);
        return DuranteAtr(this);
    }

    Vetor<N,T> operator = ( Vetor<N,T> v ) {
        m_vec = v.m_vec;
        return *this;
    }

    Vetor<3,T> operator * ( DuranteProdVetorial vetor_B) {
        Vetor<3,T> resultado;
        resultado = 0,0,0;
        T valores[3];

        switch (N)
        {
        case 1: 
            break;
        case 2:
            /* code */
            resultado.m_vec[2] = m_vec[0]*vetor_B.m_vetor->m_vec[1] - m_vec[1]*vetor_B.m_vetor->m_vec[0];
            break;
        case 3:
            /* bbb */
            valores[0] = m_vec[1] * vetor_B.valorAt(2) - vetor_B.valorAt(1) * m_vec[2];
            valores[1] = m_vec[2] * vetor_B.valorAt(0) - vetor_B.valorAt(2) * m_vec[0];
            valores[2] = m_vec[0] * vetor_B.valorAt(1) - vetor_B.valorAt(0) * m_vec[1];

            resultado = valores[0], valores[1], valores[2];
            break;
        default:
            break;
        }
        return resultado;
    }

    //Define operacao de adicao entre dois vetores [Ax + Bx, Ay + By] etc.
    Vetor<N,T> operator + (Vetor<N,T> v) {
        Vetor<N,T> novo_v;
        novo_v = 0,0,0;

        for( int i=0; i<N; i++) 
            novo_v.m_vec.at(i) = m_vec[i] + v.m_vec[i];

        return novo_v;
    }
    
    //Define operacao de subtracao entre dois vetores [Ax - Bx, Ay - By] etc.
    Vetor<N,T> operator - (Vetor<N,T> v) {
        Vetor<N,T> novo_v;
        novo_v = 0,0,0;

        for( int i=0; i<N; i++) 
            novo_v.m_vec.at(i) = m_vec[i] - v.m_vec[i];
            
        return novo_v;
    }

    //Multiplica o vetor m_vec por um escalar numerico num: [Ax, Ay] * 2 -> [2Ax, 2Ay]
    Vetor<N,T> operator * (T num) {
        Vetor<N,T> novo_v;
        novo_v = 0,0,0;

        for( int i=0; i<N; i++) 
            novo_v.m_vec.at(i) = m_vec[i] * num;

        return novo_v;
    }

    //Divide o vetor m_vec por um escalar numerico num: [Ax, Ay] / 2 -> [Ax/2, Ay/2]
    Vetor<N,T> operator / (T num) {
        Vetor<N,T> novo_v;
        novo_v = 0,0,0;

        for( int i=0; i<N; i++) 
            novo_v.m_vec.at(i) = m_vec[i] / num;

        return novo_v;
    }

    //Produto escalar entre os vetores m_vec e v.m_vec denotado por AxBx + AyBy
    T operator * (Vetor<N,T> v) {
        T soma = 0;

        for( int i=0; i<N; i++)
            soma += m_vec[i] * v.m_vec[i];  

        return soma;    
    }

    void print(ostream& o) {
        for( auto v : m_vec )
            o << v << " ";
        o << endl;
    }

};

template <int N, typename T>
Vetor<N,T>& operator * (T num, Vetor<N,T> v){
    return (v * num);
}

// template <int N,typename T,typename Q>
// // Redefine operadores para Q * Vetor e Q / Vetor
// Vetor<N,T> operator* (Q a, const Vetor<N,T>& v) {
//   Vetor<N,T> novo_v;
//   novo_v = 0,0,0;

//   for( int i = 0; i < N; i++) {
//     novo_v.m_vec[i] = v.m_vec.at(i) * a;
//   }
//   return novo_v;
// }

template <int N, typename T>
ostream& operator << (ostream& o, Vetor<N,T> v) {
    v.print(o);
    return o;
}

int main() {
    Vetor<2, double> v;
    Vetor<2, double> u;

    v = 10.0, 1;
    u = 5.5, 2.5;
    cout << 2.1 * v;

}