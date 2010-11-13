#include <thrust/device_vector.h>
#include <thrust/scan.h>
#include <thrust/transform.h>
#include <thrust/functional.h>
#include <thrust/sequence.h>
#include <iostream>

#include <carbon/lambda/primitives.hpp>
#include <carbon/lambda/operators.hpp>
using namespace carbon::lambda;

// Efficiently computes the simple moving average (SMA) [1] of a data series
// using a parallel prefix-sum or "scan" operation.
//
// Note: additional numerical precision should be used in the cumulative summing
// stage when computing the SMA of large data series.  The most straightforward 
// remedy is to replace 'float' with 'double'.   Alternatively a Kahan or 
// "compensated" summation algorithm could be applied [2].
//
// [1] http://en.wikipedia.org/wiki/Moving_average#Simple_moving_average
// [2] http://en.wikipedia.org/wiki/Kahan_summation_algorithm


template <typename InputVector, typename OutputVector>
void simple_moving_average(const InputVector& data, size_t w, OutputVector& output)
{
    typedef typename InputVector::value_type T;

    if (data.size() < w)
        return;
    
    // allocate storage for cumulative sum
    thrust::device_vector<T> temp(data.size() + 1);

    // compute cumulative sum
    thrust::exclusive_scan(data.begin(), data.end(), temp.begin());
    temp[data.size()] = data.back() + temp[data.size() - 1];

    // compute moving averages from cumulative sum
    thrust::transform(temp.begin() + w, temp.end(), temp.begin(), output.begin(),
                      (_1 - _2)/w);
}

int main(void)
{
    // length of data series
    size_t n = 30;

    // window size of the moving average
    size_t w = 4;

    // generate random data series
    thrust::device_vector<float> data(n);
    for (size_t i = 0; i < n; i++)
        data[i] = rand() % 9;

    // allocate storage for averages
    thrust::device_vector<float> averages(data.size() - (w - 1));

    // compute SMA using standard summation
    simple_moving_average(data, w, averages);
   
    // print data series
    std::cout << "data series: ";
    for (size_t i = 0; i < data.size(); i++)
        std::cout << data[i] << " ";
    std::cout << std::endl;

    // print moving averages
    for (size_t i = 0; i < averages.size(); i++)
        std::cout << "avg [" << i << ":" << (i + w - 1) << "] = " << averages[i] << std::endl;
}

