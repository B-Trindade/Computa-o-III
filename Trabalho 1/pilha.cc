/*
                +------------------------------+
                |  5 tests run/ 5 tests passed |
                +------------------------------+
*/

#include <iostream>
#include <sstream>

struct Node
{
    int valor;
    Node* proximo;
};

class PilhaInt {
    //Integer Stack

    

    //Declaracoes
    public:
    /*
        PilhaInt();     //Constructor
        const PilhaInt& operator= (const PilhaInt& p);     //Operator overloader
        void empilha(int valor);        //insere valor no topo da pilha
        int desempilha();       //remove o valor do topo
        void print(std::ostream& o);     //imprime a pilha
    */
    private:
        Node* m_topo;
        int m_altura;
    //   int* lstValores(const PilhaInt& p);   //transfere todos os valores na pilha para uma lst

    

    public:
        // Seus métodos contendo o seu código
        PilhaInt() {
            m_topo = nullptr;
            m_altura = 0;
        }
        
        PilhaInt& operator<< (int n){
            empilha(n);

            return *this;
        }

        const PilhaInt& operator= (const PilhaInt& p) {
            m_topo = nullptr;
            m_altura = 0;     //O objetivo e reconstruir a pilha atual empilhando todos os elementos de p

            int pV[p.m_altura];      //arr do tamanho da pilha p que sera preenchido de forma em que o valor do fundo da pilha p ocupa pValores[0]

            int* pValores = lstValores(p, pV);
            for(int i=0; i<p.m_altura; i++) empilha(pValores[i]);

            return *this;
        }

        void empilha(int v) {
            Node* temp = new Node;
            temp->valor = v;
            temp->proximo = m_topo;

            m_topo = temp;
            m_altura++;
        }

        int desempilha() {
            const int& desempilhado = m_topo->valor;

            m_topo = m_topo->proximo;

            m_altura--;
            return( desempilhado );
        }

        void print(std::ostream& o) {

            int pValores[m_altura];      //arr do tamanho da pilha p que sera preenchido de forma em que o valor do fundo da pilha p ocupa pValores[0] 
            int* valores = lstValores(*this, pValores);

            for(int i = 0; i<m_altura; i++) {
               
                if (i == 0) o << "[ ";
                if( i != m_altura -1 ){
                    o << valores[i] << ", ";
                } else {
                    o << valores[i] << " ]";
                }
                
            }
        }

    private:
        int* lstValores( const PilhaInt& p, int* pValores){

            Node* temp = new Node;
            temp = p.m_topo;
            
            for (int i = (p.m_altura-1); i>=0; i--) {
                pValores[i] = temp->valor;
                temp = temp->proximo;
            }

            return pValores;
        }
         
};


int main() {
    using namespace std;
    
    PilhaInt p, q;
    q << 2;
    p << 19 << 18 << 17 << 30;
    q = p;
    p.desempilha();
    q << 7;
    stringstream ssp, ssq;
    p.print( ssp );
    q.print( ssq );

    cout << "q = " << ssq.str() << "\n" << "p = " << ssp.str() << endl;

    return 0;
}