#include <thrust/transform.h>
#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <thrust/functional.h>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <carbon/lambda/primitives.hpp>
#include <carbon/lambda/operators.hpp>

void saxpy_fast(float A, thrust::device_vector<float>& X, thrust::device_vector<float>& Y)
{
  using namespace carbon::lambda;

  thrust::transform(X.begin(), X.end(), Y.begin(), Y.begin(), A*_1 + _2);
}

void saxpy_slow(float A, thrust::device_vector<float>& X, thrust::device_vector<float>& Y)
{
    thrust::device_vector<float> temp(X.size());
   
    // temp <- A
    thrust::fill(temp.begin(), temp.end(), A);
    
    // temp <- A * X
    thrust::transform(X.begin(), X.end(), temp.begin(), temp.begin(), thrust::multiplies<float>());

    // Y <- A * X + Y
    thrust::transform(temp.begin(), temp.end(), Y.begin(), Y.begin(), thrust::plus<float>());
}

int main(void)
{
    // initialize host arrays
    float x[4] = {1.0, 1.0, 1.0, 1.0};
    float y[4] = {1.0, 2.0, 3.0, 4.0};

    {
        // transfer to device
        thrust::device_vector<float> X(x, x + 4);
        thrust::device_vector<float> Y(y, y + 4);

        // slow method
        saxpy_slow(2.0, X, Y);
    }

    {
        // transfer to device
        thrust::device_vector<float> X(x, x + 4);
        thrust::device_vector<float> Y(y, y + 4);

        // fast method
        saxpy_fast(2.0, X, Y);
    }
    
    return 0;
}

