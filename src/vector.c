#include <FurredEngine/vector.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define _FE_VECTOR_EXISTS_ASSERT(v) \
    assert(v && "Vector does not exist."); \
    assert(v->data && "Vector has already been destroyed.")

unsigned int _next_pow2(unsigned int x) {
    if (x < 2) return 2;
    return ((unsigned int)1 << 31) >> (__builtin_clz(x) - 1);
}


FE_Vector furred_vector_create(FE_size_t size, FE_size_t dataSize) {
    void** data = calloc(size, dataSize);
    assert(data && "Vector could not be created. Does the system have enough memory?");

    FE_Vector vector = {
        .size       = size,
        .data_size   = dataSize,
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

    // Return data at index
    return *(vector->data + (index * vector->data_size));
}

void* furred_vector_front(FE_Vector* vector) {
    _FE_VECTOR_EXISTS_ASSERT(vector);
    assert(vector->size > 0 && "Vector index is out of range.");

    // Return beginning of data
    return *vector->data;
}

void* furred_vector_back(FE_Vector* vector) {
    _FE_VECTOR_EXISTS_ASSERT(vector);

    // Return last element of data
    return furred_vector_at(vector, vector->size - 1);
}


void furred_vector_reserve(FE_Vector* vector, FE_size_t newCapacity) {
    _FE_VECTOR_EXISTS_ASSERT(vector);
    
    // Check if space actually needs to be reserved
    if (newCapacity <= vector->capacity) return;

    const FE_size_t oldCapacity = vector->capacity;

    // Allocate new array
    void** newData = realloc(vector->data, newCapacity * vector->data_size);
    assert(newData && "Vector could not be expanded. Does the system have enough memory?");
    
    // Initialise newly allocated portion to 0
    memset(
        newData + (oldCapacity * vector->data_size),
        NULL,
        (newCapacity - oldCapacity) * vector->data_size
    );

    // Update vector object
    vector->data = newData;
    vector->capacity = newCapacity;
}

void furred_vector_shrink_to_fit(FE_Vector* vector) {
    _FE_VECTOR_EXISTS_ASSERT(vector);

    // Check if vector already fits its capacity
    if (vector->size == vector->capacity) return;

    // Allocate new array
    void** newData = realloc(vector->data, vector->size * vector->data_size);
    assert(newData && "Vector could not be shrunken. Does the system have enough memory?");
    
    // Update vector object
    vector->data = newData;
    vector->capacity = vector->size;
}

// TODO - needs to be tested to ensure this functions properly
void furred_vector_insert(FE_Vector* vector, FE_size_t index, void* data) {
    _FE_VECTOR_EXISTS_ASSERT(vector);
    assert(index < vector->size && "Vector index is out of range.");

    // If index is at back of vector
    if (index == vector->size - 1) {
        // Push data to back and return early
        furred_vector_push_back(vector, data);
        return;
    }

    const FE_size_t oldSize = vector->size;

    // Expand vector by 1
    furred_vector_resize(vector, vector->size + 1);

    // Pointer to index in vector data
    void** dataPtr = vector->data + (index * vector->data_size);
    // Length from start of index to end of vector
    const FE_size_t dataLength = oldSize - (index - 1);

    // Move data after index forward by 1
    memmove(
        vector->data, dataPtr + vector->data_size,
        dataLength * vector->data_size
    );
    // Assign index to data
    *dataPtr = data;
}

void furred_vector_clear(FE_Vector* vector) {
    _FE_VECTOR_EXISTS_ASSERT(vector);

    // Avoid using furred_vector_resize to prevent wasted computations
    vector->size = 0;
}

void furred_vector_push_back(FE_Vector* vector, void* data) {
    _FE_VECTOR_EXISTS_ASSERT(vector);

    const FE_size_t oldSize = vector->size;
    
    // Expand vector by 1
    furred_vector_resize(vector, vector->size + 1);

    // Pointer to last item in vector data
    //
    // Avoid using furred_vector_back to prevent wasted computations
    void** dataPtr = vector->data + (oldSize * vector->data_size);

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
        furred_vector_reserve(vector, _next_pow2(newSize));
    }
    // Else, vector does not need to be reallocated

    vector->size = newSize;
}