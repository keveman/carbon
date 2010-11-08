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


}
} }
