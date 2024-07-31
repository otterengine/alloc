#ifndef OTTER_ALLOC_H_
#define OTTER_ALLOC_H_

/* This generated file contains includes for project dependencies */
#include "otter-alloc/bake_config.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef int otter_alloc_result_t;

#define OTTER_RESULT_ALLOC_SUCCESSFULLY_ALLOCATED (0)
#define OTTER_RESULT_ALLOC_SUCCESSFULLY_FREED (1)
#define OTTER_RESULT_ALLOC_SUCCESSFULLY_RESIZED (2)
#define OTTER_RESULT_ALLOC_SUCCESSFULLY_REALLOCATED (3)

#define OTTER_RESULT_ALLOC_OUT_OF_MEMORY (-1)
#define OTTER_RESULT_ALLOC_INVALID_SIZE (-2)
#define OTTER_RESULT_ALLOC_INVALID_ALIGN (-3)

#define align_of(T) ((unsigned long)(&((struct { char c; T member; } *)0)->member))

typedef struct otter_allocator_vtable otter_allocator_vtable_t;
struct otter_allocator_vtable {
  otter_alloc_result_t (*alloc)(void *ctx, unsigned long size,
                          unsigned long align, void **out);
  int (*resize)(void *ctx, otter_slice_t buf,
                         unsigned long buf_align, unsigned long new_size);
  void (*free)(void *ctx, otter_slice_t buf, unsigned long buf_align);
};

typedef struct otter_allocator otter_allocator_t;
struct otter_allocator {
  void *ctx;
  const otter_allocator_vtable_t *vtable;
};

OTTER_ALLOC_API
otter_alloc_result_t 
otter_allocator_create(otter_allocator_t allocator,
                       unsigned long size, unsigned long align, void **out);

OTTER_ALLOC_API
void
otter_allocator_destroy(otter_allocator_t allocator, unsigned long size,
                    unsigned long align, void *ptr);
                    
otter_alloc_result_t otter_allocator_alloc(otter_allocator_t allocator,
                                     unsigned long elem_size,
                                     unsigned long count,
                                     unsigned long elem_align,
                                     otter_slice_t *out);

OTTER_ALLOC_API
void
otter_allocator_free(otter_allocator_t allocator, otter_slice_t buf, 
                     unsigned long buf_align);

OTTER_ALLOC_API
int
otter_allocator_resize(otter_allocator_t allocator,
                       otter_slice_t buf,
                       unsigned long elem_size,
                       unsigned long buf_align,
                       unsigned long new_size);

OTTER_ALLOC_API
otter_alloc_result_t
otter_allocator_realloc(otter_allocator_t allocator,
                        otter_slice_t buf,
                        unsigned long elem_size,
                        unsigned long buf_align,
                        unsigned long new_size,
                        otter_slice_t *out);

OTTER_ALLOC_API
int
otter_alloc_noop_resize(void *ctx, otter_slice_t buf,
                        unsigned long align,
                        unsigned long new_size);

OTTER_ALLOC_API
void
otter_alloc_noop_free(void *ctx, otter_slice_t buf,
                      unsigned long align);

#define otter_allocator_create_t(allocator, T, out) \
  otter_allocator_create(allocator, sizeof(T), align_of(T), (void **)out)

#define otter_allocator_aligned_create_t(allocator, T, align, out) \
  otter_allocator_create(allocator, sizeof(T), align, (void **)out)

#define otter_allocator_destroy_t(allocator, T, ptr) \
  otter_allocator_destroy(allocator, sizeof(T), align_of(T), (void *)ptr)

#define otter_allocator_aligned_destroy_t(allocator, T, align, ptr) \
  otter_allocator_destroy(allocator, sizeof(T), align, (void *)ptr)

#define otter_allocator_alloc_t(allocator, T, count, out) \
  otter_allocator_alloc(allocator, sizeof(T), count, align_of(T), out)

#define otter_allocator_aligned_alloc_t(allocator, T, count, align, out) \
  otter_allocator_alloc(allocator, sizeof(T), count, align, out)

#define otter_allocator_free_t(allocator, T, buf) \
  otter_allocator_free(allocator, buf, align_of(T))

#define otter_allocator_resize_t(allocator, T, buf, new_size) \
  otter_allocator_resize(allocator, buf, sizeof(T), align_of(T), new_size)

#define otter_allocator_aligned_resize_t(allocator, T, buf, align, new_size) \
  otter_allocator_resize(allocator, buf, sizeof(T), align, new_size)

#define otter_allocator_realloc_t(allocator, T, buf, new_size, out) \
  otter_allocator_realloc(allocator, buf, sizeof(T), align_of(T), new_size, out)

#define otter_allocator_aligned_realloc_t(allocator, T, buf, align, new_size, out) \
  otter_allocator_realloc(allocator, buf, sizeof(T), align, new_size, out)

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* OTTER_ALLOC_H_ */

