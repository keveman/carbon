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
__host__ __device__
inline actor<sequential_composite<actor<baseT0>, actor<baseT1> > >
operator,(actor<baseT0> const& _0, actor<baseT1> const& _1)
{
  return sequential_composite<actor<baseT0>, actor<baseT1> >(_0, _1);
}

template <typename cond_t, typename then_t, typename else_t>
struct if_then_else_composite {

  typedef if_then_else_composite<cond_t, then_t, else_t> self_t;

  template <typename TupleT>
  struct result {
    typedef void type;
  };

  cond_t cond; then_t then; else_t else_;
  
  __host__ __device__
  if_then_else_composite(
                         cond_t const& cond_,
                         then_t const& then_,
                         else_t const& else__)
    :   cond(cond_), then(then_), else_(else__) {}

  template <typename TupleT>
  __host__ __device__
  void eval(TupleT const& args) const {
    if (cond.eval(args))
      then.eval(args);
    else
      else_.eval(args);
  }
};

template <typename cond_t, typename then_t>
struct else_gen {
  cond_t cond; then_t then;

  __host__ __device__
  else_gen(cond_t const& cond_, then_t const& then_)
    :   cond(cond_), then(then_) {}

  template <typename else_t>
  __host__ __device__
  actor<if_then_else_composite<cond_t, then_t,
        typename as_actor<else_t>::type> >
  operator[](else_t const& else_) {
    typedef if_then_else_composite<cond_t, then_t,
      typename as_actor<else_t>::type>
      result;

    return result(cond, then, as_actor<else_t>::convert(else_));
  }
};

template <typename cond_t, typename then_t>
struct if_then_composite {

  typedef if_then_composite<cond_t, then_t> self_t;

  cond_t cond; then_t then;
  else_gen<cond_t, then_t> else_;
  
  template <typename TupleT>
  struct result { typedef void type; };

  __host__ __device__
  if_then_composite(cond_t const& cond_, then_t const& then_)
    :   cond(cond_), then(then_), else_(cond, then) {}

  template <typename TupleT>
  __host__ __device__
  void eval(TupleT const& args) const {
    if (cond.eval(args))
      then.eval(args);
  }
};

template <typename cond_t>
struct if_gen {

  cond_t cond;

  __host__ __device__
  if_gen(cond_t const& cond_)
    :   cond(cond_) {}

  template <typename then_t>
  __host__ __device__
  actor<if_then_composite<
        typename as_actor<cond_t>::type,
        typename as_actor<then_t>::type> >
  operator[](then_t const& then) const {
    typedef if_then_composite<
    typename as_actor<cond_t>::type,
      typename as_actor<then_t>::type>
    result;

    return result(
                  as_actor<cond_t>::convert(cond),
                  as_actor<then_t>::convert(then));
  }
};

template <typename cond_t>
__host__ __device__
inline if_gen<cond_t>
if_(cond_t const& cond)
{
  return if_gen<cond_t>(cond);
}

template <typename cond_t, typename do_t>
struct while_composite {

  typedef while_composite<cond_t, do_t> self_t;

  template <typename TupleT>
  struct result { typedef void type; };

  cond_t cond;
  do_t do_;

  __host__ __device__
  while_composite(cond_t const& cond_, do_t const& do__)
    :   cond(cond_), do_(do__) {}

  template <typename TupleT>
  __host__ __device__
  void eval(TupleT const& args) const {
    while (cond.eval(args))
      do_.eval(args);
  }
};

template <typename cond_t>
struct while_gen {

  cond_t cond;

  __host__ __device__
  while_gen(cond_t const& cond_)
    :   cond(cond_) {}

  template <typename do_t>
  __host__ __device__
  actor<while_composite<
        typename as_actor<cond_t>::type,
        typename as_actor<do_t>::type> >
  operator[](do_t const& do_) const {
    typedef while_composite<
    typename as_actor<cond_t>::type,
      typename as_actor<do_t>::type>
    result;

    return result(
                  as_actor<cond_t>::convert(cond),
                  as_actor<do_t>::convert(do_));
  }
};

template <typename cond_t>
__host__ __device__
inline while_gen<cond_t>
while_(cond_t const& cond)
{
  return while_gen<cond_t>(cond);
}

} }
