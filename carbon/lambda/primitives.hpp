#pragma once

#include <carbon/utility/type_functions.hpp>
#include <carbon/utility/vector.hpp>
#include <carbon/lambda/actor.hpp>

namespace carbon { namespace lambda {

using namespace carbon::utility;

template<int N>
struct argument {
  template<typename Vec>
  struct result {
    typedef typename typeat<Vec, N>::type type;
  };

  template<typename Vec>
  __host__ __device__
  typename typeat<Vec, N>::type
  eval(Vec const &args) const {
    return at_c<N>(args);
  }
};

actor<argument<0> > const arg1 = argument<0>();
actor<argument<1> > const arg2 = argument<1>();
actor<argument<2> > const arg3 = argument<2>();
actor<argument<3> > const arg4 = argument<3>();

actor<argument<0> > const _1 = argument<0>();
actor<argument<1> > const _2 = argument<1>();
actor<argument<2> > const _3 = argument<2>();
actor<argument<3> > const _4 = argument<3>();

template<typename T>
struct value {
  typedef typename carbon::utility::detail::remove_reference<T>::type plain_t;

  template<typename Vec>
  struct result {
    typedef plain_t const type;
  };

  plain_t val;
  
  value(plain_t val_) : val(val_) {}

  template<typename Vec>
  __host__ __device__
  plain_t const
  eval(Vec const &) const {
    return val;
  }
};

template<typename T>
__host__ __device__
inline actor<value<T> > const
val(T v)
{
  return value<T>(v);
}

template<typename base_t>
void
val(actor<base_t> const &);

template<typename T>
struct as_actor {
  typedef actor<value<T> > type;

  __host__ __device__
  static type convert(T const& x) {
    return value<T>(x);
  }
};

} }
