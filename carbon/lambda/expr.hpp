#pragma once
#include <carbon/utility/type_functions.hpp>

namespace carbon { namespace lambda {

using carbon::utility::detail::enable_if_c;
using carbon::utility::detail::is_same;

struct filler {};

namespace tag {

#define TAG(x)                                  \
struct x {};                                    \
 template<typename T>                           \
 struct is_tag_##x {                            \
   static const bool value = false;             \
 };                                             \
 template<>                                     \
 struct is_tag_##x<x> {                         \
   static const bool value = true;              \
 };

TAG(add)
TAG(sub)
TAG(mul)
TAG(div)
TAG(func)
TAG(subscript)
TAG(term)
TAG(assign)
TAG(comma)
TAG(iftag)
TAG(itetag)

#undef TAG
}

template<typename tag,
typename C0=filler,
typename C1=filler,
typename C2=filler,
typename C3=filler>
struct expr;

template<typename T>
struct isexpr;

template<typename thetag,
typename C0,
typename C1,
typename C2,
typename C3>
struct expr {
  C0 c0;
  C1 c1;
  C2 c2;
  C3 c3;

  typedef expr<thetag, C0, C1, C2, C3> type;

  template<typename RHS>
  typename enable_if_c<isexpr<RHS>::value,
  expr<tag::subscript, type, RHS> >::type
  operator [](const RHS &rhs) const {
    expr<tag::subscript, type, RHS> retval = {*this, rhs};
    return retval;
  }

  template<typename RHS>
  typename enable_if_c<!isexpr<RHS>::value,
  expr<tag::subscript, type, expr<tag::term, RHS> > >::type
  operator [](const RHS &rhs) const {
    expr<tag::term, RHS> t = {rhs};
    expr<tag::subscript, type, expr<tag::term, RHS> > retval = {*this, t};
    return retval;
  }

  template<typename RHS>
  typename enable_if_c<isexpr<RHS>::value && tag::is_tag_term<thetag>::value,
  expr<tag::assign, type, RHS> >::type
  operator =(const RHS &rhs) const {
    expr<tag::assign, type, RHS> retval = {*this, rhs};
    return retval;
  }

  template<typename RHS>
  typename enable_if_c<(!isexpr<RHS>::value) && tag::is_tag_term<thetag>::value,
  expr<tag::assign, type, expr<tag::term, RHS> > >::type
  operator =(const RHS &rhs) const {
    expr<tag::term, RHS> t = {rhs};
    expr<tag::assign, type, expr<tag::term, RHS> > retval = {*this, t};
    return retval;
  }

};

template<int>
struct arg {};

template<int>
struct localvar {};

template<typename T>
struct isexpr {
  static const bool value = false;
};

template<typename thetag, typename C0, typename C1, typename C2, typename C3>
struct isexpr<expr<thetag, C0, C1, C2, C3> > {
  static const bool value = true;
};

#define DEF(TAG, OP)                                                    \
template<typename LHS, typename RHS>                                    \
 typename enable_if_c<(isexpr<LHS>::value && isexpr<RHS>::value),       \
expr<TAG, LHS, RHS> >::type                                             \
 operator OP(const LHS &lhs, const RHS &rhs)                            \
{                                                                       \
  expr<TAG, LHS, RHS> e = { lhs, rhs };                                 \
  return e;                                                             \
}                                                                       \
 template<typename LHS, typename RHS>                                   \
 typename enable_if_c<(isexpr<LHS>::value && !(isexpr<RHS>::value)),    \
 expr<TAG, LHS, expr<tag::term, RHS> > >::type                          \
 operator OP(const LHS &lhs, const RHS &rhs)                            \
 {                                                                      \
   expr<tag::term, RHS> rhsterm = { rhs };                              \
   expr<TAG, LHS, expr<tag::term, RHS> > e = { lhs, rhsterm };          \
   return e;                                                            \
 }                                                                      \
 template<typename LHS, typename RHS>                                   \
 typename enable_if_c<(!(isexpr<LHS>::value) && isexpr<RHS>::value),    \
 expr<TAG, expr<tag::term, LHS>, RHS> >::type                           \
 operator OP(const LHS &lhs, const RHS &rhs)                            \
 {                                                                      \
   expr<tag::term, LHS> lhsterm = { lhs };                              \
   expr<TAG, expr<tag::term, LHS>, RHS> e = { lhsterm, rhs };           \
   return e;                                                            \
 }

DEF(tag::add, +)
DEF(tag::sub, -)
DEF(tag::mul, *)
DEF(tag::div, /)
#define COMMA ,
DEF(tag::comma, COMMA)
#undef COMMA
#undef DEF

template<typename E,
typename TAG, typename C0=filler, typename C1=filler, typename C2=filler, typename C3=filler>
struct matches {
  static const bool value = false;
};

struct _ ;

template<typename TAG, typename C0, typename C1, typename C2, typename C3,
typename D0, typename D1, typename D2, typename D3>
struct matches<expr<TAG, C0, C1, C2, C3>, TAG, D0, D1, D2, D3> {
  static const bool v1 = is_same<C0, D0>::value || is_same<D0, _>::value;
  static const bool v2 = is_same<C1, D1>::value || is_same<D1, _>::value;
  static const bool v3 = is_same<C2, D2>::value || is_same<D2, _>::value;
  static const bool v4 = is_same<C3, D3>::value || is_same<D3, _>::value;

  static const bool value = v1 && v2 && v3 && v4;
};

static const expr<tag::term, arg<0> > _1 = {{}};
static const expr<tag::term, arg<1> > _2 = {{}};
static const expr<tag::term, arg<2> > _3 = {{}};
static const expr<tag::term, arg<3> > _4 = {{}};

static const expr<tag::term, localvar<0> > _a = {{}};
static const expr<tag::term, localvar<1> > _b = {{}};
static const expr<tag::term, localvar<2> > _c = {{}};
static const expr<tag::term, localvar<3> > _d = {{}};

template<typename RHS>
typename enable_if_c<isexpr<RHS>::value,
expr<tag::iftag, RHS> >::type
if_(const RHS &e) {
  expr<tag::iftag, RHS> retval = {e};
  return retval;
}

template<typename RHS>
typename enable_if_c<!isexpr<RHS>::value,
expr<tag::iftag, expr<tag::term, RHS> > >::type
if_(const RHS &e) {
  expr<tag::term, RHS> t = {e};
  expr<tag::iftag, expr<tag::term, RHS> > retval = {t};
  return retval;
}

} }
