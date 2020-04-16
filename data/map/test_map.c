#include <stdio.h>
#include <windows.h>
#include "iterator.h"

void print_map(HashMap map)
{
    if (!map->size)
        return;

    HashMapIterator iterator = map_iterator(map);
    HashMapIteratorValue iteratorValue = map_iterator_value();
    do
    {
        next_map_iterator(iterator, iteratorValue);
        printf("{ key: %s, key: %s }\n", iteratorValue->value[0], iteratorValue->value[1]);
    } while (iteratorValue->done);
    free(iterator);
    free(iteratorValue);
}

int main()
{
    HashMap map = new_map();
    void *key = (void *)"4545";
    void *value = (void *)"asdfasdfds";

    map_set(map, (void *)"asdfasdf", value);
    map_set(map, (void *)"sasdasd", value);
    map_set(map, (void *)"asdhfgh", value);
    map_set(map, key, value);
    map_set(map, (void *)"asdfaasdasdsdf", value);
    map_set(map, (void *)"asdasg", value);
    map_set(map, (void *)"qweqeqwe", value);

    printf("key: 4545, has: %s\n", map_has(map, key) ? "true" : "false");
    printf("4545: %s\n", map_get(map, key));
    printf("remove 4545 %s\n", map_delete(map, key) ? "true" : "false");
    printf("remove 4545 %s\n", map_delete(map, key) ? "true" : "false");
    printf("key: 4545, has: %s\n", map_has(map, key) ? "true" : "false");

    print_map(map);
    map_clear(map);
    printf("clear...\n");
    print_map(map);

    map_dispose(map);
    system("pause");

    return 0;
}