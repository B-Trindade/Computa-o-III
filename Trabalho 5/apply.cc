#include <iostream>
#include <vector>
#include <initializer_list>
#include <map>
#include <string>

using namespace std;

template <typename T, typename F>
auto apply( vector<T> vetor, F function ) {

    vector <decltype(function( vetor[0] ))> applied;

    for( auto i : vetor ) 
        applied.push_back( function(i) );
    
    return( applied );
}

template <typename T, typename F>
auto apply( initializer_list<T> lista, F function ) {

    vector <decltype(function( *lista.begin() ))> applied;

    for( auto i : lista )
        applied.push_back( function(i) );

    return( applied );
}

template <typename T, typename F, int N>
auto apply( T(& arr)[N], F function ) {

    vector <decltype(function( arr[0] ))> applied;
    
    for( int i=0; i<N; i++) 
        applied.push_back( function( arr[i] ));

    return( applied );
}
