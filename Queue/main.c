#include "LinkQueue/link-queue.h"
#include "SqQueue/sq-queue.h"
#include <stdio.h>

int main(void) {
    // 测试顺序队
    printf("-----------------------------\n");
    printf("现在开始测试顺序队\n");

    SqQueue queue = {0}; // 初始化队
    InitSqQueue(&queue);

    // 判断此时队是否空
    if (isSqQueueEmpty(&queue))
        printf("isSqQueueEmpty(): success\n");

    // 入队
    int data = 0;
    for (int i = 0; i < MAXSIZE; i++) {
        EnSqQueue(&queue, i);
    }
    if (isSqQueueFull(&queue))
        printf("EnSqQueue() && isSqQueueFull(): success\n");

    // 求队长
    int len = GetSqQueueLen(&queue);
    printf("队长：%d\n", len);

    // 出队
    printf("出队：");
    for (int i = 0; i < MAXSIZE; i++) {
        DeSqQueue(&queue, &data);
        printf("%d ", data);
    }
    printf("\n");
    if (isSqQueueEmpty(&queue))
        printf("DeSqQueue() && isSqQueueEmpty(): success\n");

    // 测试链式队列
    printf("----------------------------------------------------\n");
    printf("开始测试链式队列：\n");

    // 初始化
    LinkQueue linkQueue = {0};
    InitLiQueue(&linkQueue);

    // 判队空
    if (isLiQueueEmpty(&linkQueue))
        printf("isLiQueueEmpty(): success\n");

    // 此时出队(异常情况)
    if (!DeLiQueue(&linkQueue, &data))
        printf("DeLiQueue(): success\n");

    // 入队
    for (int i = 0; i < MAXSIZE; i++) {
        EnLiQueue(&linkQueue, i);
    }
    len = GetLiQueueLen(&linkQueue);
    if (len == MAXSIZE)
        printf("EnLiQueue() && GetLiQueueLen(): success\n");

    // 出队
    printf("出队: ");
    for (int i = 0; i < MAXSIZE; i++) {
        DeLiQueue(&linkQueue, &data);
        printf("%d ", data);
    }
    printf("\n");

    // 判队空
    if (isLiQueueEmpty(&linkQueue))
        printf("队为空\n");

    // 销毁链式队列
    DestroyLiQueue(&linkQueue);

    return 0;
}
