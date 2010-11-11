#include <iostream>
#include <carbon/lambda/primitives.hpp>

using namespace std;
using namespace carbon::lambda;

template<typename F>
__global__ void kernel(int *a, F f)
{
  int i=42;
  *a = f(42);
}

int main()
{
  cout << arg1(42) << "\n";
  int *da, ha;
  cudaMalloc((void **)&da, sizeof(int));

  kernel<<<1,1>>>(da, arg1);

  cudaMemcpy(&ha, da, sizeof(int), cudaMemcpyDeviceToHost);

  cout << ha << "\n";
  return 0;
}
