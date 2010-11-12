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
  foo((arg1=factorial(arg2)));
  return 0;
}
