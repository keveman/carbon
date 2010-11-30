
//          Copyright Manjunath Kudlur 2010 - 2012
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// Based on Boost.Phoenix v1.2
// Copyright (c) 2001-2002 Joel de Guzman
#pragma once

#include <carbon/utility/type_functions.hpp>
#include <carbon/utility/config.hpp>
#include <carbon/utility/vector.hpp>

namespace carbon { namespace lambda {

struct nil_t { char dummy; };

struct assign_op;
//struct index_op;

namespace detail {
template<typename op_t, typename base_t, typename B>
struct make_binary1;
}
using namespace carbon::utility;

template <typename actor_t, typename Vec>
struct actor_result {

  typedef typename actor_t::template result<Vec>::type type;
  typedef typename carbon::utility::detail::remove_reference<type>::type plain_type;
};

template <typename base_t>
struct actor : public base_t {

  __host__ __device__
  actor() : base_t() {}

  __host__ __device__
  actor(base_t const &base) : base_t(base) {}

  template<typename A0>
  __host__ __device__
  typename base_t::template result<typename make_vector::template result<make_vector(A0 &)>::type>::type
  operator()(A0 &a0) const {
    return base_t::eval(make_vector().operator()<A0 &>(a0));
  }

  template<typename A0>
  __host__ __device__
  typename base_t::template result<typename make_vector::template result<make_vector(A0 const &)>::type>::type
  operator()(A0 const &a0) const {
    return base_t::eval(make_vector().operator()<A0 const &>(a0));
  }

  template<typename A0, typename A1>
  __host__ __device__
  typename base_t::template result<typename make_vector::template result<make_vector(A0 &, A1 &)>::type>::type
  operator()(A0 &a0, A1 &a1) const {
    return base_t::eval(make_vector().operator()<A0 &, A1 &>(a0, a1));
  }

  template<typename A0, typename A1>
  __host__ __device__
  typename base_t::template result<typename make_vector::template result<make_vector(A0 const&, A1 &)>::type>::type
  operator()(A0 const &a0, A1 &a1) const {
    return base_t::eval(make_vector().operator()<A0 const&, A1 &>(a0, a1));
  }

  template<typename A0, typename A1>
  __host__ __device__
  typename base_t::template result<typename make_vector::template result<make_vector(A0 &, A1 const&)>::type>::type
  operator()(A0 &a0, A1 const &a1) const {
    return base_t::eval(make_vector().operator()<A0 &, A1 const&>(a0, a1));
  }

  template<typename A0, typename A1>
  __host__ __device__
  typename base_t::template result<typename make_vector::template result<make_vector(A0 const&, A1 const&)>::type>::type
  operator()(A0 const &a0, A1 const &a1) const {
    return base_t::eval(make_vector().operator()<A0 const&, A1 const&>(a0, a1));
  }

#define DEF(X0, CX0, x0, X1, CX1, x1, X2, CX2, x2)                      \
template<typename X0, typename X1, typename X2>                         \
 __host__ __device__                                                    \
 typename base_t::template result<typename make_vector::template result<make_vector(X0 CX0 &, X1 CX1 &, X2 CX2 &)>::type>::type \
 operator()(X0 CX0 & x0, X1 CX1 & x1, X2 CX2 & x2) const {              \
  return base_t::eval(make_vector().operator()<X0 CX0 &, X1 CX1 &, X2 CX2 &>(x0, x1, x2)); \
}                                                                       \
/**/
  DEF(A0, , a0, A1, , a1, A2, , a2)
  DEF(A0, , a0, A1, , a1, A2, const, a2)
  DEF(A0, , a0, A1, const, a1, A2, , a2)
  DEF(A0, , a0, A1, const, a1, A2, const, a2)
  DEF(A0, const, a0, A1, , a1, A2, , a2)
  DEF(A0, const, a0, A1, , a1, A2, const, a2)
  DEF(A0, const, a0, A1, const, a1, A2, , a2)
  DEF(A0, const, a0, A1, const, a1, A2, const, a2)

#undef DEF

#define DEF(X0, CX0, x0, X1, CX1, x1, X2, CX2, x2, X3, CX3, x3)         \
template<typename X0, typename X1, typename X2, typename X3>            \
 __host__ __device__                                                    \
 typename base_t::template result<typename make_vector::template result<make_vector(X0 CX0 &, X1 CX1 &, X2 CX2 &, X3 CX3 &)>::type>::type \
 operator()(X0 CX0 & x0, X1 CX1 & x1, X2 CX2 & x2, X3 CX3 & x3) const { \
  return base_t::eval(make_vector().operator()<X0 CX0 &, X1 CX1 &, X2 CX2 &, X3 CX3 &>(x0, x1, x2, x3)); \
}                                                                       \
/**/

  DEF(A0, , a0, A1, , a1, A2, , a2, A3, , a3)
  DEF(A0, , a0, A1, , a1, A2, , a2, A3, const, a3)
  DEF(A0, , a0, A1, , a1, A2, const, a2, A3, , a3)
  DEF(A0, , a0, A1, , a1, A2, const, a2, A3, const, a3)
  DEF(A0, , a0, A1, const, a1, A2, , a2, A3, , a3)
  DEF(A0, , a0, A1, const, a1, A2, , a2, A3, const, a3)
  DEF(A0, , a0, A1, const, a1, A2, const, a2, A3, , a3)
  DEF(A0, , a0, A1, const, a1, A2, const, a2, A3, const, a3)
  DEF(A0, const, a0, A1, , a1, A2, , a2, A3, , a3)
  DEF(A0, const, a0, A1, , a1, A2, , a2, A3, const, a3)
  DEF(A0, const, a0, A1, , a1, A2, const, a2, A3, , a3)
  DEF(A0, const, a0, A1, , a1, A2, const, a2, A3, const, a3)
  DEF(A0, const, a0, A1, const, a1, A2, , a2, A3, , a3)
  DEF(A0, const, a0, A1, const, a1, A2, , a2, A3, const, a3)
  DEF(A0, const, a0, A1, const, a1, A2, const, a2, A3, , a3)
  DEF(A0, const, a0, A1, const, a1, A2, const, a2, A3, const, a3)
#undef DEF
  
  template<typename B>
  __host__ __device__
  typename detail::make_binary1<assign_op, base_t, B>::type
  operator =(B const &b) const {
    return detail::make_binary1<assign_op, base_t, B>::construct(*this, b);
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

template <>
struct as_actor<nil_t> {

  typedef nil_t type;
  __host__ __device__
  static nil_t convert(nil_t /*x*/)
  { return nil_t(); }
};

template<>
struct as_actor<void> {
  typedef void type;
};

} }
