#include <otter_alloc.h>

#include <otter-alloc/align.h>

static
void
memcpy(void *dst, void *src, unsigned long size) {
  unsigned char *d = dst;
  unsigned char *s = src;
  while (size > 0) {
    *d++ = *s++;
    size--;
  }
}

static
otter_alloc_result_t
alloc_bytes_with_alignment(otter_allocator_t allocator,
                           unsigned long size,
                           unsigned long align,
                           void **out) {
  /* TODO: Assert that align is less than the native page size */

  if (size == 0) {
    return OTTER_RESULT_ALLOC_INVALID_SIZE;
  }

  if (align == 0) {
    return OTTER_RESULT_ALLOC_INVALID_ALIGN;
  }

  return allocator.vtable->alloc(allocator.ctx, size, align, out);
}

otter_alloc_result_t
otter_allocator_create(otter_allocator_t allocator,
                       unsigned long size,
                       unsigned long align,
                       void **out) {
  return alloc_bytes_with_alignment(allocator, size, align, out);
}

void
otter_allocator_destroy(otter_allocator_t allocator,
                        unsigned long size,
                        unsigned long align,
                        void *ptr) {
  if (size == 0 || ptr == 0) {
    return;
  }

  allocator.vtable->free(allocator.ctx, otter_slice_init(ptr, size), align);
}

otter_alloc_result_t
otter_allocator_alloc(otter_allocator_t allocator,
                       unsigned long elem_size,
                       unsigned long count,
                       unsigned long elem_align,
                       otter_slice_t *out) {
  otter_alloc_result_t result = alloc_bytes_with_alignment(allocator,
                                                           elem_size * count,
                                                           elem_align,
                                                           &out->ptr);
  
  if (result >= 0) {
    out->len = elem_size * count;
  }

  return result;
}

void
otter_allocator_free(otter_allocator_t allocator,
                     otter_slice_t buf,
                     unsigned long buf_align) {
  if (buf.len == 0 || buf_align == 0) {
    return;
  }

  allocator.vtable->free(allocator.ctx, buf, buf_align);
}

int
otter_allocator_resize(otter_allocator_t allocator,
                       otter_slice_t buf,
                       unsigned long elem_size,
                       unsigned long buf_align,
                       unsigned long new_size) {
  if (new_size == 0) {
    otter_allocator_free(allocator, buf, buf_align);
    return 1;
  }

  if (buf.len == 0 || buf_align == 0) {
    return 0;
  }

  return allocator.vtable->resize(allocator.ctx, buf, buf_align, new_size);
}

otter_alloc_result_t
otter_allocator_realloc(otter_allocator_t allocator,
                        otter_slice_t buf,
                        unsigned long elem_size,
                        unsigned long buf_align,
                        unsigned long new_size,
                        otter_slice_t *out) {
  if (new_size == 0) {
    otter_allocator_free(allocator, buf, buf_align);
    return OTTER_RESULT_ALLOC_SUCCESSFULLY_FREED;
  }

  if (buf.len == 0) {
    return alloc_bytes_with_alignment(allocator, new_size, buf_align, &out->ptr);
  }

  if (otter_is_aligned(buf.ptr, buf_align)) {
    if (otter_allocator_resize(allocator, buf, elem_size, buf_align, new_size)) {
      return OTTER_RESULT_ALLOC_SUCCESSFULLY_RESIZED;
    }
  }

  if (alloc_bytes_with_alignment(allocator, new_size, buf_align, &out->ptr) >= 0) {
    memcpy(out->ptr, buf.ptr, buf.len);

    otter_allocator_free(allocator, buf, buf_align);

    return OTTER_RESULT_ALLOC_SUCCESSFULLY_REALLOCATED;
  }

  return OTTER_RESULT_ALLOC_OUT_OF_MEMORY;
}

int
otter_alloc_noop_resize(void *ctx, otter_slice_t buf,
                        unsigned long align,
                        unsigned long new_size) {
  (void)ctx;
  (void)buf;
  (void)align;
  (void)new_size;

  return 0;
}

void
otter_alloc_noop_free(void *ctx, otter_slice_t buf,
                      unsigned long align) {
  (void)ctx;
  (void)buf;
  (void)align;
}
