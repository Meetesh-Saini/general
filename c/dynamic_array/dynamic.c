#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INIT(type, units) init(sizeof(type), units)

/*
*   Retrieves element at index i from array.
*   Parameters: 
*       ptr: Array pointer to the array
*       i: index of the element to retrieve
*       type: data type of the element
*   Returns:
*       element at index i type casted to `type`
*/
#define get_value(ptr, i, type)   *(type *)get(ptr, i)

typedef struct array{
    size_t len;    // length of array
    size_t size;   // number of units allocated to array
    size_t unit;   // size of each unit
    void *a;    // array pointer
} Array;

/*
*   Initialise the array.
*   Parameters: 
*       size: size of each element of array
*       units: number of elements (initial can be 1)
*   Returns:
*       Array pointer (struct array pointer)
*/
Array* init(size_t size, size_t units);

/*
*   Appends element to the end of the array.
*   Parameters: 
*       ptr: Array pointer to which element is being pushed
*       elem: Pointer to the element being pushed
*   Returns:
*       None
*/
void push(Array* ptr, void* elem);

/*
*   Retrieves address of element at index i from array.
*   Parameters: 
*       ptr: Array pointer to the array
*       i: index of the element to retrieve
*   Returns:
*       void pointer to the element of index i
*/
void* get(Array* ptr, int i);

/*
*   Replace element at index i with new element in array.
*   Parameters: 
*       ptr: Array pointer to the array
*       i: index of the element to replace
*       elem: Pointer to the element being replaced
*   Returns:
*       None
*/
void set(Array* ptr, int i, void* elem);

/*
*   Removes last element of the array.
*   Parameters: 
*       ptr: Array pointer to the array
*   Returns:
*       None
*/
void pop(Array* ptr);

/*
*   Deallocate the array memory.
*   Parameters: 
*       ptr: Array pointer to the array
*   Returns:
*       None
*/
void free_array(Array* ptr);


Array* init(size_t size, size_t units){
    if(!units || !size){
        fprintf(stderr, "Error: Invalid memory allocation.\n");
        exit(EXIT_FAILURE);
    }
    Array *ptr = (Array* )malloc(sizeof(Array));
    ptr->len = 0;
    ptr->size = units;
    ptr->unit = size;
    ptr->a = malloc(size*units);
    if(!ptr->a){
        fprintf(stderr, "Error: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    return ptr;
}

void push(Array* ptr, void* elem){
    if(ptr->len >= ptr->size){
        ptr->size *= 2;
        ptr->a = realloc(ptr->a, ptr->size*ptr->unit);
    }
    memcpy(ptr->a + (ptr->len * ptr->unit), elem, ptr->unit);
    ptr->len++;
}

void* get(Array* ptr, int i){
    i = i<0 ? ptr->len + i : i;
    if(i < 0 || i >= ptr->len){
        fprintf(stderr, "Error: Index out of range.\n");
        exit(EXIT_FAILURE);
    }
    return ptr->a + (i*ptr->unit);
}

void set(Array* ptr, int i, void* elem){
    i = i<0 ? ptr->len + i : i;
    if(i < 0 || i >= ptr->len){
        fprintf(stderr, "Error: Index out of range.\n");
        exit(EXIT_FAILURE);
    }
    memcpy(ptr->a + i, elem, ptr->unit);
}

void pop(Array* ptr){
    if(ptr->len <= 0){
        fprintf(stderr, "Error: No element left.\n");
        exit(EXIT_FAILURE);
    }
    ptr->len--;
}

void free_array(Array* ptr){
    free(ptr->a);
    free(ptr);
}
