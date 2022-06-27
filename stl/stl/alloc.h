//
// Created by 17535 on 2022/6/26.
//

#ifndef MYSTL_ALLOC_H
#define MYSTL_ALLOC_H

#include <new>

#include <cstddef>

namespace stl {

union obj {
  union obj *next;
  char       data[1];
};

constexpr size_t Align            = 8;
constexpr size_t SmallObjectBytes = 128;
constexpr int    FreeListNumber   = SmallObjectBytes / Align;

class alloc {
private:
  static char  *start_free;
  static char  *end_free;
  static size_t heap_size;

  static obj   *freeList[FreeListNumber];

public:
  static void *allocate(size_t n);
  static void  deallocate(void *p, size_t n);
  static void *reallocate(void *p, size_t old_size, size_t new_size);

private:
  static size_t ROUND_UP(size_t bytes) {
    return (((bytes) + Align - 1) & ~(Align - 1));
  }
  static size_t FREELIST_INDEX(size_t bytes) {
    return (((bytes) + Align - 1) / Align - 1);
  }
  static void *refill(size_t n);
  static char *chunk_alloc(size_t size, int &number);
};

char  *alloc::start_free               = nullptr;
char  *alloc::end_free                 = nullptr;
size_t alloc::heap_size                = 0;

obj   *alloc::freeList[FreeListNumber] = {
    nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
    nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};

void *alloc::allocate(size_t n) {
  obj **my_list;
  obj  *result;
  if (n > SmallObjectBytes) return ::operator new(n);
  my_list = freeList + FREELIST_INDEX(n);
  result  = *my_list;
  if (result == nullptr) {
    void *r = refill(ROUND_UP(n));
    return r;
  }
  *my_list = result->next;
  return result;
}

void alloc::deallocate(void *p, size_t n) {
  obj  *q = (obj *)p;
  obj **my_list;
  if (n > SmallObjectBytes) {
    ::operator delete(p);
    return;
  }
  my_list  = freeList + FREELIST_INDEX(n);
  q->next  = *my_list;
  *my_list = q;
}

void *alloc::refill(size_t n) {
  int   number = 20;
  char *chunk  = chunk_alloc(n, number);
  obj **my_list;
  obj  *result;
  obj  *cur_obj, *next_obj;
  int   i;
  if (number == 1) return chunk;
  my_list = freeList + FREELIST_INDEX(n);
  // 这n bytes是留给用户的
  result   = (obj *)chunk;
  *my_list = next_obj = (obj *)(chunk + n);
  for (i = 1;; i++) {
    cur_obj  = next_obj;
    next_obj = (obj *)((char *)next_obj + n);
    if (number - 1 == i) {
      cur_obj->next = nullptr;
      break;
    } else {
      cur_obj->next = next_obj;
    }
  }
  return result;
}

char *alloc::chunk_alloc(size_t size, int &number) {
  char  *result;
  size_t total_bytes = size * number;
  size_t bytes_left  = end_free - start_free;

  if (bytes_left >= total_bytes) {
    result = start_free;
    start_free += total_bytes;
    return result;
  } else if (bytes_left >= size) {
    number      = bytes_left / size;
    total_bytes = size * number;
    result      = start_free;
    start_free += total_bytes;
    return result;
  } else {
    size_t bytes_to_get = 1.5 * total_bytes + ROUND_UP(heap_size >> 4);
    if (bytes_left > 0) {
      obj **my_list             = freeList + FREELIST_INDEX(bytes_left);
      ((obj *)start_free)->next = *my_list;
      *my_list                  = (obj *)start_free;
    }
    start_free = (char *)::operator new(bytes_to_get);
    if (nullptr == start_free) {
      obj **my_list, *p;
      for (int i = size; i <= SmallObjectBytes; i += Align) {
        my_list = freeList + FREELIST_INDEX(i);
        p       = *my_list;
        if (p != nullptr) {
          *my_list   = p->next;
          start_free = (char *)p;
          end_free   = start_free + i;
          return chunk_alloc(size, number);
        }
      }
      end_free = nullptr;
    }
    heap_size += bytes_to_get;
    end_free = start_free + bytes_to_get;
    return chunk_alloc(size, number);
  }
}
void *alloc::reallocate(void *p, size_t old_size, size_t new_size) {
  deallocate(p, old_size);
  void *ret = allocate(new_size);
  return ret;
}

} // namespace stl

#endif // MYSTL_ALLOC_H
