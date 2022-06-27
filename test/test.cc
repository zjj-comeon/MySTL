#include "stl/alloc.h"
#include "stl/allocator.h"
#include <gtest/gtest.h>

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(stlTest, allocateTest) {
  std::string *s = stl::allocator<std::string, stl::alloc>::allocate();
  stl::allocator<std::string, stl::alloc>::construct(s, "hello");
  std::cout << *s << std::endl;
  stl::allocator<std::string, stl::alloc>::destroy(s);
  //  std::allocator<std::string> allocator;
  //  std::string                *s = allocator.allocate(sizeof(std::string));
  //  allocator.construct(s, "hello");
  //  std::cout << *s << std::endl;
  //  allocator.destroy(s);

  stl::alloc alloc;
  int        n = 4;
  int       *p = (int *)alloc.allocate(n);
  *p           = 10;
  alloc.reallocate(p, n, n * 2);
  *(p + 1) = 20;
  alloc.deallocate(p, n);
}
