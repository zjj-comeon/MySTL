//
// 这个模板类用于管理内存的分配、释放等操作
//

#ifndef MYSTL_ALLOCATOR_H
#define MYSTL_ALLOCATOR_H

#include "stl/alloc.h"
#include "stl/construct.h"
#include "stl/util.h"

namespace stl {

template <class T, class Alloc>
class allocator {
public:
  using value_type      = T;
  using pointer         = T *;
  using const_pointer   = const T *;
  using reference       = T &;
  using const_reference = const T &;
  using size_type       = size_t;
  using difference_type = ptrdiff_t;

public:
  static T   *allocate();
  static T   *allocate(size_type n);

  static void deallocate(T *ptr);
  static void deallocate(T *ptr, size_type n);

  static void construct(T *ptr);
  static void construct(T *ptr, const T &value);
  static void construct(T *ptr, T &&value);

  // TODO
  //  template <class... Args>
  //  static void construct(T* ptr, Args&& ...args);

  static void destroy(T *ptr);
  static void destroy(T *first, T *last);
};
template <class T, class Alloc>
T *allocator<T, Alloc>::allocate() {
  return static_cast<T *>(Alloc::allocate(sizeof(T)));
}
template <class T, class Alloc>
T *allocator<T, Alloc>::allocate(allocator::size_type n) {
  return static_cast<T *>(Alloc::allocate(n * sizeof(T)));
}
template <class T, class Alloc>
void allocator<T, Alloc>::deallocate(T *ptr) {
  Alloc::deallocate(ptr, sizeof(T));
}
template <class T, class Alloc>
void allocator<T, Alloc>::deallocate(T *ptr, allocator::size_type n) {
  Alloc::deallocate(ptr, n * sizeof(T));
}
template <class T, class Alloc>
void allocator<T, Alloc>::construct(T *ptr) {
  stl::construct(ptr);
}
template <class T, class Alloc>
void allocator<T, Alloc>::construct(T *ptr, const T &value) {
  stl::construct(ptr, value);
}
template <class T, class Alloc>
void allocator<T, Alloc>::construct(T *ptr, T &&value) {
  stl::construct(ptr, stl::move(value));
}
template <class T, class Alloc>
void allocator<T, Alloc>::destroy(T *ptr) {
  stl::destroy(ptr);
}
template <class T, class Alloc>
void allocator<T, Alloc>::destroy(T *first, T *last) {
  stl::destroy(first, last);
}

} // namespace stl

#endif // MYSTL_ALLOCATOR_H
