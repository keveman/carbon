#pragma once

#include <carbon/utility/config.hpp>
#include <carbon/lambda/actor.hpp>
#include <carbon/lambda/composite.hpp>

namespace carbon { namespace lambda {

template<typename op_t>
struct function {

  op_t op;
  
  __host__ __device__
  function () : op() {}

  __host__ __device__
  actor<composite<op_t> >
  operator()() const {
    return actor<composite<op_t> >(op);
  }

  template<typename A0>
  __host__ __device__
  typename detail::make_composite<op_t, A0>::type
  operator()(A0 const &_a0) const {
    typedef typename detail::make_composite<op_t, A0>::composite_type
      ret_t;
    return ret_t(op, as_actor<A0>::convert(_a0));
  }

  template<typename A0, typename A1>
  __host__ __device__
  typename detail::make_composite<op_t, A0, A1>::type
  operator()(A0 const &_a0, A1 const &_a1) const {
    typedef typename detail::make_composite<op_t, A0, A1>::composite_type
      ret_t;
    return ret_t(op, as_actor<A0>::convert(_a0), as_actor<A1>::convert(_a1));
  }

  template<typename A0, typename A1, typename A2>
  __host__ __device__
  typename detail::make_composite<op_t, A0, A1, A2>::type
  operator()(A0 const &_a0, A1 const &_a1, A2 const &_a2) const {
    typedef typename detail::make_composite<op_t, A0, A1, A2>::composite_type
      ret_t;
    return ret_t(op,
                 as_actor<A0>::convert(_a0),
                 as_actor<A1>::convert(_a1),
                 as_actor<A2>::convert(_a2));
  }

  template<typename A0, typename A1, typename A2, typename A3>
  __host__ __device__
  typename detail::make_composite<op_t, A0, A1, A2, A3>::type
  operator()(A0 const &_a0, A1 const &_a1, A2 const &_a2, A3 const &_a3) const {
    typedef typename detail::make_composite<op_t, A0, A1, A2, A3>::composite_type
      ret_t;
    return ret_t(op,
                 as_actor<A0>::convert(_a0),
                 as_actor<A1>::convert(_a1),
                 as_actor<A2>::convert(_a2),
                 as_actor<A3>::convert(_a3));
  }

  template<typename A0, typename A1, typename A2, typename A3, typename A4>
  __host__ __device__
  typename detail::make_composite<op_t, A0, A1, A2, A3, A4>::type
  operator()(A0 const &_a0, A1 const &_a1, A2 const &_a2, A3 const &_a3, A4 const &_a4) const {
    typedef typename detail::make_composite<op_t, A0, A1, A2, A3, A4>::composite_type
      ret_t;
    return ret_t(op,
                 as_actor<A0>::convert(_a0),
                 as_actor<A1>::convert(_a1),
                 as_actor<A2>::convert(_a2),
                 as_actor<A3>::convert(_a3),
                 as_actor<A4>::convert(_a4));
  }

  template<typename A0, typename A1, typename A2, typename A3, typename A4, typename A5>
  __host__ __device__
  typename detail::make_composite<op_t, A0, A1, A2, A3, A4, A5>::type
  operator()(A0 const &_a0, A1 const &_a1, A2 const &_a2, A3 const &_a3, A4 const &_a4, A5 const &_a5) const {
    typedef typename detail::make_composite<op_t, A0, A1, A2, A3, A4, A5>::composite_type
      ret_t;
    return ret_t(op,
                 as_actor<A0>::convert(_a0),
                 as_actor<A1>::convert(_a1),
                 as_actor<A2>::convert(_a2),
                 as_actor<A3>::convert(_a3),
                 as_actor<A4>::convert(_a4),
                 as_actor<A5>::convert(_a5));
  }

};

} }
