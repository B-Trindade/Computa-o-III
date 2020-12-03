/*
                +------------------------------+
                |  5 tests run/ 5 tests passed |
                +------------------------------+

*/


#include <initializer_list>
#include <iostream>
#include <vector>
#include <memory>

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
  PairImpl(A& a, B& b) {
    m_valorA = a;
    m_ptr_to_B = make_shared<B>(b);
  }
  
  void print(ostream& o) override {
    o << m_valorA << " = " << *m_ptr_to_B << endl;
  }

private:
  A m_valorA;
  shared_ptr<B> m_ptr_to_B;
};

class Pair 
{
public:
  template <typename A, typename B>
  Pair( A a, B b ) {
    m_p = make_shared<PairImpl<A,B>>(a,b);
  }
  
  void print(ostream& o) {
    m_p->print(o);
  }

  ~Pair() {
  }

private:
    shared_ptr<AbstractPair> m_p;
};

void print( ostream& o, initializer_list<Pair> lista ) {
    for ( Pair par : lista ) {
        par.print(o);
    }
};

//  int main() {
// //   Pair p{ "1", "2" };
// //   print( cout, { { "jan", 1 }, { string( "pi" ), 3.14 }, p } );

//   return 0; 
//  } 