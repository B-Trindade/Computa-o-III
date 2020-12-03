/*
                +------------------------------+
                |  10 tests run/ 10 tests passed |
                +------------------------------+

*/

#include <vector>
#include <iostream>
#include <math.h>
#include <string>
#include <map>

#include "apply.cc"

using namespace std;

double seno( double n ) { return sin(n); }
int id( int n ) { return n; }
string roman( int n ) {
    map<int,string> rom = { { 1, "I" }, { 2, "II" }, { 3, "III" }, { 4, "IV" }, { 5, "V" }, { 6, "VI" }, { 7, "VII" }, { 8, "VIII" } } ; 

    return rom[n]; 
}

struct FunctorSimples { 
    string operator()( int n ) { return roman( n ) + "!"; }
};

struct FunctorTemplate { 
    template <typename T>
    T operator()( T n ) { return n+n; }
};

template <typename T>
ostream& operator << ( ostream& o, const vector<T>& v ) {
    o << "[ ";
    for( auto x : v )
        o << x << " ";
        
    return o << "]";
}

int main( int argc, char* argv[]) {     

/* TESTCASE-1 */
  /* CLEAR */

                        // vector<int> v{ 1, 2, 3, 4, 5 };
                        // vector<int> r = ::apply( v, id );
                        // cout << r;

/* TESTCASE-2 */
  /* CLEAR */

                        // vector<int> v{ 1, 2, 3, 4, 5 };
                        // vector<double> r = ::apply( v, seno );
                        // cout << r;

/* TESTCASE-3 */
  /* CLEAR */

                        // auto v = { 1, 2, 3, 4, 5 };
                        // cout << ::apply( v, []( auto n ) -> double { return n*n + 0.1; } );

/* TESTCASE-4 */
  /* CLEAR */


/* TESTCASE-5 */
  /* CLEAR */

                        // auto a = { 1, 2 }, b = { 3, 4 };
                        // cout << ::apply( a, [b]( auto x ) { return ::apply( b, [x]( auto y ){ return vector{ x, y }; } ); } );

/* TESTCASE-6 */
  /* CLEAR */


/* TESTCASE-7 */
  /* CLEAR */


/* TESTCASE-8 */
  /* CLEAR */

                        //cout << ::apply( { 1, 2, 3, 4, 5 }, roman );

/* TESTCASE-9 */
  /* CLEAR */

                        int v[] = { 1, 2, 3, 4, 5 };
                            vector<int> r = ::apply( v, id );
                            cout << r;

/* TESTCASE-10 */
  /* CLEAR */

                        // int v[] = { 1, 2, 3, 4, 5 };
                        // vector<string> r = ::apply( v, roman );
                        // cout << r;

   return 0;
}