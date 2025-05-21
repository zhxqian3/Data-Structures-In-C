// 单链表实现（有头节点）
#ifndef LINKLIST_H
#define LINKLIST_H

#include <stdbool.h>

// 定义
struct LNode {
    int data;
    struct LNode *next;
};

typedef struct LNode LNode;
typedef LNode *LinkList;

// 初始化
bool InitList(LinkList *L);

// 求表长
int Length(LinkList L);

// 按序号查找节点
LNode *GetElem(LinkList L, int i);

// 按值查找节点
LNode *LocateElem(LinkList L, int e);

// 插入节点
bool ListInsert(LinkList L, int i, int e);

// 删除节点
bool ListDelete(LinkList L, int i, int *e);

// 采用头插法建立单链表
LinkList List_HeadInsert(LinkList *L);

// 采用尾插法建立单链表
LinkList List_TailInsert(LinkList *L);

// 打印链表
void PrintList(LinkList L);

// 测试函数
void ListTest(void);

#endif
