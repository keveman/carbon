#pragma once

#include <carbon/lambda/composite.hpp>

namespace carbon { namespace lambda {

template <typename A0, typename A1>
struct sequential_composite {

  typedef sequential_composite<A0, A1> self_t;

  template <typename Vec>
  struct result { typedef void type; };

  A0 a0; A1 a1;

  __host__ __device__
  sequential_composite(A0 const& _0, A1 const& _1)
    :   a0(_0), a1(_1) {}

  template <typename Vec>
  __host__ __device__
  void
  eval(Vec const& args) const
  {
    a0.eval(args);
    a1.eval(args);
  }

};

template <typename baseT0, typename baseT1>
inline actor<sequential_composite<actor<baseT0>, actor<baseT1> > >
operator,(actor<baseT0> const& _0, actor<baseT1> const& _1)
{
  return sequential_composite<actor<baseT0>, actor<baseT1> >(_0, _1);
}

} }
