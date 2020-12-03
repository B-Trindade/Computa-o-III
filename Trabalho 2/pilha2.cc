/*
                +------------------------------+
                |  8 tests run/ 8 tests passed |
                +------------------------------+

*/

#include <iostream>
#include <sstream>
#include <stdlib.h>

class PilhaInt {
    //Integer Stack


    //Declaracoes
    public:

    private:
        int* m_ponteiro_pilha;
        int m_altura = 0;
        int m_capacidade_atual = m_altura;    

    public:
        PilhaInt(int capacidade = 10) {
            m_ponteiro_pilha = (int*) malloc(sizeof(int) * capacidade);
            m_capacidade_atual = capacidade;
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
                free(m_ponteiro_pilha);
                copia(p);

                return *this;
            } else {
                //Nao sera necessario alterar nada pois &p = &m_ponteiro_pilha
                return *this;
            }

            return *this;
        }

        void empilha(int v) {
            
            if(testaCapacidade(m_altura+1)) {
                //ha espaco na pilha
                m_ponteiro_pilha[m_altura] = v;
            } else {
                //nao ha espaco na pilha, dobrar a capacidade atual
                m_capacidade_atual *= 2;
                m_ponteiro_pilha = (int*) realloc (m_ponteiro_pilha, sizeof(int) * m_capacidade_atual);
                m_ponteiro_pilha[m_altura] = v;
            }

            m_altura++;
        }

        int desempilha() {
            m_altura--;
            const int& desempilhado = m_ponteiro_pilha[m_altura];


            return( desempilhado );
        }

        void print(std::ostream& o) {

            for(int i = 0; i<m_altura; i++) {
               
                if (i == 0) o << "[ ";
                if( i != m_altura -1 ){
                    o << m_ponteiro_pilha[i] << ", ";
                } else {
                    o << m_ponteiro_pilha[i] << " ]";
                }
            }
        }

        int capacidade() const {
            return(m_capacidade_atual);
        }

        void redimensiona(int n) {
            m_capacidade_atual = n;

            if( m_capacidade_atual < m_altura) 
                m_altura = m_capacidade_atual;
            
            m_ponteiro_pilha = (int*) realloc (m_ponteiro_pilha, sizeof(int) * m_capacidade_atual);  
        }

        ~PilhaInt() {
            free(m_ponteiro_pilha);
        }

    private:

        int testaCapacidade(int novaAltura) const{
            if(novaAltura > m_capacidade_atual) {
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

            m_capacidade_atual = p.m_capacidade_atual;
            m_altura = p.m_altura;
            m_ponteiro_pilha = (int*) malloc(sizeof(int) * m_capacidade_atual);

            for(int i = 0; i<m_altura; i++) {
                m_ponteiro_pilha[i] = p.m_ponteiro_pilha[i];
            }

            return *this;
        }
};

PilhaInt embaralha( PilhaInt q ) {
    int aux = q.desempilha();
    q << 32 << 9 << aux;
    
    return q;
}

int main() {
    using namespace std;
        
    PilhaInt a{81};
    a << 5 << 6 << 3 << 2 << 9 << 13;
    a.redimensiona( 81 ); cout << a.capacidade() << endl;
    a.redimensiona( 11 ); cout << a.capacidade() << endl;
    a.redimensiona( 6 ); cout << a.capacidade() << endl;
    a.print( cout ); cout << endl;
    a.redimensiona( 3 ); cout << a.capacidade() << endl;
    a.print( cout ); cout << endl;

    return 0;
}