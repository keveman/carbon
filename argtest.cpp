#include <iostream>
#include <carbon/lambda/primitives.hpp>
#include <carbon/lambda/composite.hpp>

using namespace std;
using namespace carbon::lambda;

int main()
{
  cout << arg1(42) << "\n";
  return 0;
}
