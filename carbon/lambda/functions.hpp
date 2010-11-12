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

};

} }
