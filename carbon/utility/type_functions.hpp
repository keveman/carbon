
//          Copyright Manjunath Kudlur 2010 - 2012
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

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
