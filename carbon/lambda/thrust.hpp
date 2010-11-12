#pragma once

#include <carbon/utility/config.hpp>
#include <carbon/lambda/composite.hpp>
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

} }
