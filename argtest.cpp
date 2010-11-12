#include <iostream>
#include <carbon/lambda/primitives.hpp>
#include <carbon/lambda/operators.hpp>
#include <carbon/lambda/statements.hpp>

using namespace std;
using namespace carbon::lambda;

template<typename F>
void foo(F f)
{
  int i=42;
  f(i,2);
  cout << i << "\n";
}

int main()
{
  foo((arg1=arg1*arg2, arg1=1, arg1 = arg1+1));
  return 0;
}
