#pragma once

#include <carbon/utility/config.hpp>
#include <carbon/utility/type_functions.hpp>

namespace carbon { namespace utility {

struct endmarker {};

template<typename H, typename T>
struct vector {
  H elem;
  T rest;
};

struct make_vector {

  template<typename>
  struct result;

  template<typename This, typename T1>
  struct result<This(T1)> {
    typedef vector<T1, endmarker> type;
  };

  template<typename This, typename T1, typename T2>
  struct result<This(T1, T2)> {
    typedef vector<T1, typename result<This(T2)>::type> type;
  };

  template<typename This, typename T1, typename T2, typename T3>
  struct result<This(T1, T2, T3)> {
    typedef vector<T1, typename result<This(T2, T3)>::type> type;
  };

  template<typename This, typename T1, typename T2, typename T3, typename T4>
  struct result<This(T1, T2, T3, T4)> {
    typedef vector<T1, typename result<This(T2, T3, T4)>::type> type;
  };

  template<typename T1>
  __host__ __device__
  typename result<make_vector(T1)>::type
  operator()(T1 t1) {
    typename result<make_vector(T1)>::type retval = {t1};
    return retval;
  }

  template<typename T1, typename T2>
  __host__ __device__
  typename result<make_vector(T1, T2)>::type
  operator()(T1 t1, T2 t2) {
    typename result<make_vector(T1, T2)>::type retval = {t1,
                                                         make_vector().operator()<T2>(t2)};
    return retval;
  }

  template<typename T1, typename T2, typename T3>
  __host__ __device__
  typename result<make_vector(T1, T2, T3)>::type
  operator()(T1 t1, T2 t2, T3 t3) {
    typename result<make_vector(T1, T2, T3)>::type retval = {t1,
                                                             make_vector().operator()<T2, T3>(t2, t3)};
    return retval;
  }

  template<typename T1, typename T2, typename T3, typename T4>
  __host__ __device__
  typename result<make_vector(T1, T2, T3, T4)>::type
  operator()(T1 t1, T2 t2, T3 t3, T4 t4) {
    typename result<make_vector(T1, T2, T3, T4)>::type retval = {t1,
                                                                 make_vector().operator()<T2, T3, T4>(t2, t3, t4)};
    return retval;
  }
};

template <typename>
struct length;

template <typename T>
struct length<vector<T, endmarker> > {
  static const int value = 1;
};

template <typename T, typename Rest>
struct length<vector<T, Rest> > {
  static const int value = 1 + length<Rest>::value;
};

template<typename V, int N, bool=(N>=0), bool=(length<V>::value > N)>
struct typeat {
};

template<typename T, typename Rest>
struct typeat<vector<T, Rest>, 0, true, true> {
  typedef T type;
};

template<typename T, typename Rest, int N>
struct typeat<vector<T, Rest>, N, true, true> {
  typedef typename typeat<Rest, N-1>::type type;
};

template<typename T, typename Rest, int N>
struct typeat<vector<T, Rest>, N, false, false> {
  typedef typename typeat<vector<T, Rest>, length<vector<T, Rest> >::value-1>::type type;
};

template<typename T, typename Rest, int N>
struct typeat<vector<T, Rest>, N, true, false> {
  typedef typename typeat<vector<T, Rest>, length<vector<T, Rest> >::value-1>::type type;
};

template<typename T, typename Rest, int N>
struct typeat<vector<T, Rest>, N, false, true> {
  typedef typename typeat<vector<T, Rest>, length<vector<T, Rest> >::value-1>::type type;
};

template<int N, typename T, typename Rest>
__host__ __device__
typename detail::enable_if_c<(N==0),
typename typeat<vector<T, Rest>, N>::type>::type
at_c(const vector<T, Rest> &v)
{
  return v.elem;
}

template<int N, typename T, typename Rest>
__host__ __device__
typename detail::enable_if_c<((N>0) && (length<vector<T, Rest> >::value > N)),
typename typeat<Rest, N-1>::type>::type
at_c(const vector<T, Rest> &v)
{
  return at_c<N-1>(v.rest);
}

} }
