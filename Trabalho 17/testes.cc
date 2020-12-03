#include <iostream>
#include <vector>
#include <math.h>
#include <string>
#include <string.h>

using namespace std;

#include "lambda2.cc"

vector<int> operator + ( const vector<int>& v, int n ) {
    vector<int> result{ v };
    result.push_back( n );
    return result;
}

int main() {
    // Test 1:
    std::cout << "Teste 1:\t";
    // std::vector<int> l{ 1, 0, 2, 0, 3 };
    // l | []( auto v ) { return v != 0; } | std::cout << x << ' ';
    std::cout << "\n\n";

    // Test 2:
    std::cout << "Teste 2:\t";
    // std::vector<std::vector<int>> z{ { 1, 2, 3 }, { 0, 3, 7 }, { 1, 3 } };
    // z | []( auto v ) { return v[0] != 0; } | (x | std::cout << x << ' ');
    std::cout << "\n\n";

    // Test 3:
    std::cout << "Teste 3:\t";
    // vector< vector<int> > m{ { 1, 2, 3 }, { 0, 3, 7 }, { 1, 3 } };
    // m | x[0] != 0 | ( x | cout << x << ' ' );
    std::cout << "\n\n";

    // Test 4:
    std::cout << "Teste 4:\t";
    std::vector<std::vector<int>> o{ { 1, 2, 3 }, { 0, 3, 7 }, { 1, 3 } };
    o | x[0] != 0 | (( x + 7 )| std::cout << x << ' ' );
    std::cout << "\n\n";
}