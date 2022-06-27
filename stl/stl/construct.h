//
// Created by 17535 on 2022/6/25.
//

#ifndef MYSTL_CONSTRUCT_H
#define MYSTL_CONSTRUCT_H

#include <new>

#include "stl/iterator.h"
#include "stl/type_traits.h"

namespace stl {

// placement new用于在已经分配的内存上构造
// 需要注意的是不存在placement delete
template <class T>
void construct(T *ptr) {
  ::new ((void *)ptr) T();
}

template <class T1, class T2>
void construct(T1 *ptr, const T2 &value) {
  ::new ((void *)ptr) T1(value);
}

// 等最后在考虑是否完善
//    template <class T, class... Args>
//    void construct(T* ptr, Args&&... args)
//    {
//        ::new ((void*)ptr) T(my forward<Args>(args)...);
//    }

// true_type的时候不需要进行析构
template <class T>
static void destroy(T *ptr, stl_true_type) {}

template <class T>
static void destroy(T *ptr, stl_false_type) {
  if (ptr != nullptr) {
    ptr->~T();
  }
}

template <class ForwardIterator>
static void destroy(ForwardIterator first, ForwardIterator last,
                    stl_true_type) {}

template <class ForwardIterator>
static void destroy(ForwardIterator first, ForwardIterator last,
                    stl_false_type) {
  for (; first != last; ++first)
    destroy(&*first);
}

template <class T>
void destroy(T *ptr) {
  destroy(ptr, has_trivial_destructor<T>());
}

template <class ForwardIterator>
void destroy(ForwardIterator first, ForwardIterator last) {
  destroy(first, last,
          has_trivial_destructor<
              typename iterator_traits<ForwardIterator>::value_type>{});
}

} // namespace stl

#endif // MYSTL_CONSTRUCT_H
