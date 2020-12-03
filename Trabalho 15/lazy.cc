/*
                +------------------------------+
                |  0 tests run/ 0 tests passed |
                +------------------------------+
*/

#include <iostream>
#include <vector>
#include <iterator>
#include <map>
#include <string>

using namespace std;

#define MAX_INT 100

template <typename T, typename F>
auto operator | (const T& collection, F function) {
    constexpr bool is_boolean = is_same<bool, decay_t<decltype( __invoke(function, *begin(collection)) )>>::value;
    //constexpr bool is_void = is_same<void, decay_t<decltype( __invoke(function, *begin(collection)) )>>::value;

    // cout << "is F boolean type? " << to_string(is_boolean) << endl;
    // cout << "is F void type? " << to_string(is_void) << endl;

    if constexpr( is_boolean ) {
        vector <decay_t<decltype( *begin(collection) )>> res;
        for( auto key : collection ) {
            if( __invoke(function, key) == true ) 
                res.push_back(key);
        }
        return res;
    } else if constexpr ( is_same<void, decay_t<decltype( __invoke(function, *begin(collection)) )>>::value ) {
        vector <decay_t<decltype( *begin(collection) )>> res;        
        for( auto key : collection )
            __invoke(function, key);
        return res;
    } else {
        vector <decay_t<decltype( __invoke(function, *begin(collection)) )>> res;
        for( auto key : collection )
            res.push_back( __invoke(function, key) );
        return res;
    }      
}

std::vector<int> Intervalo ( int inicio, int fim) {
    std::vector<int> res;
    for ( int i = inicio; i < fim; ++i ) 
        res.push_back(i);
    return res;
}

template<int FIM = MAX_INT>
std::vector<int> Intervalo ( int inicio) {
    std::vector<int> res;
    for ( int i = inicio; i < FIM; ++i ) 
        res.push_back(i);
    return res;
}

class NPrimeiros
{
public:
    NPrimeiros(int n):
        num(n) {}

    template<typename T>
    auto operator() (T t) {
        return t;
    }
public:
    int num;
};

template<typename T>
auto operator | (const T& collection, NPrimeiros nPrimeiros) {
    vector <decay_t<decltype( *begin(collection ) )>> res;
    int counter = 0;
    for( auto key : collection ) 
        if (counter < nPrimeiros.num ) {
            res.push_back( nPrimeiros(key) );
            counter++;
        }
    return res;
}

struct Impares {
  bool operator()( int n ) {
    return n % 2 == 0;
  }
};



int main() {
    //   int tab[10] =  { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    //   vector<int> v;
    
    //   tab |	 [ &v ]( int x ) { v.push_back( x ); };
    //   v | []( int x ) { return x % 2 == 0; } 
    //     | []( int x ) { return x*x / 10.0; } 
    //     | [] ( double x ) { cout << x << endl; };
    
    //   cout << endl;
    //   return 0;
    auto filtro1 = []( int n ) { return n % 3 == 0; };
    auto filtro2 = []( int n ) { return n % 2 == 0; };
    auto st = Intervalo( 0 ) | filtro1 | filtro2;
    st | NPrimeiros( 10 ) | [](int x){ return x/10.0; } | []( auto x ){ cout << x << ";"; };

}