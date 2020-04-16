#include <stdlib.h>
#include "iterator.h"

int hasNext(HashMapIterator iterator)
{
    return iterator->count < iterator->hashMap->size;
}

// ========================================================
HashMapIterator map_iterator(HashMap hashMap)
{
    HashMapIterator iterator = (HashMapIterator)malloc(sizeof(struct _HashMapIterator));
    iterator->count = 0;
    iterator->hashCode = -1;
    iterator->node = NULL;
    iterator->hashMap = hashMap;

    return iterator;
}

HashMapIteratorValue map_iterator_value()
{
    return (HashMapIteratorValue)malloc(sizeof(struct _HashMapIteratorValue));
}

HashMapIteratorValue next_map_iterator(HashMapIterator iterator, HashMapIteratorValue iteratorValue)
{
    if (!hasNext(iterator))
    {
        iteratorValue->done = 0;
        iteratorValue->value[0] = iteratorValue->value[0] = NULL;
        return iteratorValue;
    }

    ListNode *node;
    if (iterator->node != NULL && iterator->node->next != NULL)
    {
        iterator->count++;
        node = iterator->node = iterator->node->next;
    }
    else
    {
        while (++iterator->hashCode < iterator->hashMap->listSize)
        {
            node = &iterator->hashMap->list[iterator->hashCode];
            if (node->key != NULL)
            {
                iterator->count++;
                iterator->node = node;
                break;
            }
        }
    }

    iteratorValue->done = hasNext(iterator);
    iteratorValue->value[0] = node->key;
    iteratorValue->value[1] = node->value;

    return iteratorValue;
}