#pragma once

#include <carbon/utility/config.hpp>
#include <carbon/lambda/actor.hpp>
#include <carbon/lambda/composite.hpp>

namespace carbon { namespace lambda {

struct ident_op;
struct negate_op;

struct add_op;
struct sub_op;
struct mul_op;
struct div_op;

template<typename tag_t, typename T>
struct unary_operator;

template<typename T>
struct unary_operator<negate_op, T> {
  typedef T const result_type;

  __host__ __device__
  static result_type eval(T const& v) {
    return -v;
  }
};

template<typename T>
struct unary_operator<ident_op, T> {
  typedef T const result_type;

  __host__ __device__
  static result_type eval(T const& v) {
    return +v;
  }
};

template<typename tag_t, typename T0, typename T1>
struct binary_operator;

#define DEF(TAG, OP)                                            \
template<typename T0, typename T1>                              \
 struct binary_operator<TAG, T0, T1> {                          \
  typedef __typeof__(T0() OP T1()) const result_type;           \
  __host__ __device__                                           \
  static result_type eval(T0 const& lhs, T1 const& rhs) {       \
    return lhs OP rhs;                                          \
  }                                                             \
 };

DEF(add_op, +)
DEF(sub_op, -)
DEF(mul_op, *)
DEF(div_op, /)

#undef DEF

struct negate_op {
  template<typename T0>
  struct result {
    typedef typename unary_operator<negate_op, T0>::result_type type;
  };

  template<typename T0>
  __host__ __device__
  typename unary_operator<negate_op, T0>::result_type
  operator()(T0 &_0) const {
    return unary_operator<negate_op, T0>::eval(_0);
  }
};

template<typename base_t>
__host__ __device__
inline typename detail::make_unary<negate_op, base_t>::type
operator -(actor<base_t> const& _0)
{
  return detail::make_unary<negate_op, base_t>::construct(_0);
}

struct ident_op {
  template<typename T0>
  struct result {
    typedef typename unary_operator<ident_op, T0>::result_type type;
  };

  template<typename T0>
  __host__ __device__
  typename unary_operator<ident_op, T0>::result_type
  operator()(T0 &_0) const {
    return unary_operator<ident_op, T0>::eval(_0);
  }
};

template<typename base_t>
__host__ __device__
inline typename detail::make_unary<ident_op, base_t>::type
operator +(actor<base_t> const& _0)
{
  return detail::make_unary<ident_op, base_t>::construct(_0);
}

} }
