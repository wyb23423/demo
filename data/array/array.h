#ifndef array_h
#define array_h

struct _array
{
    unsigned int initSize;
    unsigned int size;   // 数组的容量，不够可以自动进行扩容
    unsigned int length; // 当前数组中拥有数据的个数
    void **elements;
};
typedef struct _array array;

array *array_create(int size);

void *array_get(array *arr, int index);
int array_set(array *arr, int index, void *data);

int array_insert_multiple(array *arr, int index, int count, void **data);
int array_insert(array *arr, int index, void *data);
int array_append_multiple(array *arr, int count, void **data);
int array_append(array *arr, void *data);

void array_iterator(array *arr, void (*handler)(void *data, int index));

array *array_remove(array *arr, int index, int length);
void array_dispose(array *arr);

#endif