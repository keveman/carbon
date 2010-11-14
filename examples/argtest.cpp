#include <iostream>
#include <carbon/lambda/primitives.hpp>
#include <carbon/lambda/operators.hpp>
#include <carbon/lambda/statements.hpp>
#include <carbon/lambda/functions.hpp>

using namespace std;
using namespace carbon::lambda;

struct fact_impl {

  template<typename Arg>
  struct result {
    typedef Arg type;
  };

  template<typename Arg>
  Arg operator()(Arg n) const {
    return (n <= 0) ? 1 : n * this->operator()(n-1);
  }
};

function<fact_impl> const factorial;

template<typename F>
void foo(F f)
{
  int i=42;
  f(i,10);
  cout << i << "\n";
}

int main()
{
  __typeof__((factorial(arg1))) prog = (factorial(arg1));
  //foo((arg1=factorial(arg2)));
  foo(arg1=prog(10));

  vector_type<int>::type a = make_vector().operator()<int>(2);

  vector_type<intpair<1, int> >::type b = make_vector()(intpair<1, int>(42));

  cout << _b.eval(append_vectors()(a,b)) << "\n";

  int jj;
  let_(_a=41)[let_(_b=1)[_1 = _a+_b]](jj);

  cout << jj << "\n";
  return 0;
}
