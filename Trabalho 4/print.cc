/*
                +------------------------------+
                |  5 tests run/ 5 tests passed |
                +------------------------------+

*/


#include <initializer_list>
#include <iostream>
#include <vector>

using namespace std;

class AbstractPair 
{
public:
  virtual void print(ostream& o) = 0;
};

template<typename A, typename B>
class PairImpl : public AbstractPair
{
public:
  PairImpl(A a, B b) {
    m_valorA = a;
    m_valorB = b;
  }
  
  void print(ostream& o) override {
    o << m_valorA << " = " << m_valorB << endl;
  }

private:
  A m_valorA;
  B m_valorB;
};

class Pair 
{
public:
  template <typename A, typename B>
  Pair( A a, B b ) {
    m_p = new PairImpl<A,B>(a,b);
  }
  
  void print(ostream& o) {
    m_p->print(o);
  }

private:
    AbstractPair *m_p;
};

void print( ostream& o, initializer_list<Pair> lista ) {
    for ( Pair par : lista ) {
        par.print(o);
    }
};

int main() {
  Pair p{ "1", "2" };
  print( cout, { { "jan", 1 }, { string( "pi" ), 3.14 }, p } );

  return 0;  
}