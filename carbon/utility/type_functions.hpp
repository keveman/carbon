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
namespace carbon { namespace utility {
namespace detail {

template<bool, typename T = void> struct enable_if_c {};
template<typename T>              struct enable_if_c<true, T> {typedef T type;};

template<typename U, typename V>
struct is_same {
  static const bool value = false;
};
template<typename U>
struct is_same<U, U> {
  static const bool value = true;
};

template<typename T>
struct remove_reference {
  typedef T type;
};

template<typename T>
struct remove_reference<T &> {
  typedef T type;
};

template<typename T>
struct remove_reference<T const&> {
  typedef T type;
};

template<typename T>
struct remove_reference<T const volatile&> {
  typedef T type;
};

template<typename T>
struct remove_const {
  typedef T type;
};

template<typename T>
struct remove_const<T const> {
  typedef T type;
};

}
} }
