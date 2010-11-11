#include <iostream>
#include <carbon/lambda/primitives.hpp>
#include <carbon/lambda/operators.hpp>

using namespace std;
using namespace carbon::lambda;

int main()
{
  cout << arg2(42, 42) << "\n";
  return 0;
}
