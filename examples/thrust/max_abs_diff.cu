#include <thrust/inner_product.h>
#include <thrust/functional.h>
#include <thrust/device_vector.h>

#include <carbon/lambda/primitives.hpp>
#include <carbon/lambda/operators.hpp>
#include <carbon/lambda/thrust.hpp>
#include <iostream>

// this example computes the maximum absolute difference 
// between the elements of two vectors


using namespace carbon::lambda;

int main(void)
{
    thrust::device_vector<float> d_a(4);
    thrust::device_vector<float> d_b(4);

    d_a[0] = 1.0;  d_b[0] = 2.0; 
    d_a[1] = 2.0;  d_b[1] = 4.0;
    d_a[2] = 3.0;  d_b[2] = 3.0;
    d_a[3] = 4.0;  d_b[3] = 0.0;

    // initial value of the reduction
    float init = 0;

    float max_abs_diff = thrust::inner_product(d_a.begin(), d_a.end(), d_b.begin(), init,
                                               max_(_1, _2),
                                               fabsdiff_(_1, _2)); 

    std::cout << "maximum absolute difference: " << max_abs_diff << std::endl;
    return 0;
}

