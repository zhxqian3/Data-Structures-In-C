// 顺序栈实现

#ifndef SQ_STACK_H
#define SQ_STACK_H

#include <stdbool.h>

#define MAXSIZE 50

struct SqStack {
    int data[MAXSIZE];
    int top;
};

typedef struct SqStack SqStack;

// 初始化
void InitStack(SqStack *S);

// 判断栈是否空
bool StackEmpty(const SqStack *S);

// 入栈
bool Push(SqStack *S, int x);

// 出栈
bool Pop(SqStack *S, int *x);

// 读栈顶元素
bool GetTop(const SqStack *S, int *x);

// 测试顺序栈
void SqStackTest(void);

#endif
