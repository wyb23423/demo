#include <string.h>
#include <stdlib.h>
#include "iterator.h"

#define INIT_SIZE 10

static int hashCode(int length, void *key)
{
    char *k = (char *)key;
    unsigned long h = 0;
    while (*k)
    {
        h = (h << 4) + *k++;
        unsigned long g = h & 0xF0000000L;
        if (g)
        {
            h ^= g >> 24;
        }
        h &= ~g;
    }

    return h % length;
}

static int equal(void *key1, void *key2)
{
    return !strcmp((char *)key1, (char *)key2);
}

static void init_data(HashMap map)
{
    for (int i = 0; i < map->listSize; i++)
    {
        map->list[i].key = NULL;
        map->list[i].value = NULL;
        map->list[i].next = NULL;
    }
}

static void free_data(HashMap map)
{
    for (int i = 0; i < map->listSize; i++)
    {
        // 释放冲突值内存
        ListNode *node = map->list[i].next;
        while (node != NULL)
        {
            ListNode *next = node->next;
            free(node);
            node = next;
        }

        map->list[i].next = NULL;
    }
}

static void scale(HashMap map, int size)
{
    int length = map->size;
    ListNode listNodes[length];

    if (length)
    {
        HashMapIterator iterator = map_iterator(map);
        HashMapIteratorValue iteratorValue = map_iterator_value();
        for (int i = 0; i < length; i++)
        {
            next_map_iterator(iterator, iteratorValue);
            listNodes[i].key = iteratorValue->value[0];
            listNodes[i].value = iteratorValue->value[1];
            listNodes[i].next = NULL;
        }
        free(iterator);
        free(iteratorValue);

        free_data(map);
        map->size = 0;
    }

    map->list = (ListNode *)calloc(map->listSize = size, sizeof(ListNode));
    init_data(map);

    // 将所有键值对重新写入内存
    for (int i = 0; i < length; i++)
        map_set(map, listNodes[i].key, listNodes[i].value);

    free(listNodes);
}

// ======================================================================
HashMap new_map()
{
    HashMap map = (HashMap)malloc(sizeof(struct _HashMap));
    map->size = 0;
    map->listSize = INIT_SIZE;
    map->hashCode = &hashCode;
    map->equal = &equal;

    map->list = (ListNode *)calloc(INIT_SIZE, sizeof(ListNode));
    init_data(map);

    return map;
}

void *map_get(HashMap map, void *key)
{
    ListNode *node = &map->list[map->hashCode(map->listSize, key)];

    while (node->key != NULL && !map->equal(node->key, key))
        node = node->next;

    return node->value;
}

void map_set(HashMap map, void *key, void *value)
{
    if (map->size > map->listSize)
    {
        // 内存扩充至原来的两倍
        // *注: 扩充时考虑的是当前存储元素数量与存储空间的大小关系，而不是存储空间是否已经存满，
        // 例如: 存储空间为10，存入了10个键值对，但是全部冲突了，所以存储空间空着9个，其余的全部挂在一个上面，
        // 这样检索的时候和遍历查询没有什么区别了，可以简单这样理解，当我存入第11个键值对的时候一定会发生冲突，
        // 这是由哈希函数本身的特性(取模)决定的，冲突就会导致检索变慢，所以这时候扩充存储空间，对原有键值对进行
        // 再次散列，会把冲突的数据再次分散开，加快索引定位速度。
        scale(map, map->listSize * 2);
    }

    ListNode *node = &map->list[map->hashCode(map->listSize, key)];
    if (node->key == NULL)
    {
        node->key = key;
        node->value = value;
    }
    else
    {
        while (1)
        {
            if (map->equal(node->key, key))
            {
                // 已经存在, 直接覆盖
                node->value = value;
                return;
            }

            if (node->next == NULL)
                break;

            node = node->next;
        }

        ListNode *next = node->next = (ListNode *)malloc(sizeof(struct _ListNode));
        next->key = key;
        next->value = value;
        next->next = NULL;
    }

    map->size++;
}

int map_delete(HashMap map, void *key)
{
    ListNode *node = &map->list[map->hashCode(map->listSize, key)];
    if (node->key == NULL)
        return 0;

    ListNode *prev = NULL;
    while (node != NULL && !map->equal(node->key, key))
    {
        prev = node;
        node = node->next;
    }

    if (node == NULL)
        return 0;

    ListNode *next = node->next;
    if (prev == NULL)
    {
        if (next != NULL)
        {
            node->key = next->key;
            node->value = next->value;
            node->next = next->next;
        }
        else
            node->key = node->value = node->next = NULL;
    }
    else
    {
        prev->next = next;
        free(node);
    }

    map->size--;

    int halfSize = map->listSize / 2;
    if (map->size < halfSize)
        scale(map, halfSize);

    return 1;
}

int map_has(HashMap map, void *key)
{
    ListNode *node = &map->list[map->hashCode(map->listSize, key)];
    if (node->key == NULL)
        return 0;

    while (node != NULL)
    {
        if (map->equal(node->key, key))
            return 1;

        node = node->next;
    }

    return 0;
}

void map_clear(HashMap map)
{
    free_data(map);
    map->size = 0;
    init_data(map);
}

void map_dispose(HashMap map)
{
    free_data(map);
    free(map->list);
    map->list = NULL;

    map->size = 0;
    map->listSize = INIT_SIZE;

    free(map);
}
