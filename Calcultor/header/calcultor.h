#ifndef CALCULATOR_H
#define CALCULATOR_H
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
// define 数字 运算符 和 括号
typedef enum { 
NUMBER, OPERATOR, PAREN
 } TokenType;  // 标记类型：数字、运算符、括号
//define 
typedef struct {    //使用联合体可以节省空间
    TokenType type;     // 标记类型
    union {             // 联合体：根据类型存储不同值
        double num;    // 如果是数字，存储数值
        char op;        // 如果是运算符或括号，存储字符
    } value;
} Token;
// define 数字栈链  和   符号栈链

// define4 fuhao 如: * ,/,+.-

typedef struct OpNode {     // 符号链栈
	char op;               // define 存储符号
	struct OpNode*next;    // define 指向下一个节点的指针
}OpNode;

typedef struct {
	struct OpNode*top;  //define 栈顶指针
}OpStack;

void initOpStack(OpStack *s);// 初始化符号空栈
int isEmptyOpStack(OpStack *s);// 判断符号栈是否为空
void pushOp(OpStack *s, char op);   //插入符号函数
char popOp(OpStack *s) ;  // define 退出符号函数
char topOp(OpStack *s);       // 查看栈顶元素
//define shuzi   如:1，2，3

typedef struct NumNode{  //define 数字 链栈
	double num;          //define 存储数字
	struct NumNode*next; //define 指向下一个节点
}NumNode;

typedef struct{
	struct NumNode*top;  //define 数字链栈头指针
}NumStack;
void initNumStack(NumStack *s);// 初始化空数字栈
int isEmptyNumStack(NumStack *s);  // 判断数字栈是否为空
void pushNum(NumStack *s, double num); //define 插入数字函数
double popNum(NumStack *s); //define 推出数字函数
//define 区分数字和符号函数
Token *tokenize(const char *expr, int *count); //将输入的字符串表达式（如 "3.14*(2+5)"）解析为 Token 数组
// define 中缀转后缀函数 输入示例：3 + 4 * 2 / (1 - 5) 输出后缀表达式：3 4 2 * 1 5 - / +
Token *infixToPostfix(Token *infix, int count, int *postfixCount);
// 获取运算符优先级
int getPriority(char op);
// define 计算后转表达式
double evaluatePostfix(Token *postfix, int count) ;

#endif