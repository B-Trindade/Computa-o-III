/*
                +------------------------------+
                |  8 tests run/ 8 tests passed |
                +------------------------------+
*/

#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

template <typename T, typename F>
auto operator | (const T& collection, F function) {
    constexpr bool is_boolean = is_same<bool, decay_t<decltype( __invoke(function, *begin(collection)) )>>::value;
    constexpr bool is_void = is_same<void, decay_t<decltype( __invoke(function, *begin(collection)) )>>::value;

    // cout << "is F boolean type? " << to_string(is_boolean) << endl;
    // cout << "is F void type? " << to_string(is_void) << endl;

    if constexpr( is_boolean ) {
        vector <decay_t<decltype( *begin(collection) )>> res;
        for( auto key : collection ) {
            if( __invoke(function, key) == true ) 
                res.push_back(key);
        }
        return res;
    } else if constexpr ( is_void ) {
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


int main() {
    // vector<int> v1 = { 2, 9, 8, 8, 7, 4 };
    // auto result0 = v1 | []( int x ) { return x % 2 == 0; };
    // for( auto x : result0 )
    //     cout << x << " ";
    // cout << endl;

    // vector<int> v2 = { 2, 9, 8, 8, 7, 4 };
    // v2 | []( int x ) { return x % 2 == 0; } | [] ( int x ) { cout << x << " "; };
    // cout << endl;

    // int v3[] = { 2, 9, 8, 8, 7, 4 };
    // auto result = v3 | []( int x ) { return x % 2 == 0; };
    // for( auto x : result )
    //     cout << x << " ";

    // map<string,string> m = { { "a", "1" }, { "b", "2" }, { "c", "3" }, { "d", "4" }, { "e", "5" } };
    // m | []( auto x ){ return make_pair( x.first, stod( x.second ) ); } | []( auto p ) { cout << p.second + 1.1 << " "; };
    // cout << endl;

    // map<string,string> v = { { "a", "1" }, { "b", "2" }, { "c", "3" }, { "d", "4" }, { "e", "5" }, { "f", "6" } };
    // auto par = []( auto x ){ return stoi( x.second ) % 2 == 0; };
    // auto upper_first = []( auto x ){ string st = x.first; transform(st.begin(), st.end(), st.begin(), ::toupper); return st; };
    // v | par | upper_first | []( auto st ) { cout << st + "! "; };
    // cout << endl;

    vector<string> v1 = { "janeiro", "fevereiro", "março", "abril", "maio" };
    v1 | &string::length | [] ( int x ) { cout << x << " "; };
    cout << endl;
}