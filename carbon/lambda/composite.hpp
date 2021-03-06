/*
 *  Copyright 2010-2012 NVIDIA Corporation
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

// Based on Boost.Phoenix v1.2
// Copyright (c) 2001-2002 Joel de Guzman

#pragma once

#include <carbon/utility/config.hpp>
#include <carbon/lambda/actor.hpp>

namespace carbon { namespace lambda {

template<typename op_t,
typename A0=nil_t,
typename A1=nil_t,
typename A2=nil_t,
typename A3=nil_t,
typename A4=nil_t,
typename A5=nil_t,
typename=nil_t>
struct composite;

template<typename op_t, typename Vec>
struct composite0_result {
  typedef typename op_t::result_type type;
};

template<typename op_t>
struct composite<op_t, nil_t, nil_t, nil_t, nil_t, nil_t, nil_t, nil_t> {
  
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
struct composite<op_t, A0, nil_t, nil_t, nil_t, nil_t, nil_t, nil_t> {

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
struct composite<op_t, A0, A1, nil_t, nil_t, nil_t, nil_t, nil_t> {

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

template<typename op_t, typename Vec, typename A0, typename A1, typename A2>
struct composite3_result {
  typedef typename op_t::template result<
  typename actor_result<A0, Vec>::plain_type,
  typename actor_result<A1, Vec>::plain_type,
  typename actor_result<A2, Vec>::plain_type
  >::type type;
};

template<typename op_t, typename A0, typename A1, typename A2>
struct composite<op_t, A0, A1, A2, nil_t, nil_t, nil_t, nil_t> {

  typedef composite<op_t, A0, A1, A2> self_t;

  op_t op;
  A0 a0;
  A1 a1;
  A2 a2;
  
  template<typename Vec>
  struct result {
    typedef typename composite3_result<op_t, Vec, A0, A1, A2>::type type;
  };

  __host__ __device__
  composite(op_t const &op_, A0 const &a0_, A1 const &a1_, A2 const &a2_)
    : op(op_), a0(a0_), a1(a1_), a2(a2_) {}

  template<typename Vec>
  __host__ __device__
  typename actor_result<self_t, Vec>::type
  eval(Vec const &args) const {
    typename actor_result<A0, Vec>::type ra = a0.eval(args);
    typename actor_result<A1, Vec>::type rb = a1.eval(args);
    typename actor_result<A2, Vec>::type rc = a2.eval(args);
    return op(ra, rb, rc);
  }
};

template<typename op_t, typename Vec, typename A0, typename A1, typename A2, typename A3>
struct composite4_result {
  typedef typename op_t::template result<
  typename actor_result<A0, Vec>::plain_type,
  typename actor_result<A1, Vec>::plain_type,
  typename actor_result<A2, Vec>::plain_type,
  typename actor_result<A3, Vec>::plain_type
  >::type type;
};

template<typename op_t, typename A0, typename A1, typename A2, typename A3>
struct composite<op_t, A0, A1, A2, A3, nil_t, nil_t, nil_t> {

  typedef composite<op_t, A0, A1, A2, A3> self_t;

  op_t op;
  A0 a0;
  A1 a1;
  A2 a2;
  A3 a3;
  
  template<typename Vec>
  struct result {
    typedef typename composite4_result<op_t, Vec, A0, A1, A2, A3>::type type;
  };

  __host__ __device__
  composite(op_t const &op_, A0 const &a0_, A1 const &a1_, A2 const &a2_, A3 const &a3_)
    : op(op_), a0(a0_), a1(a1_), a2(a2_), a3(a3_) {}

  template<typename Vec>
  __host__ __device__
  typename actor_result<self_t, Vec>::type
  eval(Vec const &args) const {
    typename actor_result<A0, Vec>::type ra = a0.eval(args);
    typename actor_result<A1, Vec>::type rb = a1.eval(args);
    typename actor_result<A2, Vec>::type rc = a2.eval(args);
    typename actor_result<A3, Vec>::type rd = a3.eval(args);
    return op(ra, rb, rc, rd);
  }
};

template<typename op_t, typename Vec, typename A0, typename A1, typename A2, typename A3, typename A4>
struct composite5_result {
  typedef typename op_t::template result<
  typename actor_result<A0, Vec>::plain_type,
  typename actor_result<A1, Vec>::plain_type,
  typename actor_result<A2, Vec>::plain_type,
  typename actor_result<A3, Vec>::plain_type,
  typename actor_result<A4, Vec>::plain_type
  >::type type;
};

template<typename op_t, typename A0, typename A1, typename A2, typename A3, typename A4>
struct composite<op_t, A0, A1, A2, A3, A4, nil_t, nil_t> {

  typedef composite<op_t, A0, A1, A2, A3, A4> self_t;

  op_t op;
  A0 a0;
  A1 a1;
  A2 a2;
  A3 a3;
  A4 a4;
  
  template<typename Vec>
  struct result {
    typedef typename composite5_result<op_t, Vec, A0, A1, A2, A3, A4>::type type;
  };

  __host__ __device__
  composite(op_t const &op_, A0 const &a0_, A1 const &a1_, A2 const &a2_, A3 const &a3_, A4 const &a4_)
    : op(op_), a0(a0_), a1(a1_), a2(a2_), a3(a3_), a4(a4_) {}

  template<typename Vec>
  __host__ __device__
  typename actor_result<self_t, Vec>::type
  eval(Vec const &args) const {
    typename actor_result<A0, Vec>::type ra = a0.eval(args);
    typename actor_result<A1, Vec>::type rb = a1.eval(args);
    typename actor_result<A2, Vec>::type rc = a2.eval(args);
    typename actor_result<A3, Vec>::type rd = a3.eval(args);
    typename actor_result<A4, Vec>::type re = a4.eval(args);
    return op(ra, rb, rc, rd, re);
  }
};

template<typename op_t, typename Vec, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5>
struct composite6_result {
  typedef typename op_t::template result<
  typename actor_result<A0, Vec>::plain_type,
  typename actor_result<A1, Vec>::plain_type,
  typename actor_result<A2, Vec>::plain_type,
  typename actor_result<A3, Vec>::plain_type,
  typename actor_result<A4, Vec>::plain_type,
  typename actor_result<A5, Vec>::plain_type
  >::type type;
};

template<typename op_t, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5>
struct composite<op_t, A0, A1, A2, A3, A4, A5, nil_t> {

  typedef composite<op_t, A0, A1, A2, A3, A4, A5> self_t;

  op_t op;
  A0 a0;
  A1 a1;
  A2 a2;
  A3 a3;
  A4 a4;
  A5 a5;
  
  template<typename Vec>
  struct result {
    typedef typename composite6_result<op_t, Vec, A0, A1, A2, A3, A4, A5>::type type;
  };

  __host__ __device__
  composite(op_t const &op_, A0 const &a0_, A1 const &a1_, A2 const &a2_, A3 const &a3_, A4 const &a4_,
            A5 const &a5_)
    : op(op_), a0(a0_), a1(a1_), a2(a2_), a3(a3_), a4(a4_), a5(a5_) {}

  template<typename Vec>
  __host__ __device__
  typename actor_result<self_t, Vec>::type
  eval(Vec const &args) const {
    typename actor_result<A0, Vec>::type ra = a0.eval(args);
    typename actor_result<A1, Vec>::type rb = a1.eval(args);
    typename actor_result<A2, Vec>::type rc = a2.eval(args);
    typename actor_result<A3, Vec>::type rd = a3.eval(args);
    typename actor_result<A4, Vec>::type re = a4.eval(args);
    typename actor_result<A5, Vec>::type rf = a5.eval(args);
    return op(ra, rb, rc, rd, re, rf);
  }
};

namespace detail {

template<typename op_t,
typename A0=nil_t,
typename A1=nil_t,
typename A2=nil_t,
typename A3=nil_t,
typename A4=nil_t,
typename A5=nil_t>
struct make_composite {
  typedef composite<op_t,
  typename as_actor<A0>::type,
  typename as_actor<A1>::type,
  typename as_actor<A2>::type,
  typename as_actor<A3>::type,
  typename as_actor<A4>::type,
  typename as_actor<A5>::type>
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
