#pragma once

#include "exports.h"

typedef unsigned int FE_size_t;

/**
 * @brief An automatically resizing array.
 * 
 */
typedef struct {
    /**
     * @brief Number of elements stored in the vector.
     * 
     */
    FE_size_t size;
    /**
     * @brief Size of each element in bytes.
     * 
     */
    const FE_size_t data_size;
    /**
     * @brief Array of data of an unspecified type.
     * 
     */
    void* data;
    /**
     * @brief Number of elements currently able to fit into the array.
     * 
     */
    FE_size_t capacity;
} FE_Vector;


/**
 * @brief Constructs a vector of given `size` and `dataSize`.
 * 
 * @param size The number zeroed elements that will be inserted into the array.
 * @param dataSize The side of each element in bytes. Intended to use with `sizeof`.
 * @return FE_Vector 
 */
FE_EXPORT FE_Vector furred_vector_create(FE_size_t size, FE_size_t dataSize);
/**
 * @brief Destroys a previously constructed vector. See @ref furred_vector_create.
 * 
 * @param vector A pointer to the associated vector.
 * @return void 
 */
FE_EXPORT void furred_vector_destroy(FE_Vector* vector);

/**
 * @brief Returns an element of `vector` at the location `index`.
 * 
 * @param vector A pointer to the associated vector. See @ref furred_vector_create.
 * @param index The position of the element to return.
 * @return void* 
 */
FE_EXPORT void* furred_vector_at(FE_Vector* vector, FE_size_t index);
/**
 * @brief Returns the first element in `vector`.
 * 
 * @param vector A pointer to the associated vector. See @ref furred_vector_create.
 * @return void* 
 */
FE_EXPORT void* furred_vector_front(FE_Vector* vector);
/**
 * @brief Returns the last element in `vector`.
 * 
 * @param vector A pointer to the associated vector. See @ref furred_vector_create.
 * @return void* 
 */
FE_EXPORT void* furred_vector_back(FE_Vector* vector);

/**
 * @brief Increases the capacity of `vector`.
 * 
 * @param vector A pointer to the associated vector. See @ref furred_vector_create.
 * @param newCapacity The desired capacity of the vector.
 * @return void 
 */
FE_EXPORT void furred_vector_reserve(FE_Vector* vector, FE_size_t newCapacity);
/**
 * @brief Decreases the capacity of `vector` to its size.
 * 
 * @param vector A pointer to the associated vector. See @ref furred_vector_create.
 * @return void 
 */
FE_EXPORT void furred_vector_shrink_to_fit(FE_Vector* vector);

/**
 * @brief Erases all elements from `vector`.
 * 
 * @param vector A pointer to the associated vector. See @ref furred_vector_create.
 * @return void 
 */
FE_EXPORT void furred_vector_clear(FE_Vector* vector);
/**
 * @brief Inserts `data` at the location `index`, shifting any following elements forward.
 * 
 * @param vector A pointer to the associated vector. See @ref furred_vector_create.
 * @param index The position of the element to be inserted.
 * @param data A single element.
 * @return void 
 */
FE_EXPORT void furred_vector_insert(FE_Vector* vector, FE_size_t index, void* data);
/**
 * @brief Erases the element at the location `index` and collapses `vector` to fill the space.
 * 
 * @param vector A pointer to the associated vector. See @ref furred_vector_create.
 * @param index The position of the element to be erased.
 * @return void
 */
FE_EXPORT void furred_vector_erase(FE_Vector* vector, FE_size_t index);
/**
 * @brief Appends `data` to the end of `vector`.
 * 
 * @param vector A pointer to the associated vector. See @ref furred_vector_create.
 * @param data A single element.
 * @return void 
 */
FE_EXPORT void furred_vector_push_back(FE_Vector* vector, void* data);
/**
 * @brief Erases the element at the end of `vector`.
 * 
 * @param vector A pointer to the associated vector. See @ref furred_vector_create.
 * @return void 
 */
FE_EXPORT void furred_vector_pop_back(FE_Vector* vector);
/**
 * @brief Changes the size of `vector` to `newSize`, filling any empty space with zeroes.
 * 
 * @param vector A pointer to the associated vector. See @ref furred_vector_create.
 * @param newSize The desired size of the vector.
 * @return void 
 */
FE_EXPORT void furred_vector_resize(FE_Vector* vector, FE_size_t newSize);