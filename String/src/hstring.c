#include "hstring.h"
#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

void InitString(HString *str) {
    assert(str);
    str->length = 0;
    str->size = 0;
    str->ch = NULL;
}

bool StrAssign(HString *str, const char *chars, const int length) {
    assert(str);
    str->ch = (char *)chars;
    // 更新长度
    str->length = length;
    str->size = length;
    return true;
}

bool StrCopy(HString *str, const HString *sourceStr) {
    assert(str && sourceStr != NULL);
    char *newCharStr = (char *)malloc(
        sizeof(char) * (sourceStr->size + 1)); // size+1: 不用下标为0的char
    if (newCharStr == NULL) {
        return false;
    }
    free(str->ch);
    str->ch = newCharStr;
    str->length = sourceStr->length;
    str->size = sourceStr->size;
    // 将chars中的元素赋值
    for (int i = 1; i <= sourceStr->length; i++) {
        str->ch[i] = sourceStr->ch[i];
    }
    return true;
}

bool StrEmpty(const HString *str) {
    assert(str);
    return str->length == 0;
}

int StrCompare(const HString *str1, const HString *str2) {
    assert(str1 && str2 != NULL);
    for (int i = 1; i <= str1->length && i <= str2->length; i++) {
        if (str1->ch[i] != str2->ch[i]) {
            return str1->ch[i] - str2->ch[i];
        }
    }
    return str1->length - str2->length;
}

int StrLength(const HString *str) {
    assert(str);
    return str->length;
}

bool SubString(HString *subStr, const HString *str, const int pos,
               const int len) {
    assert(subStr && str != NULL);
    // 当超出范围时
    if (pos + len - 1 > str->length)
        return false;
    // 为 substr 分配空间
    char *subCh = (char *)malloc(sizeof(char) * (len + 1));
    if (subCh == NULL)
        return false;
    for (int i = 1; i <= len; i++) {
        subCh[i] = str->ch[pos + i - 1];
    }
    free(subStr->ch);
    subStr->ch = subCh;
    subStr->length = len;
    subStr->size = len;
    return true;
}

bool Concat(HString *retStr, const HString *str1, const HString *str2) {
    assert(retStr && str1 && str2 != NULL);
    char *new =
        (char *)malloc(sizeof(char) * (str1->length + str2->length + 1));
    if (new == NULL) {
        return false;
    }
    for (int i = 1; i <= str1->length; i++) {
        new[i] = str1->ch[i];
    }
    for (int i = 1; i <= str2->length; i++) {
        new[str1->length + i] = str2->ch[i];
    }
    free(retStr->ch);
    retStr->ch = new;
    retStr->length = str1->length + str2->length;
    retStr->size = str1->length + str2->length;
    return true;
}

void ClearString(HString *str) {
    assert(str);
    str->length = 0;
}

void DestroyString(HString *str) {
    assert(str);
    free(str->ch);
    str->ch = NULL;
    str->length = 0;
    str->size = 0;
}

int Index(const HString *str, const HString *templateStr) {
    assert(str && templateStr != NULL);
    for (int i = 1; i <= str->length - templateStr->length + 1; i++) {
        int equalFlag = 1; // 默认相等
        int j = 1;
        for (j = 1; j <= templateStr->length; j++) {
            if (str->ch[i + j - 1] != templateStr->ch[j]) {
                equalFlag = 0;
                break;
            }
        }
        if (equalFlag == 1 && j > templateStr->length) {
            return i;
        }
    }
    return 0; // 没有找到返回 0
}

int Index_KMP(const HString *str, const HString *templateStr) {
    assert(str && templateStr != NULL);
    // 模式串长度小于0时，直接返回 0
    if (templateStr->length < 0) {
        return 0;
    }
    // 求 next 数组（非标准实现）
    int next[templateStr->length + 1];
    for (int i = 1; i <= templateStr->length; i++) {
        if (i == 1) {
            next[i] = 0;
        }
        if (i > 1) {
            for (int j = i - 1; j >= 1; j--) {
                int comFlag = 1; // 假设此时能完全匹配的得上
                for (int k = j - 1; k >= 1; k--) {
                    if (templateStr->ch[k] != templateStr->ch[k + 1]) {
                        comFlag = 0;
                        break;
                    }
                }
                if (comFlag == 1) {
                    next[i] = j;
                    if (templateStr->ch[i] == templateStr->ch[j]) {
                        next[i] = next[j];
                    }
                }
            }
        }
    }
    // KMP 模式匹配
    int i = 1, j = 1;
    while (i <= str->length && j <= templateStr->length) {
        if (j == 0 || str->ch[i] == templateStr->ch[j]) {
            i++;
            j++;
        } else {
            j = next[j];
        }
    }
    if (j > templateStr->length) {
        return i - templateStr->length;
    } else {
        return 0;
    }
}
