#include "array.h"
#include <windows.h>
#include <stdio.h>
#include <crtdefs.h>

struct custom_data
{
    int value;
};

void printData(void *data, int index)
{
    if (data == NULL)
        printf("%d: NULL   ", index);
    else
        printf("%d: %d   ", index, *(int *)data);
}

void test_array()
{
    array *arr = array_create(10);
    int data[12];
    for (int i = 0; i < 11; i++)
    {
        data[i] = i;
        array_append(arr, &data[i]);
    }

    array_iterator(arr, &printData);
    putchar('\n');

    array *r = array_remove(arr, 8, 4);
    array_iterator(arr, &printData);
    putchar('\n');

    array_insert_multiple(arr, 2, 3, r->elements);
    array_iterator(arr, &printData);
    putchar('\n');

    data[12] = 100;
    array_set(arr, 13, &data[12]);
    array_iterator(arr, &printData);
    putchar('\n');

    printData(array_get(arr, 4), 4);
    printData(array_get(arr, 15), 15);
    putchar('\n');

    array_dispose(arr);
}

int main()
{
    test_array();

    system("pause");
    return 0;
}