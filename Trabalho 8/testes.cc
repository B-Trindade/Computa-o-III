#include <iostream>
#include <map>
#include <vector>
#include <initializer_list>
#include <memory>

#include "print.cc"

using namespace std;

class Leak {
    public:
        Leak(): n( ++contador ) {
            cout << "Criou: " << n << endl;
        }
        
        Leak( const Leak& p ): n( ++contador ) {
            cout << "Criou: " << n << " copiando de " << p.n << endl;
        }
        
        ~Leak() {
            cout << "Destruiu: " << n << endl;
        }
        
        ostream& print( ostream& o ) const {
            return o << "lk(" << n << ")";
        }
        
    private:
        static int contador;
        int n;
};

int Leak::contador = 0;

ostream& operator << ( ostream& o, const Leak& v ) {
    return v.print( o ); 
}

int main() {
    print( cout, { { "jan", Leak() }, { string( "pi" ), Leak() } } ); 
}
