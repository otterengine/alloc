#include <otter-alloc/align.h>

void *otter_align_forward(void *ptr, unsigned long align) {
  return otter_align_backward((void *)(((char *)ptr) + (align - 1)), align);
}

void *otter_align_backward(void *ptr, unsigned long align) {
  char *p = (char *)ptr;
  unsigned long offset = (unsigned long)p % align;
  if (offset != 0) {
    p -= offset;
  }

  return (void *)p;
}

int otter_is_aligned(void *ptr, unsigned long align) {
  char *p = (char *)ptr;

  return (unsigned long)p % align == 0;
}

unsigned long otter_align_size_forward(unsigned long size,
                                       unsigned long align) {
  return otter_align_size_backward(size + (align - 1), align);
}

unsigned long otter_align_size_backward(unsigned long size,
                                        unsigned long align) {
  return size & ~(align - 1);
}

int otter_is_size_aligned(unsigned long size, unsigned long align) {
  return (size & (align - 1)) == 0;
}
