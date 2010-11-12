#include <iostream>
#include <carbon/lambda/primitives.hpp>
#include <carbon/lambda/operators.hpp>

using namespace std;
using namespace carbon::lambda;

template<typename F>
void foo(F f)
{
  int i=42;
  cout << f(i, 2) << "\n";
  cout << i << "\n";
}

int main()
{
  foo(arg1=arg1*arg2);
  return 0;
}
