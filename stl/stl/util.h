//
// Created by 17535 on 2022/6/25.
//

#ifndef MYSTL_UTIL_H
#define MYSTL_UTIL_H

#include <cstddef>

#include "stl/type_traits.h"

namespace stl {

/*
 * 使用万能引用接受参数，无条件将之转换为右值引用
 */
template <class T>
decltype(auto) move(T &&arg) noexcept {
  return static_cast<typename std::remove_reference<T>::type &&>(arg);
}

/*
 * 使用
 */
template <class T>
decltype(auto) forward(typename std::remove_reference<T>::type &arg) noexcept {
  return static_cast<T &&>(arg);
}

template <class T>
decltype(auto) forward(typename std::remove_reference<T>::type &&arg) noexcept {
  return static_cast<T &&>(arg);
}

template <class T>
void swap(T &lhs, T &rhs) {
  auto tmp(move(lhs));
  lhs = move(rhs);
  rhs = move(tmp);
}
} // namespace stl

#endif // MYSTL_UTIL_H
