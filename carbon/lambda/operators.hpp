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

template<typename T0, typename T1>
struct binary_operator<add_op, T0, T1> {
  typedef __typeof__(T0() + T1()) const result_type;

  __host__ __device__
  static result_type eval(T0 const& lhs, T1 const& rhs) {
    return lhs + rhs;
  }
};

} }
