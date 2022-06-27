//
// Created by 17535 on 2022/6/26.
//

#ifndef MYSTL_UNINITIALIZED_H
#define MYSTL_UNINITIALIZED_H

// TODO
#include <algorithm>

#include "stl/construct.h"
#include "stl/iterator.h"
#include "stl/type_traits.h"
#include "stl/util.h"

namespace stl {

template <class InputIter, class ForwardIter>
ForwardIter __uninitialized_copy_aux(InputIter first, InputIter last,
                                     ForwardIter result, stl_false_type) {
  ForwardIter cur = first;
  for (; first != last; ++first, ++cur)
    construct(&*cur, *first);
  return cur;
}

template <class InputIter, class ForwardIter>
inline ForwardIter __uninitialized_copy_aux(InputIter first, InputIter last,
                                            ForwardIter result, stl_true_type) {
  return std::copy(first, last, result);
}

template <class InputIter, class ForwardIter, class T>
inline ForwardIter uninitialized_copy(InputIter first, InputIter last,
                                      ForwardIter result, T *) {
  return __uninitialized_copy_aux(first, last, result, is_POD_type<T>());
}

template <class InputIter, class ForwardIter>
inline ForwardIter uninitialized_copy(InputIter first, InputIter last,
                                      ForwardIter result) {
  return __uninitialized_copy(first, last, result, value_type(result));
}

template <class ForwardIter, class T>
inline void __uninitialized_fill_aux(ForwardIter first, ForwardIter last,
                                     const T &x, stl_true_type) {
  std::fill(first, last, x);
}

template <class ForwardIter, class T>
inline void __uninitialized_fill_aux(ForwardIter first, ForwardIter last,
                                     const T &x, stl_false_type) {
  ForwardIter cur = first;
  for (; cur != last; ++cur)
    construct(&*cur, x);
}

template <class ForwardIter, class T, class T1>
inline void __uninitialized_fill(ForwardIter first, ForwardIter last,
                                 const T &x, T1 *) {
  return __uninitialized_fill_aux(first, last, x, is_POD_type<T1>());
}

template <class ForwardIter, class T>
inline void uninitialized_fill(ForwardIter first, ForwardIter last,
                               const T &x) {
  return __uninitialized_fill(first, last, x, value_type(first));
}

template <class ForwardIter, class Size, class T, class T1>
ForwardIter __uninitialized_fill_n_aux(ForwardIter first, Size n, const T &x,
                                       stl_false_type) {
  ForwardIter cur = first;
  for (; n > 0; --n, ++cur)
    construct(&*cur, x);
  return cur;
}

template <class ForwardIter, class Size, class T, class T1>
inline ForwardIter __uninitialized_fill_n_aux(ForwardIter first, Size n,
                                              const T &x, stl_true_type) {
  return std::fill_n(first, n, x);
}

template <class ForwardIter, class Size, class T, class T1>
inline ForwardIter __uninitialized_fill_n(ForwardIter first, Size n, const T &x,
                                          T1 *) {
  return __uninitialized_fill_n_aux(first, n, x,
                                    typename stl::is_POD_type<T1>());
}

template <class ForwardIter, class Size, class T>
inline ForwardIter uninitialized_fill_n(ForwardIter first, Size n, const T &x) {
  return __uninitialized_fill_n(first, n, x, value_type(first));
}

} // namespace stl

#endif // MYSTL_UNINITIALIZED_H
