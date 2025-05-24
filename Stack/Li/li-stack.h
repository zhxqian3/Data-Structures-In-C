// 链栈实现（不带头节点）

#ifndef LI_STACK_H
#define LI_STACK_H

#include <stdbool.h>
struct LiStack {
    int data;
    struct LiStack *next;
};

typedef struct LiStack LiStack;
typedef LiStack *LHead;

// 初始化
void InitLiStack(LHead *headPtr);

// 判断栈是否为空
bool LiStackEmpty(const LHead head);

// 入栈
bool LiPush(LHead *headPtr, int x);

// 出栈
bool LiPop(LHead *headPtr, int *x);

// 读取栈顶元素
bool GetLiTop(const LHead head, int *x);

// 销毁栈
void DestroyLiStack(LHead *headPtr);

// 测试链栈
void LiStackTest(void);

#endif
