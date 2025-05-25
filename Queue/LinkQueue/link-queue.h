// 链式队列实现（不带头节点）
#ifndef LINK_QUEUE_H
#define LINK_QUEUE_H

#include <stdbool.h>
struct LinkNode {
    int data;
    struct LinkNode *next;
};

typedef struct LinkNode LinkNode;

struct LinkQueue {
    LinkNode *front; // 队头指针
    LinkNode *rear;  // 队尾指针
};

typedef struct LinkQueue LinkQueue;

// 初始化
void InitLiQueue(LinkQueue *queue);

// 判断队列是否为空
bool isLiQueueEmpty(const LinkQueue *queue);

// 入队
bool EnLiQueue(LinkQueue *queue, int x);

// 出队
bool DeLiQueue(LinkQueue *queue, int *x);

// 求队列长度
int GetLiQueueLen(const LinkQueue *queue);

// 销毁链式队列
void DestroyLiQueue(LinkQueue *queue);

#endif
