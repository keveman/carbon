/*
 *  Copyright 2010-2012 NVIDIA Corporation
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

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
