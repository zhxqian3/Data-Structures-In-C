#include "li-stack.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void InitLiStack(LHead *headPtr) {
    assert(headPtr);
    (*headPtr) = NULL; // 初始化时指向NULL
}

bool LiStackEmpty(const LHead head) { return head == NULL; }

bool LiPush(LHead *headPtr, int x) {
    assert(headPtr);
    LiStack *stack = (LiStack *)malloc(sizeof(LiStack));
    if (stack == NULL)
        return false;
    stack->data = x;
    stack->next = (*headPtr);
    (*headPtr) = stack;
    return true;
}

bool LiPop(LHead *headPtr, int *x) {
    assert(headPtr && x);
    // 判断栈是否为空
    if (LiStackEmpty(*headPtr))
        return false;
    *x = (*headPtr)->data;
    // 存储当前的head
    LiStack *tmpHead = (*headPtr);
    // 将head指向下一个节点
    (*headPtr) = (*headPtr)->next;
    free(tmpHead);
    return true;
}

bool GetLiTop(const LHead head, int *x) {
    assert(x);
    // 判断是否是空
    if (LiStackEmpty(head))
        return false;
    *x = head->data;
    return true;
}

void DestroyLiStack(LHead *headPtr) {
    assert(headPtr);
    int x = 0;
    while (LiPop(headPtr, &x)) {
        ;
    }
}

void LiStackTest(void) {
    printf("------------------------------\n");
    printf("LiStackTest(): \n");

    LHead lHead = NULL;

    // 初始化
    InitLiStack(&lHead);

    // 判断栈是否空
    if (LiStackEmpty(lHead))
        printf("还没入栈，当然是空\n");

    // 测试入栈
    for (int i = 0; i < 10; i++) {
        if (LiPush(&lHead, i))
            printf("%d入栈成功\n", i);
    }

    // 此时再判断栈是否为空
    if (!LiStackEmpty(lHead))
        printf("入栈了10个, 当然是非空的\n");

    // 查找栈顶
    int data = 0;
    if (GetLiTop(lHead, &data))
        printf("栈顶元素为：%d\n", data);

    // 测试出栈
    for (int i = 0; i < 11; i++) {
        if (LiPop(&lHead, &data))
            printf("%d出栈成功\n", data);
        else
            printf("尝试出栈第11个，当然是失败的\n");
    }

    // 此时再查找栈顶
    if (!GetLiTop(lHead, &data))
        printf("都出栈完了，当然找不到了\n");

    // 测试销毁栈
    // 先创建
    for (int i = 0; i < 10; i++) {
        if (LiPush(&lHead, i))
            printf("%d入栈成功\n", i);
    }
    DestroyLiStack(&lHead);
    if (lHead == NULL) {
        printf("销毁成功\n");
    }
}
