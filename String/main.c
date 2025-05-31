#include "src/hstring.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 256

int main(void) {
    HString str1 = {0}, str2 = {0};
    InitString(&str1);
    InitString(&str2);

    // 输入主串
    printf("请输入主串：");
    char inputStr[SIZE] = {0};
    fgets(inputStr, SIZE, stdin);
    inputStr[strcspn(inputStr, "\n")] = '\0';
    int inputStrLen = strlen(inputStr);
    char *tmpCh = (char *)malloc(sizeof(char) * (inputStrLen + 1));
    if (tmpCh == NULL) {
        printf("err: malloc failed.\n");
        return -1;
    }
    for (int i = 1; i <= inputStrLen; i++) {
        tmpCh[i] = inputStr[i - 1];
    }
    StrAssign(&str1, tmpCh, inputStrLen);

    // 输入模式串
    printf("请输入模式串：");
    fgets(inputStr, SIZE, stdin);
    inputStr[strcspn(inputStr, "\n")] = '\0';
    inputStrLen = strlen(inputStr);
    tmpCh = (char *)malloc(sizeof(char) * (inputStrLen + 1));
    if (tmpCh == NULL) {
        printf("err: malloc failed.\n");
        return -1;
    }
    for (int i = 1; i <= inputStrLen; i++) {
        tmpCh[i] = inputStr[i - 1];
    }
    StrAssign(&str2, tmpCh, inputStrLen);

    // 检查输入
    printf("主串：");
    for (int i = 1; i <= str1.length; i++) {
        printf("%c", str1.ch[i]);
    }
    printf("\n");
    printf("模式串：");
    for (int i = 1; i <= str2.length; i++) {
        printf("%c", str2.ch[i]);
    }
    printf("\n");

    // 匹配
    int index1 = Index(&str1, &str2);
    int index2 = Index_KMP(&str1, &str2);

    printf("朴素：%d\n", index1);
    printf("KMP: %d\n", index2);

    return 0;
}
