//
// Created by 17535 on 2022/6/26.
//

#ifndef MYSTL_ITERATOR_H
#define MYSTL_ITERATOR_H

#include <cstddef>

#include "stl/type_traits.h"

namespace stl {
struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

// 开发自己的迭代器最好继承这个以防止漏掉什么
template <class Category, class T, class Distance = ptrdiff_t,
          class Pointer = T *, class Reference = T &>
struct iterator {
  using iterator_category = Category;
  using value_type        = T;
  using pointer           = Pointer;
  using reference         = Reference;
  using difference_type   = Distance;
};

// 之所以增加一层是因为这样就可以进行偏特化
template <class Iterator>
struct iterator_traits {
  using iterator_category = typename Iterator::iterator_category;
  using value_type        = typename Iterator::value_type;
  using difference_type   = typename Iterator::difference_type;
  using pointer           = typename Iterator::pointer;
  using reference         = typename Iterator::reference;
};

// 为原生指针特化
template <class T>
struct iterator_traits<T *> {
  using iterator_category = random_access_iterator_tag;
  using value_type        = T;
  using difference_type   = ptrdiff_t;
  using pointer           = T *;
  using reference         = T &;
};

// 为const原生指针特化
template <class T>
struct iterator_traits<const T *> {
  using iterator_category = random_access_iterator_tag;
  using value_type        = T;
  using difference_type   = ptrdiff_t;
  using pointer           = const T *;
  using reference         = const T &;
};

// 获取迭代器的分类
template <class Iterator>
inline decltype(auto) iterator_category(const Iterator &) {
  return typename iterator_traits<Iterator>::iterator_category();
}

// 获取迭代器的difference_type
template <class Iterator>
inline decltype(auto) distance_type(const Iterator &) {
  return static_cast<typename iterator_traits<Iterator>::difference_type *>(0);
}

// 获取迭代器的value_type
template <class Iterator>
inline decltype(auto) value_type(const Iterator &) {
  return static_cast<typename iterator_traits<Iterator>::value_type *>(0);
}

template <class InputIter>
inline decltype(auto) __distance(InputIter first, InputIter last,
                                 input_iterator_tag) {
  typename iterator_traits<InputIter>::difference_type n = 0;
  while (first != last) {
    ++first;
    ++n;
  }
  return n;
}

template <class RandomAccessIter>
inline decltype(auto) __distance(RandomAccessIter first, RandomAccessIter last,
                                 random_access_iterator_tag) {
  return last - first;
}

template <class InputIter>
inline decltype(auto) distance(InputIter first, InputIter last) {
  return __distance(first, last,
                    iterator_traits<InputIter>::iterator_category());
}

template <class InputIter, class Distance>
inline void __advance(InputIter &i, Distance n, input_iterator_tag) {
  if (n >= 0)
    while (n--)
      ++i;
  else
    while (n++)
      --i;
}

template <class RandomAccessIter, class Distance>
inline void __advance(RandomAccessIter &i, Distance n,
                      random_access_iterator_tag) {
  i += n;
}

template <class InputIter, class Distance>
inline void advance(InputIter &i, Distance n) {
  __advance(i, n, iterator_category(i));
}

} // namespace stl

#endif // MYSTL_ITERATOR_H
