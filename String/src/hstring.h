// 串的堆分配存储实现
#ifndef HSTRING_H
#define HSTRING_H

#include <stdbool.h>

struct HString {
    char *ch;   // 串的手元素地址
    int length; // 串的长度
    int size;   // 串的容量
};

typedef struct HString HString;

// 初始化
void InitString(HString *str);

// 赋值, chars 参数必须是动态分配得来的
bool StrAssign(HString *str, const char *chars, const int length);

// 复制
bool StrCopy(HString *str, const HString *sourceStr);

// 判空
bool StrEmpty(const HString *str);

// 比较
// str1 > str2 返回正数; < 返回负数; = 返回 0
int StrCompare(const HString *str1, const HString *str2);

// 求串长
int StrLength(const HString *str);

// 求子串
bool SubString(HString *subStr, const HString *str, const int pos,
               const int len);

// 串联
bool Concat(HString *retStr, const HString *str1, const HString *str2);

// 清空
void ClearString(HString *str);

// 销毁
void DestroyString(HString *str);

// 朴素模式匹配, 没有找到返回0
int Index(const HString *str, const HString *templateStr);

// KMP 匹配
int Index_KMP(const HString *str, const HString *templateStr);

#endif
