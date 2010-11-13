#include <thrust/device_vector.h>
#include <thrust/sequence.h>
#include <thrust/copy.h>
#include <thrust/count.h>
#include <thrust/remove.h>
#include <iostream>
#include <iterator>
#include <string>

#include <carbon/lambda/primitives.hpp>
#include <carbon/lambda/operators.hpp>
using namespace carbon::lambda;

template <typename Iterator>
void print_range(const std::string& name, Iterator first, Iterator last)
{
    typedef typename std::iterator_traits<Iterator>::value_type T;

    std::cout << name << ": ";
    thrust::copy(first, last, std::ostream_iterator<T>(std::cout, " "));  
    std::cout << "\n";
}

int main(void)
{
    // input size
    size_t N = 10;

    // define some types
    typedef thrust::device_vector<int> Vector;
    typedef Vector::iterator           Iterator;

    // allocate storage for array
    Vector values(N);

    // initialize array to [0, 1, 2, ... ]
    thrust::sequence(values.begin(), values.end());
    
    print_range("values", values.begin(), values.end());

    // allocate output storage, here we conservatively assume all values will be copied
    Vector output(values.size());

    // copy odd numbers to separate array
    Iterator output_end = thrust::copy_if(values.begin(), values.end(), output.begin(), _1 % 2);

    print_range("output", output.begin(), output_end);

    // another approach is to count the number of values that will 
    // be copied, and allocate an array of the right size
    size_t N_odd = thrust::count_if(values.begin(), values.end(), _1 % 2);
    
    Vector small_output(N_odd);
    
    thrust::copy_if(values.begin(), values.end(), small_output.begin(), _1 % 2);
    
    print_range("small_output", small_output.begin(), small_output.end());

    // we can also compact sequences with the remove functions, which do the opposite of copy
    Iterator values_end = thrust::remove_if(values.begin(), values.end(), _1 % 2);

    // since the values after values_end are garbage, we'll resize the vector
    values.resize(values_end - values.begin());

    print_range("values", values.begin(), values.end());

    return 0;
}

