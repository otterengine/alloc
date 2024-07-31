#include <test.h>

#include <otter-alloc/align.h>

void align_forward(void) {
  void *ptr = (void *)123;
  void *aligned = otter_align_forward(ptr, 8);
  test_assert(aligned == (void *)128);
}

void align_backward(void) {
  void *ptr = (void *)123;
  void *aligned = otter_align_backward(ptr, 8);
  test_assert(aligned == (void *)120);
}

void align_is_aligned(void) {
  void *ptr = (void *)124;
  test_assert(otter_is_aligned(ptr, 4));
  test_assert(!otter_is_aligned(ptr, 8));
  test_assert(!otter_is_aligned(ptr, 16));
  test_assert(!otter_is_aligned(ptr, 32));
}

void align_size_forward(void) {
  unsigned long size = 123;
  unsigned long align = 8;
  test_assert(otter_align_size_forward(size, align) == 128);
}

void align_size_backward(void) {
  unsigned long size = 123;
  unsigned long align = 8;
  test_assert(otter_align_size_backward(size, align) == 120);
}
