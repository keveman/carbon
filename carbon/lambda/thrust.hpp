#pragma once

#include <carbon/utility/config.hpp>
#include <carbon/lambda/composite.hpp>
#include <carbon/lambda/functions.hpp>
#include <thrust/tuple.h>

namespace carbon { namespace lambda {

template<int N>
struct get_impl {
  template<typename Arg>
  struct result {
    typedef typename thrust::tuple_element<N, Arg>::type type;
  };

  template<typename Arg>
  __host__ __device__
  typename thrust::tuple_element<N, Arg>::type
  operator()(Arg const &arg) const {
    return thrust::get<N>(arg);
  }
};

template<int N, typename A0>
__host__ __device__
typename detail::make_composite<get_impl<N>, A0>::type
get_(A0 const &_a0)
{
  typedef typename detail::make_composite<get_impl<N>, A0>::composite_type
    ret_t;
  return ret_t(get_impl<N>(), as_actor<A0>::convert(_a0));
}

struct fabsdiff_impl {
  template<typename T0, typename T1>
  struct result;

  __host__ __device__
  float operator()(float const &a, float const &b) const {
    return fabs(b - a);
  }
};

template<>
struct fabsdiff_impl::result<float, float> {
  typedef float type;
};

function<fabsdiff_impl> const fabsdiff_;

struct max_impl {
  template<typename T0, typename T1>
  struct result;

  template<typename T>
  struct result<T, T> {
    typedef T type;
  };
  
  template<typename T>
  __host__ __device__
  T operator()(T const &a, T const &b) const {
    return max(a, b);
  }
};

function<max_impl> const max_;

} }
