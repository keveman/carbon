#pragma once

#include <carbon/utility/config.hpp>
#include <carbon/lambda/actor.hpp>

namespace carbon { namespace lambda {

struct nil_t { char dummy; };

template<typename op_t,
typename A0=nil_t,
typename A1=nil_t,
typename A2=nil_t,
typename A3=nil_t>
struct composite;

template<typename op_t, typename Vec>
struct composite0_result {
  typedef typename op_t::result_type type;
};

template<typename op_t>
struct composite<op_t, nil_t, nil_t, nil_t, nil_t> {
  
  typedef composite<op_t> self_t;

  op_t op;
  
  template<typename Vec>
  struct result {
    typedef typename composite0_result<op_t, Vec>::type type;
  };

  __host__ __device__
  composite(op_t const &op_) : op(op_) {}

  template<typename Vec>
  __host__ __device__
  typename op_t::result_type
  eval(Vec const &) const {
    return op();
  }
};

template<typename op_t, typename Vec, typename A0>
struct composite1_result {
  typedef typename op_t::template result<
  typename actor_result<A0, Vec>::plain_type
  >::type type;
};

template<typename op_t, typename A0>
struct composite<op_t, A0, nil_t, nil_t, nil_t> {

  typedef composite<op_t, A0> self_t;

  op_t op;
  A0 a0;

  template<typename Vec>
  struct result {
    typedef typename composite1_result<op_t, Vec, A0>::type type;
  };

  __host__ __device__
  composite(op_t const &op_, A0 const &a0_)
    : op(op_), a0(a0_) {}

  template<typename Vec>
  __host__ __device__
  typename actor_result<self_t, Vec>::type
  eval(Vec const &args) const {
    typename actor_result<A0, Vec>::type ra = a0.eval(args);
    return op(ra);
  }
};

template<typename op_t, typename Vec, typename A0, typename A1>
struct composite2_result {
  typedef typename op_t::template result<
  typename actor_result<A0, Vec>::plain_type,
  typename actor_result<A1, Vec>::plain_type
  >::type type;
};

template<typename op_t, typename A0, typename A1>
struct composite<op_t, A0, A1, nil_t, nil_t> {

  typedef composite<op_t, A0, A1> self_t;

  op_t op;
  A0 a0;
  A1 a1;

  template<typename Vec>
  struct result {
    typedef typename composite2_result<op_t, Vec, A0, A1>::type type;
  };

  __host__ __device__
  composite(op_t const &op_, A0 const &a0_, A1 const &a1_)
    : op(op_), a0(a0_), a1(a1_) {}

  template<typename Vec>
  __host__ __device__
  typename actor_result<self_t, Vec>::type
  eval(Vec const &args) const {
    typename actor_result<A0, Vec>::type ra = a0.eval(args);
    typename actor_result<A1, Vec>::type rb = a1.eval(args);
    return op(ra, rb);
  }
};

namespace detail {

template<typename op_t,
typename A0=nil_t,
typename A1=nil_t,
typename A2=nil_t,
typename A3=nil_t>
struct make_composite {
  typedef composite<op_t,
  typename as_actor<A0>::type,
  typename as_actor<A1>::type,
  typename as_actor<A2>::type,
  typename as_actor<A3>::type>
  composite_type;

  typedef actor<composite_type> type;
};

template<typename op_t, typename base_t>
struct make_unary {
  typedef typename make_composite<op_t, actor<base_t> >::type type;

  __host__ __device__
  static type
  construct(actor<base_t> const &_0) {
    typedef typename make_composite<op_t, actor<base_t> >::composite_type
      ret_t;

    return ret_t(op_t(), _0);
  }
};

template<typename op_t, typename base_t, typename B>
struct make_binary1 {
  typedef typename make_composite<op_t, actor<base_t>, B>::type type;

  __host__ __device__
  static type
  construct(actor<base_t> const& _0, B const& _1) {
    typedef typename make_composite<op_t, actor<base_t>, B>::composite_type
      ret_t;

    return ret_t(op_t(), _0, as_actor<B>::convert(_1));
  }
};

template<typename op_t, typename A, typename base_t>
struct make_binary2 {
  typedef typename make_composite<op_t, A, actor<base_t> >::type type;

  __host__ __device__
  static type
  construct(A const& _0, actor<base_t> const& _1) {
    typedef typename make_composite<op_t, A, actor<base_t> >::composite_type
      ret_t;

    return ret_t(op_t(), as_actor<A>::convert(_0), _1);
  }
};

template<typename op_t, typename A, typename B>
struct make_binary3 {
  typedef typename make_composite<op_t, actor<A>, actor<B> >::type type;

  __host__ __device__
  static type
  construct(actor<A> const& _0, actor<B> const& _1) {
    typedef typename make_composite<op_t, actor<A>, actor<B> >::composite_type
      ret_t;

    return ret_t(op_t(), _0, _1);
  }
};

}

} }
