// 顺序存储的队列实现（循环队列）
#ifndef SQ_QUEUE_H
#define SQ_QUEUE_H

#include <stdbool.h>

#define MAXSIZE 50

struct SqQueue {
    int data[MAXSIZE];
    int front; // 队首指针
    int rear;  // 队尾指针
};

typedef struct SqQueue SqQueue;

// 初始化
void InitSqQueue(SqQueue *queue);

// 判对空
bool isSqQueueEmpty(const SqQueue *queue);

// 入队
bool EnSqQueue(SqQueue *queue, int x);

// 判断队是否已满
bool isSqQueueFull(const SqQueue *queue);

// 出队
bool DeSqQueue(SqQueue *queue, int *x);

// 求队的长度
int GetSqQueueLen(const SqQueue *queue);

#endif
