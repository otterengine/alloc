#include <otter-alloc/align.h>

void *otter_align_forward(void *ptr, unsigned long align) {
  return otter_align_backward((void *)(((char *)ptr) + (align - 1)), align);
}

void *otter_align_backward(void *base, unsigned long align) {
  unsigned long i;
  unsigned char align_bytes[sizeof(unsigned long)];
  unsigned char aligned_ptr_bytes[sizeof(void *)];
  unsigned long *align_first = (void *)(&align_bytes[0]);
  void **aligned_ptr_first = (void *)(&aligned_ptr_bytes[0]);

  *align_first = align - 1;
  *aligned_ptr_first = base;

  for (i = (sizeof(void *) - sizeof(unsigned long));
       i < sizeof(void *); i++) {
    aligned_ptr_bytes[i] = aligned_ptr_bytes[i] & ~align_bytes[i];
  }

  return *aligned_ptr_first;
}

int otter_is_aligned(void *ptr, unsigned long align) {
  unsigned char ptr_buf[sizeof(void *)];
  unsigned char align_buf[sizeof(unsigned long)];
  void **ptr_first = (void *)(&ptr_buf[0]);
  unsigned long *align_first = (void *)(&align_buf[0]);
  unsigned long i;

  *ptr_first = ptr;
  *align_first = align - 1;

  /* we simply check if the least significant bytes overlap with the align */
  for (i = (sizeof(void *) - sizeof(unsigned long));
       i < sizeof(void *); i++) {
    if ((ptr_buf[i] & ~align_buf[i]) != ptr_buf[i]) {
      return 0;
    }
  }

  return 1;
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
