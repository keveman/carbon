#pragma once

#include <carbon/utility/config.hpp>
#include <carbon/utility/vector.hpp>

namespace carbon { namespace utility {

template<int N, typename T>
struct intpair {
  static const int first = N;
  T second;
};

template<int N1, typename T1>
__host__ __device__
typename make_vector::result<make_vector(intpair<N1, T1>)>::type
make_intmap(T1 t1) {
  intpair<N1, T1> p1 = {t1};
  typename make_vector::result<make_vector(intpair<N1, T1>)>::type
    retval = {p1};
  return retval;
}

template<int N1, int N2, typename T1, typename T2>
__host__ __device__
typename make_vector::result<make_vector(intpair<N1, T1>, intpair<N2, T2>)>::type
make_intmap(T1 t1, T2 t2) {
  intpair<N1, T1> p1 = {t1};
  intpair<N2, T2> p2 = {t2};
  typename make_vector::result<make_vector(intpair<N1, T1>, intpair<N2, T2>)>::type
    retval = {p1, p2};
  return retval;
}

template<int N1, int N2, int N3, typename T1, typename T2, typename T3>
typename make_vector::result<make_vector(intpair<N1, T1>, intpair<N2, T2>,
                                         intpair<N3, T3>)>::type
__host__ __device__
make_intmap(T1 t1, T2 t2, T3 t3) {
  intpair<N1, T1> p1 = {t1};
  intpair<N2, T2> p2 = {t2};
  intpair<N3, T3> p3 = {t3};
  typename make_vector::result<make_vector(intpair<N1, T1>, intpair<N2, T2>,
                                           intpair<N3, T3>)>::type
    retval = {p1, p2, p3};
  return retval;
}

template<int N1, int N2, int N3, int N4, typename T1, typename T2, typename T3, typename T4>
typename make_vector::result<make_vector(intpair<N1, T1>, intpair<N2, T2>,
                                         intpair<N3, T3>, intpair<N4, T4>)>::type
__host__ __device__
make_intmap(T1 t1, T2 t2, T3 t3, T4 t4) {
  intpair<N1, T1> p1 = {t1};
  intpair<N2, T2> p2 = {t2};
  intpair<N3, T3> p3 = {t3};
  intpair<N4, T4> p4 = {t4};
  typename make_vector::result<make_vector(intpair<N1, T1>, intpair<N2, T2>,
                                           intpair<N3, T3>, intpair<N4, T4>)>::type
    retval = {p1, p2, p3, p4};
  return retval;
}

template<int N, typename M>
struct intmap_find {
  
};

template<int N, typename T, typename Rest>
struct intmap_find<N, vector<intpair<N, T>, Rest> > {
  static const unsigned loc = 0;
};

template<int N, int M, typename T, typename Rest>
struct intmap_find<N, vector<intpair<M, T>, Rest> > {
  static const unsigned loc = 1 + intmap_find<N, Rest>::loc;
};

template<int N>
struct intmap_find<N, endmarker> {
  static const unsigned loc = 0;
};

template<int N, typename M>
__host__ __device__
typename typeat<M, intmap_find<N, M>::loc>::type
find_c(const M &m)
{
  return at_c<intmap_find<N, M>::loc>(m);
}

} }
