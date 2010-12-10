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

#include <carbon/utility/type_functions.hpp>
#include <carbon/utility/vector.hpp>
#include <carbon/utility/intmap.hpp>
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

template<int N>
struct localvar {
  template<typename Vec>
  struct result {
    typedef typename typeat<Vec, intmap_find<N, Vec>::loc>::type pair_type;
    typedef typename carbon::utility::detail::remove_reference<pair_type>::type plain_pair_type;
    typedef typename plain_pair_type::type type;
  };

  template<typename Vec>
  __host__ __device__
  typename result<Vec>::type
  eval(Vec const &args) const {
    return find_c<N>(args).second;
  }
};

actor<localvar<0>  > const _a = localvar<0> ();
actor<localvar<1>  > const _b = localvar<1> ();
actor<localvar<2>  > const _c = localvar<2> ();
actor<localvar<3>  > const _d = localvar<3> ();
actor<localvar<4>  > const _e = localvar<4> ();
actor<localvar<5>  > const _f = localvar<5> ();
actor<localvar<6>  > const _g = localvar<6> ();
actor<localvar<7>  > const _h = localvar<7> ();
actor<localvar<8>  > const _i = localvar<8> ();
actor<localvar<9>  > const _j = localvar<9> ();
actor<localvar<10> > const _k = localvar<10>();
actor<localvar<11> > const _l = localvar<11>();
actor<localvar<12> > const _m = localvar<12>();
actor<localvar<13> > const _n = localvar<13>();
actor<localvar<14> > const _o = localvar<14>();
actor<localvar<15> > const _p = localvar<15>();
actor<localvar<16> > const _q = localvar<16>();
actor<localvar<17> > const _r = localvar<17>();
actor<localvar<18> > const _s = localvar<18>();
actor<localvar<19> > const _t = localvar<19>();
actor<localvar<20> > const _u = localvar<20>();
actor<localvar<21> > const _v = localvar<21>();
actor<localvar<22> > const _w = localvar<22>();
actor<localvar<23> > const _x = localvar<23>();
actor<localvar<24> > const _y = localvar<24>();
actor<localvar<25> > const _z = localvar<25>();

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
