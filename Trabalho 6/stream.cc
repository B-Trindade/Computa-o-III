/*
                +------------------------------+
                |  4 tests run/ 4 tests passed |
                +------------------------------+

*/

#include <iostream>
#include <vector>

using namespace std;

template <typename T, typename F>
void operator| (T& vetor, F function) {
    for( auto &v : vetor )
        function( v );
}

void print( int x ) { cout << x << " "; }

int main() {

    int tab[10] =  { 1, 2, 3, 2, 3, 4, 6, 0, 1, 8 };
    vector<int> v{ 2 , 6, 8 };
    tab | []( int x ) { cout << x*x << endl; };
    tab | [ &v ]( int x ) { v.push_back( x ); };
    v | []( int x ) { cout << x*x << endl; };
    v | &print;
}