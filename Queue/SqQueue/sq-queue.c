#include "sq-queue.h"
#include <assert.h>
#include <stdbool.h>

void InitSqQueue(SqQueue *queue) {
    assert(queue);
    queue->front = 0; // 队首指针初始化
    queue->rear = 0;  // 队首指针初始化
}

bool isSqQueueEmpty(const SqQueue *queue) {
    assert(queue);
    return queue->front == queue->rear;
}

bool EnSqQueue(SqQueue *queue, int x) {
    assert(queue);
    // 判断队是否已满
    if (isSqQueueFull(queue))
        return false;
    queue->data[queue->rear] = x;
    queue->rear = (queue->rear + 1) % MAXSIZE; // 更新rear
    return true;
}

bool isSqQueueFull(const SqQueue *queue) {
    assert(queue);
    return (queue->rear + 1) % MAXSIZE == queue->front; // 牺牲了一个存储空间
}

bool DeSqQueue(SqQueue *queue, int *x) {
    assert(queue && x);
    // 判断队是否为空
    if (isSqQueueEmpty(queue))
        return false;
    *x = queue->data[queue->front];
    queue->front = (queue->front + 1) % MAXSIZE; // 更新front
    return true;
}

int GetSqQueueLen(const SqQueue *queue) {
    assert(queue);
    // 判断队空
    if (isSqQueueEmpty(queue))
        return 0;
    if (queue->rear > queue->front)
        return queue->rear - queue->front;
    else
        return MAXSIZE - queue->front + queue->rear;
}
