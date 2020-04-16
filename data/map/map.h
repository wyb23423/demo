#ifndef hashmap_h
#define hashmap_h

typedef struct _ListNode
{
    void *key;              // 键
    void *value;            // 值
    struct _ListNode *next; // 冲突链表
} ListNode;

typedef struct _HashMap *HashMap;
// 哈希函数类型
typedef int (*HashCode)(int length, void *key);
// 判等函数类型
typedef int (*Equal)(void *key1, void *key2);
typedef struct _HashMap
{
    int size;          // 当前大小
    int listSize;      // 有效空间大小
    ListNode *list;    // 存储区域
    HashCode hashCode; // 哈希函数
    Equal equal;       // 判等函数
} * HashMap;

HashMap new_map();

void *map_get(HashMap map, void *key);
void map_set(HashMap map, void *key, void *value);
int map_delete(HashMap map, void *key);
int map_has(HashMap map, void *key);
void map_clear(HashMap map);

void map_dispose(HashMap map);

#endif