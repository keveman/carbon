#pragma once

#include <carbon/utility/config.hpp>
#include <carbon/utility/vector.hpp>

namespace carbon { namespace lambda {

using namespace carbon::utility;

template <typename base_t>
struct actor : public base_t {

  __host__ __device__
  actor() : base_t() {}

  __host__ __device__
  actor(base_t const &base) : base_t(base) {}

  template<typename A0>
  __host__ __device__
  typename base_t::template result<typename make_vector::result<make_vector(A0 &)>::type>::type
  operator()(A0 &a0) const {
    return base_t::eval(make_vector().operator()<A0 &>(a0));
  }

  template<typename A0>
  __host__ __device__
  typename base_t::template result<typename make_vector::result<make_vector(A0 const &)>::type>::type
  operator()(A0 const &a0) const {
    return base_t::eval(make_vector().operator()<A0 const &>(a0));
  }

};

template<typename T>
struct as_actor;

template<typename base_t>
struct as_actor<actor<base_t> > {
  typedef actor<base_t> type;

  __host__ __device__
  static type convert(actor<base_t> const &x) {
    return x;
  }
};

template<>
struct as_actor<void> {
  typedef void type;
};

} }
