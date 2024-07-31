#ifndef OTTER_ALLOC_ALIGN_H_
#define OTTER_ALLOC_ALIGN_H_

/* This generated file contains includes for project dependencies */
#include "otter-alloc/bake_config.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

OTTER_ALLOC_API
void *
otter_align_forward(void *ptr, unsigned long align);

OTTER_ALLOC_API
void *
otter_align_backward(void *ptr, unsigned long align);

OTTER_ALLOC_API
int
otter_is_aligned(void *ptr, unsigned long align);

OTTER_ALLOC_API
unsigned long
otter_align_size_forward(unsigned long size, unsigned long align);

OTTER_ALLOC_API
unsigned long
otter_align_size_backward(unsigned long size, unsigned long align);

OTTER_ALLOC_API
int
otter_is_size_aligned(unsigned long size, unsigned long align);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* OTTER_ALLOC_ALIGN_H_ */
