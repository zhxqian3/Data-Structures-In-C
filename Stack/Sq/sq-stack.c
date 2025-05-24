#include "sq-stack.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

void InitStack(SqStack *S) {
    assert(S);
    S->top = -1;
}

bool StackEmpty(const SqStack *S) {
    assert(S);
    return S->top == -1;
}

bool Push(SqStack *S, int x) {
    assert(S);
    // 判断栈是否满
    if (S->top == MAXSIZE - 1)
        return false;
    S->top++;
    S->data[S->top] = x;
    return true;
}

bool Pop(SqStack *S, int *x) {
    assert(S && x);
    // 判断栈是否空
    if (S->top == -1)
        return false;
    *x = S->data[S->top];
    S->top--;
    return true;
}

bool GetTop(const SqStack *S, int *x) {
    assert(S && x);
    // 判断栈是否为空
    if (S->top == -1)
        return false;
    *x = S->data[S->top];
    return true;
}

void SqStackTest(void) {
    printf("------------------------------\n");
    printf("SqStackTest(): \n");
    SqStack stack = {0}; // 创建stack
    InitStack(&stack);   // 初始化stack
    if (StackEmpty(&stack))
        printf("此时栈为空\n");

    printf("尝试在栈为空时pop:\n");
    int topData = 0;
    if (!Pop(&stack, &topData))
        printf("Pop 失败\n");

    for (int i = 0; i < 10; i++) {
        if (Push(&stack, i)) // 入栈
            printf("%d push success\n", i);
    }
    if (!StackEmpty(&stack))
        printf("此时栈为非空\n");

    GetTop(&stack, &topData); // 读取栈顶元素
    printf("栈顶元素：%d\n", topData);

    for (int i = 0; i < 10; i++) {
        if (Pop(&stack, &topData)) // 出栈
            printf("%d pop success\n", topData);
    }
    if (StackEmpty(&stack))
        printf("此时栈为空\n");

    // 测试栈满情况下push
    printf("尝试在栈满时push:\n");
    for (int i = 0; i < MAXSIZE; i++) {
        Push(&stack, i);
    }
    if (!Push(&stack, 50))
        printf("栈已满, push 失败\n");
}
