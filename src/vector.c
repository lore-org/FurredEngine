#include <FurredEngine/vector.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define _FE_VECTOR_EXISTS_ASSERT(v) \
    assert(v && "Vector does not exist."); \
    assert(v->data && "Vector has already been destroyed.")

unsigned int next_pow2(unsigned int x) {
    if (x < 2) return 2;
    return ((unsigned int)1 << 31) >> (__builtin_clz(x) - 1);
}


FE_Vector furred_vector_create(FE_size_t size, FE_size_t dataSize) {
    void** data = calloc(size, dataSize);
    assert(data && "Vector could not be created. Does the system have enough memory?");

    FE_Vector vector = {
        .size       = size,
        .dataSize   = dataSize,
        .data       = data,
        .capacity   = size
    };

    return vector;
}

void furred_vector_destroy(FE_Vector* vector) {
    if (!vector) return;

    free(vector->data);
    vector->data = NULL;

    vector->size = 0;
    vector->capacity = 0;
}


void* furred_vector_at(FE_Vector* vector, FE_size_t index) {
    _FE_VECTOR_EXISTS_ASSERT(vector);
    assert(index < vector->size && "Vector index is out of range.");

    return *(vector->data + (index * vector->dataSize));
}

void* furred_vector_front(FE_Vector* vector) {
    _FE_VECTOR_EXISTS_ASSERT(vector);
    assert(vector->size > 0 && "Vector index is out of range.");

    return *vector->data;
}

void* furred_vector_back(FE_Vector* vector) {
    _FE_VECTOR_EXISTS_ASSERT(vector);

    return furred_vector_at(vector, vector->size - 1);
}


void furred_vector_reserve(FE_Vector* vector, FE_size_t newCapacity) {
    _FE_VECTOR_EXISTS_ASSERT(vector);
    
    // Check if space actually needs to be reserved
    if (newCapacity <= vector->capacity) return;

    const FE_size_t capacityBytes = newCapacity * vector->dataSize;

    // Allocate new array
    void** newData = realloc(vector->data, capacityBytes);
    assert(newData && "Vector could not be expanded. Does the system have enough memory?");
    
    // Update vector object
    vector->data = newData;
    vector->capacity = newCapacity;
}


void furred_vector_clear(FE_Vector* vector) {
    _FE_VECTOR_EXISTS_ASSERT(vector);

    // Avoid using furred_vector_resize to prevent wasted computations
    vector->size = 0;
}

void furred_vector_push_back(FE_Vector* vector, void* data) {
    _FE_VECTOR_EXISTS_ASSERT(vector);

    const FE_size_t oldSize = vector->size;
    furred_vector_resize(vector, vector->size + 1);
    // Retreive index to last item
    // Avoid using furred_vector_back to prevent wasted computations
    void** dataPtr = vector->data + (oldSize * vector->dataSize);
    // Assign last item to data
    *dataPtr = data;
}

void furred_vector_pop_back(FE_Vector* vector) {
    _FE_VECTOR_EXISTS_ASSERT(vector);
    assert(vector->size != 0 && "Vector has no elements to pop.");

    // Avoid using furred_vector_resize to prevent wasted computations
    vector->size--;
}

void furred_vector_resize(FE_Vector* vector, FE_size_t newSize) {
    _FE_VECTOR_EXISTS_ASSERT(vector);
    
    // If current capacity cannot handle newSize
    if (newSize > vector->capacity) {
        // Increase the current capacity to the power of 2 following newSize
        // This is done to ensure that the larger a vector grows the less allocations it should need
        //
        // furred_vector_reserve incurs an extra unneeded check, but code brevity is more important in this situation
        furred_vector_reserve(vector, next_pow2(newSize));
    }
    // Else, vector does not need to be reallocated

    vector->size = newSize;
}