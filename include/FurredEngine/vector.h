#pragma once

#include "exports.h"
#include <stdbool.h>

typedef unsigned int FE_size_t;

typedef struct {
    FE_size_t size;
    const FE_size_t dataSize;
    void** data;
    FE_size_t capacity;
} FE_Vector;

FE_EXPORT FE_Vector furred_vector_create(FE_size_t size, FE_size_t dataSize);
FE_EXPORT void furred_vector_destroy(FE_Vector* vector);

FE_EXPORT void* furred_vector_at(FE_Vector* vector, FE_size_t index);
FE_EXPORT void* furred_vector_front(FE_Vector* vector);
FE_EXPORT void* furred_vector_back(FE_Vector* vector);

FE_EXPORT void furred_vector_reserve(FE_Vector* vector, FE_size_t newCapacity);
FE_EXPORT void furred_vector_shrink_to_fit(FE_Vector* vector);

FE_EXPORT void furred_vector_clear(FE_Vector* vector);
FE_EXPORT void furred_vector_insert(FE_Vector* vector, FE_size_t index, void* data); // TODO - impl
FE_EXPORT void furred_vector_emplace(FE_Vector* vector, FE_size_t index, void* data); // TODO - impl
FE_EXPORT void furred_vector_erase(FE_Vector* vector, FE_size_t index); // TODO - impl
FE_EXPORT void furred_vector_push_back(FE_Vector* vector, void* data);
FE_EXPORT void furred_vector_pop_back(FE_Vector* vector);
FE_EXPORT void furred_vector_resize(FE_Vector* vector, FE_size_t newSize);
FE_EXPORT void furred_vector_swap(FE_Vector** vector, FE_Vector** otherVector);