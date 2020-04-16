#ifndef hashmap_iterator_h
#define hashmap_iterator_h

#include "map.h"

// 迭代器结构
typedef struct _HashMapIterator
{
    ListNode *node; // 迭代器当前指向
    int count;      // 迭代次数
    int hashCode;   // 键值对的哈希值
    HashMap hashMap;
} * HashMapIterator;

typedef struct _HashMapIteratorValue
{
    int done;
    void *value[2];
} * HashMapIteratorValue;

HashMapIterator map_iterator(HashMap hashMap);
HashMapIteratorValue map_iterator_value();
HashMapIteratorValue next_map_iterator(HashMapIterator iterator, HashMapIteratorValue iteratorValue);

#endif