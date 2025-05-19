// 顺序表的实现(动态分配)

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define InitSize 10

struct SeqList {
    int *data;
    int MaxSize;
    int length;
};

typedef struct SeqList SeqList;

// 初始化
bool InitList(SeqList *L) {
    if (L != NULL) {
        L->data = (int *)malloc(sizeof(int) * InitSize);
        if (L->data == NULL) {
            return false;
        }
        L->MaxSize = InitSize;
        L->length = 0;
        return true;
    } else {
        return false;
    }
}

// 增加最大长度
bool AppendList(SeqList *L, int appendSize) {
    if (L == NULL) {
        return false;
    }
    int *newData = (int *)malloc(sizeof(int) * (L->MaxSize + appendSize));
    if (newData == NULL) {
        return false;
    }
    for (int i = 0; i < L->length; i++) {
        newData[i] = L->data[i];
    }
    int *oldData = L->data;
    L->data = newData;
    L->MaxSize = L->MaxSize + appendSize;
    free(oldData);
    return true;
}

// 插入操作
bool ListInsert(SeqList *L, int i, int e) {
    if (L == NULL) {
        return false;
    }
    if (i < 1 || i > L->length + 1) {
        return false;
    }
    if (L->length >= L->MaxSize) {
        bool isSuccess = AppendList(L, 1);
        if (isSuccess == false) {
            return false;
        }
    }
    for (int j = L->length; j >= i; j--) {
        L->data[j] = L->data[j - 1];
    }
    L->data[i - 1] = e;
    L->length++;
    return true;
}

// 删除操作
bool ListDelete(SeqList *L, int i, int *e) {
    if (L == NULL) {
        return false;
    }
    if (i < 1 || i > L->length) {
        return false;
    }
    *e = L->data[i - 1];
    for (int j = i - 1; j < L->length - 1; j++) {
        L->data[j] = L->data[j + 1];
    }
    L->length--;
    return true;
}

// 查找操作
int LocateElem(SeqList *L, int e) {
    if (L == NULL) {
        return -1;
    }
    for (int i = 0; i < L->length; i++) {
        if (L->data[i] == e) {
            return i + 1;
        }
    }
    return -1;
}

int main(void) {
    SeqList list = {0};
    bool real = false;
    real = InitList(&list); // 初始化
    if (real == false) {
        printf("初始化失败\n");
        return 1;
    }

    // 存入数据
    for (int i = 0; i < 10; i++) {
        real = ListInsert(&list, i + 1, i);
        if (real == false) {
            printf("存入数据失败\n");
            return 1;
        }
    }

    // 打印
    for (int i = 0; i < list.length; i++) {
        printf("%d ", list.data[i]);
    }
    printf("\n");

    // 删除
    int deleteData = 0;
    ListDelete(&list, 8, &deleteData);

    // 打印
    for (int i = 0; i < list.length; i++) {
        printf("%d ", list.data[i]);
    }
    printf("\n");

    // 查找
    int findNum = 6;
    int index = LocateElem(&list, findNum);
    printf("%d在第%d位上\n", findNum, index);

    return 0;
}
