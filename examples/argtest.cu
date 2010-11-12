#include <iostream>
#include <carbon/lambda/primitives.hpp>
#include <carbon/lambda/operators.hpp>
#include <carbon/lambda/statements.hpp>

using namespace std;
using namespace carbon::lambda;

template<typename F>
__global__ void kernel(int *a, F f)
{
  int i=4;
  *a = 0;
  f(*a, i);
}

int main()
{
  cout << arg1(42) << "\n";
  int *da, ha;
  cudaMalloc((void **)&da, sizeof(int));

  kernel<<<1,1>>>(da, while_(arg2)[arg2 = arg2-1, arg1 = arg1 + 1]);

  cudaMemcpy(&ha, da, sizeof(int), cudaMemcpyDeviceToHost);

  cout << ha << "\n";
  return 0;
}