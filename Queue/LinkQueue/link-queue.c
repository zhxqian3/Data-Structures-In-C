#include "link-queue.h"
#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

void InitLiQueue(LinkQueue *queue) {
    assert(queue);
    queue->front = NULL;
    queue->rear = NULL;
}

bool isLiQueueEmpty(const LinkQueue *queue) {
    assert(queue);
    return queue->front == NULL && queue->rear == NULL;
}

bool EnLiQueue(LinkQueue *queue, int x) {
    assert(queue);
    LinkNode *node = (LinkNode *)malloc(sizeof(LinkNode));
    if (node == NULL)
        return false;
    // 赋值node
    node->data = x;
    node->next = NULL;
    // 判断队列是否为空
    if (isLiQueueEmpty(queue)) {
        queue->front = node;
        queue->rear = node;
        return true;
    }
    queue->rear->next = node;
    queue->rear = node;
    return true;
}

bool DeLiQueue(LinkQueue *queue, int *x) {
    assert(queue && x != NULL);
    // 判断队是否是空
    if (isLiQueueEmpty(queue))
        return false;
    *x = queue->front->data;
    // 当只有一个节点时
    if (queue->front == queue->rear) {
        free(queue->front);
        queue->front = NULL;
        queue->rear = NULL;
        return true;
    } else {
        LinkNode *tmpNode = queue->front;
        queue->front = queue->front->next;
        free(tmpNode);
        return true;
    }
}

int GetLiQueueLen(const LinkQueue *queue) {
    assert(queue);
    // 判断队列是否是空
    if (isLiQueueEmpty(queue))
        return 0;
    // 定位当前节点
    LinkNode *node = queue->front;
    int len = 0;
    while (node != NULL) {
        len++;
        node = node->next;
    }
    return len;
}

void DestroyLiQueue(LinkQueue *queue) {
    assert(queue);
    // 当队列为空时，不进行任何操作
    if (isLiQueueEmpty(queue)) {
        return;
    }
    LinkNode *node = queue->front;
    while (node != NULL) {
        LinkNode *tmpNode = node;
        node = node->next;
        free(tmpNode);
    }
    queue->front = NULL;
    queue->rear = NULL;
}
