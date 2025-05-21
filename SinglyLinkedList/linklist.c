#include "linklist.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool InitList(LinkList *L) {
    LinkList list = (LinkList)malloc(sizeof(LNode));
    if (list == NULL) {
        return false;
    }
    list->next = NULL;
    *L = list;
    return true;
}

int Length(LinkList L) {
    if (L == NULL) {
        return 0;
    }
    int length = 0;
    LNode *node = L->next;
    while (node != NULL) {
        length++;
        node = node->next;
    }
    return length;
}

LNode *GetElem(LinkList L, int i) {
    if (L == NULL) {
        return NULL;
    }
    LNode *node = L->next;
    int j = 1;
    while (j < i && node != NULL) {
        node = node->next;
        j++;
    }
    return node;
}

LNode *LocateElem(LinkList L, int e) {
    if (L == NULL) {
        return NULL;
    }
    LNode *node = L->next;
    while (node != NULL && node->data != e) {
        node = node->next;
    }
    return node;
}

bool ListInsert(LinkList L, int i, int e) {
    if (L == NULL || i < 1) {
        return false;
    }
    LNode *node = L;
    int j = 0;
    while (j < i - 1) {
        node = node->next;
        j++;
        if (node == NULL) {
            return false;
        }
    }
    LNode *new = (LNode *)malloc(sizeof(LNode));
    if (new == NULL) {
        return false;
    }
    new->data = e;
    new->next = node->next;
    node->next = new;
    return true;
}

bool ListDelete(LinkList L, int i, int *e) {
    if (L == NULL || i < 1) {
        return false;
    }
    LNode *node = L;
    LNode *preNode = NULL;
    int j = 0;
    while (node != NULL && j < i) {
        preNode = node;
        node = node->next;
        j++;
    }
    if (node == NULL) {
        return false;
    }
    *e = node->data;
    preNode->next = node->next;
    free(node);
    return true;
}

LinkList List_HeadInsert(LinkList *L) {
    *L = (LinkList)malloc(sizeof(LNode));
    if (*L == NULL) {
        return *L;
    }
    (*L)->next = NULL;
    int inputData = 0;
    scanf("%d", &inputData);
    while (inputData != 9999) {
        LNode *node = (LNode *)malloc(sizeof(LNode));
        if (node == NULL) {
            return *L;
        }
        node->data = inputData;
        node->next = (*L)->next;
        (*L)->next = node;
        scanf("%d", &inputData);
    }
    return *L;
}

LinkList List_TailInsert(LinkList *L) {
    *L = (LinkList)malloc(sizeof(LNode));
    if (*L == NULL) {
        return *L;
    }
    (*L)->next = NULL;
    int inputData = 0;
    LNode *curNode = *L; // 尾节点指针
    scanf("%d", &inputData);
    while (inputData != 9999) {
        LNode *node = (LNode *)malloc(sizeof(LNode));
        if (node == NULL) {
            return *L;
        }
        curNode->next = node;
        node->data = inputData;
        node->next = NULL;
        curNode = node;
        scanf("%d", &inputData);
    }
    return *L;
}

void PrintList(LinkList L) {
    if (L == NULL) {
        return;
    }
    LNode *node = L->next;
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

void ListTest(void) {
    LinkList list = NULL;
    InitList(&list);        // 初始化
    List_HeadInsert(&list); // 头插法插入
    PrintList(list);        // 打印

    // 插入测试
    printf("选择在哪里插入节点, 插入多少：");
    int i = 0, e = 0;
    scanf("%d%d", &i, &e);
    ListInsert(list, i, e);
    PrintList(list);

    // 删除测试
    printf("选择在哪里删除节点：");
    scanf("%d", &i);
    ListDelete(list, i, &e);
    PrintList(list);
    printf("e: %d\n", e);

    // 按序查找节点
    printf("找第几个节点：");
    scanf("%d", &i);
    LNode *node = GetElem(list, i);
    printf("节点是：%d\n", node->data);

    // 按值查找节点
    printf("找哪个值：");
    scanf("%d", &e);
    node = LocateElem(list, e);
    printf("找到了，是：%d\n", node->data);

    // 表长
    printf("表长是：%d\n", Length(list));

    // 尾插法建立单链表
    LinkList list2 = NULL;
    List_TailInsert(&list2);
    PrintList(list2);
}
