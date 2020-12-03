/*
                +------------------------------+
                |  8 tests run/ 8 tests passed |
                +------------------------------+

*/

#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <vector>

class PilhaInt {
    //Integer Stack


    //Declaracoes
    public:

    private:
        std::vector<int> m_vetor_pilha;

    public:
        PilhaInt(int capacidade = 10) {
            m_vetor_pilha.reserve(capacidade);
        }
        
        PilhaInt( const PilhaInt& pilha ) {
            //Cosntrutor de copia
            copia(pilha);
        }

        PilhaInt& operator<< (int n){
            empilha(n);

            return *this;
        }

        const PilhaInt& operator= (const PilhaInt& p) {
            if( testaBugAutoatribuicao(p) ) {
                //nao apresentou bug de carecteristica pilha1 = pilha1
                m_vetor_pilha.clear();
                copia(p);

                return *this;
            } else {
                //Nao sera necessario alterar nada pois &p = &m_vetor_pilha
                return *this;
            }

            return *this;
        }

        void empilha(int v) {
            m_vetor_pilha.push_back(v);
        }

        int desempilha() {

            const int desempilhado = m_vetor_pilha.back();
            m_vetor_pilha.pop_back();

            return( desempilhado );
        }

        void print(std::ostream& o) {

            for(int i = 0; i< (int) m_vetor_pilha.size(); i++) {
               
                if (i == 0) o << "[ ";
                if( i != (int) m_vetor_pilha.size() -1 ){
                    o << m_vetor_pilha[i] << ", ";
                } else {
                    o << m_vetor_pilha[i] << " ]";
                }
            }
        }

        int capacidade() const {
            return(m_vetor_pilha.capacity());
        }

        void redimensiona(int n) {
            m_vetor_pilha.resize(n);  
        }

        ~PilhaInt() {
            m_vetor_pilha.clear();
        }

    private:

        int testaCapacidade(int novaAltura) const{
            if(novaAltura > (int) m_vetor_pilha.capacity()) {
                return(0);
            } else return(1);

            return(2);
        }

        int testaBugAutoatribuicao(const PilhaInt& p) const {
            if( &p == this ) {
                return 0;
            } else return(1);

            return(2);
        }

        const PilhaInt& copia( const PilhaInt& p) {
            //Este metodo nao eh responsavel pela desalocacao!

            m_vetor_pilha.clear();
            m_vetor_pilha.resize(p.m_vetor_pilha.capacity());

            for(int i = 0; i< (int) p.m_vetor_pilha.size(); i++) {
                m_vetor_pilha[i] = p.m_vetor_pilha[i];
            }

            return *this;
        }
};

//////////////////////////////  TEST FUNCTION  ///////////////////////////////////

PilhaInt embaralha( PilhaInt q ) {
    int aux = q.desempilha();
    q << 32 << 9 << aux;
    
    return q;
}

int main() {
    using namespace std;
    PilhaInt a{3};
    for( int i = 0; i < 20; i++ ) {
    a << i;
    cout << a.capacidade() << " ";
    }
    cout << endl;
    a.print( cout ); cout << endl;


    return 0;
}