#include "array.h"
#include <math.h>
#include <stdlib.h>

int scale(array *arr, int length)
{
    if (arr->size > 0)
    {
        double rate = 1.0 * length / arr->size;

        if (rate > 1.0)
            arr->size = arr->size * ceil(rate);
        else if (rate < 0.5 && arr->size >= arr->initSize * 2)
            arr->size /= 2;
        else
            return 0;
    }

    arr->size <= 0 && (arr->size = 1);
    arr->elements = (void **)realloc(arr->elements, arr->size * sizeof(void *));

    return 1;
}

// ==========================================================
array *array_create(int size)
{
    size <= 0 && (size = 1);

    array *arr = (array *)calloc(1, sizeof(array));
    arr->size = arr->initSize = size;
    arr->length = 0;
    arr->elements = (void **)calloc(size, sizeof(void *));

    return arr;
}

void *array_get(array *arr, int index)
{
    if (index < 0 || index >= arr->length)
        return NULL;

    return arr->elements[index];
}

int array_set(array *arr, int index, void *data)
{
    if (index < 0)
        return 0;

    index >= arr->size && (scale(arr, index + 1));

    for (int i = arr->length; i < index; i++)
        arr->elements[i] = NULL;

    arr->elements[index] = data;
    index >= arr->length && (arr->length = index + 1);

    return 1;
}

int array_insert_multiple(array *arr, int index, int count, void **data)
{
    if (index < 0)
        return 0;

    scale(arr, arr->length + count);

    for (int i = arr->length - 1; i >= index; i--)
        arr->elements[i + count] = arr->elements[i];

    for (int j = 0; j < count; j++)
        arr->elements[index + j] = data[j];

    arr->length += count;

    return count;
}

int array_insert(array *arr, int index, void *data)
{
    return array_insert_multiple(arr, index, 1, &data);
}

int array_append_multiple(array *arr, int count, void **data)
{
    return array_insert_multiple(arr, arr->length, count, data);
}
int array_append(array *arr, void *data)
{
    return array_insert(arr, arr->length, data);
}

void array_iterator(array *arr, void (*handler)(void *data, int index))
{
    for (int i = 0; i < arr->length; i++)
        (*handler)(arr->elements[i], i);
}

array *array_remove(array *arr, int index, int length)
{
    if (index < 0 || index >= arr->length || length <= 0)
        return array_create(1);

    int len = arr->length;
    if (length + index >= len)
        length = len - index;

    array *res = array_create(length);
    int i = index;
    for (; i < index + length; i++)
    {
        array_append(res, arr->elements[i]);
        arr->elements[i] = array_get(arr, i + length);
    }

    for (; i < arr->length - length; i++)
        arr->elements[i] = array_get(arr, i + length);

    scale(arr, arr->length -= length);

    return res;
}
void array_dispose(array *arr)
{
    free(arr->elements);
    free(arr);
}
