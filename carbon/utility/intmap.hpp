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

#pragma once

#include <carbon/utility/config.hpp>
#include <carbon/utility/vector.hpp>

namespace carbon { namespace utility {

template<int N, typename T>
struct intpair {
  static const int first = N;
  T second;

  typedef T type;
  
  __host__ __device__
  intpair(T const &_t) : second(_t) {}
};

template<int N, typename M>
struct intmap_find {
  
};

template<int N, typename T, typename Rest>
struct intmap_find<N, vector<intpair<N, T>, Rest> > {
  static const unsigned loc = 0;
};

template<int N, typename T, typename Rest>
struct intmap_find<N, vector<intpair<N, T>&, Rest> > {
  static const unsigned loc = 0;
};

template<int N, int M, typename T, typename Rest>
struct intmap_find<N, vector<intpair<M, T>, Rest> > {
  static const unsigned loc = 1 + intmap_find<N, Rest>::loc;
};

template<int N, typename T, typename Rest>
struct intmap_find<N, vector<T, Rest> > {
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
