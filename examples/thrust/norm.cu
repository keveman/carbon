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
#include <thrust/transform_reduce.h>
#include <thrust/functional.h>
#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <cmath>

#include <carbon/lambda/primitives.hpp>
#include <carbon/lambda/operators.hpp>

//   This example computes the norm [1] of a vector.  The norm is 
// computed by squaring all numbers in the vector, summing the 
// squares, and taking the square root of the sum of squares.  In
// Thrust this operation is efficiently implemented with the 
// transform_reduce() algorith.  Specifically, we first transform
// x -> x^2 and the compute a standard plus reduction.  Since there
// is no built-in functor for squaring numbers, we define our own
// square functor.
//
// [1] http://en.wikipedia.org/wiki/Norm_(mathematics)#Euclidean_norm


using namespace carbon::lambda;
int main(void)
{
    // initialize host array
    float x[4] = {1.0, 2.0, 3.0, 4.0};

    // transfer to device
    thrust::device_vector<float> d_x(x, x + 4);

    float init = 0;

    // compute norm
    float norm = std::sqrt( thrust::transform_reduce(d_x.begin(), d_x.end(),
                                                     _1*_1,
                                                     init,
                                                     _1+_2) );

    std::cout << "norm is " << norm << std::endl;

    return 0;
}

