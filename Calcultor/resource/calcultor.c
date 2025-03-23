#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "calcultor.h"
int main(){   // 大概顺序:输入 → 分词 → 转后缀 → 计算 → 输出 → 释放内存
	char exp[256];
	while(1){
	printf("请正确输入你的计算式(只能满足四则运算法则)|(输入stop停止程序)：\n");
	fgets(exp,sizeof(exp),stdin);  //获取表达式到exp中
	exp[strcspn(exp,"\n")]='\0';  //去除换行，变成字符串 
	if(strcmp(exp,"stop")==0){  //停止
		break;
	}
	int count,postfixcount;  // count为有效token的数量，postfixcount为后缀表达式长度  
	//分词 
	Token*token=tokenize(exp, &count);
	//中缀转后缀
	Token*postfix=infixToPostfix(token, count, &postfixcount);
	//计算四则运算
	double result= evaluatePostfix(postfix, postfixcount);
	// 结果
	printf("计算结果为:%g\n",result);
	//释放存储的空间
	free(token);
	free(postfix);}
	return 0;
}
void initOpStack(OpStack *s) {
 s->top = NULL; 
 }  // 初始化符号空栈
int isEmptyOpStack(OpStack *s) { 
return s->top == NULL;
 }  // 判断符号栈是否为空
void pushOp(OpStack *s, char op) {     //插入符号函数
    OpNode *node = (OpNode *)malloc(sizeof(OpNode));  // 动态分配新节点
    node->op = op;
    node->next = s->top;  // 新节点插入到链表头部
    s->top = node;        // 更新链栈顶指针
}
char popOp(OpStack *s) {      // define 退出符号函数
    if (isEmptyOpStack(s)) return '\0';  // 如果空栈返回空字符
    OpNode *node = s->top;      // 取出栈顶节点
    char op = node->op;
    s->top = node->next;        // 更新栈顶指针到下一个节点
    free(node);                 // 释放原栈顶点的内存
    return op;                  // 返回要弹出的运算符
}
char topOp(OpStack *s) {        // 查看栈顶元素
    return (s->top) ? s->top->op : '\0';  //如果为空则返回空字符
}
void initNumStack(NumStack *s) {
 s->top = NULL; 
 }  // 初始化空数字栈
int isEmptyNumStack(NumStack *s) { 
return s->top == NULL; 
}  // 判断数字栈是否为空				
void pushNum(NumStack *s, double num) {     //define 插入数字函数
    NumNode *node = (NumNode *)malloc(sizeof(NumNode));  // 动态分配新节点
    node->num = num;
    node->next = s->top;  // 新节点插入到链表头部
    s->top = node;        // 更新栈顶指针
}
double popNum(NumStack *s) {   //define 推出数字函数
    if (isEmptyNumStack(s)) return 0.0;  // 如果空栈返回0.0
    NumNode *node = s->top;      // 取出栈顶节点
    double num = node->num;
    s->top = node->next;         // 更新栈顶指针到下一个节点
    free(node);                  // 释放原栈顶点内存
    return num;                  // 返回推出的数字
}
//define 区分数字和符号函数
Token *tokenize(const char *expr, int *count) { //将输入的字符串表达式（如 "3.14*(2+5)"）解析为 Token 数组
    int len = strlen(expr);      //计算字符串长度
    Token *tokens = malloc(len * sizeof(Token));  // 预分配一个长度为len的token数组
    int i = 0, tokenCount = 0;
    while (i < len) {
    if (isspace(expr[i])) { i++; continue; }  // 跳过空白字符
    if (isdigit(expr[i]) || expr[i] == '.') { // 处理数字（含小数点和科学计数法）
    char buffer[32];
    int j = 0;
    while (i < len && (isdigit(expr[i]) || expr[i] == '.' || expr[i] == 'e' || expr[i] == 'E')) {
     buffer[j++] = expr[i++];  // 将连续数字字符存入buffer
}		
    buffer[j] = '\0';
    tokens[tokenCount].type = NUMBER;
    tokens[tokenCount].value.num = atof(buffer);  // 转换为double
    tokenCount++;
} else {  // 处理运算符或括号
    tokens[tokenCount].type = (expr[i] == '(' || expr[i] == ')') ? PAREN : OPERATOR;
    tokens[tokenCount].value.op = expr[i];
    tokenCount++;
    i++;
    }
}
    *count = tokenCount;  // 返回有效Token数量
    return tokens;        // 返回Token数组指针
}
// define 中缀转后缀函数 输入示例：3 + 4 * 2 / (1 - 5) 输出后缀表达式：3 4 2 * 1 5 - / +
Token *infixToPostfix(Token *infix, int count, int *postfixCount) {
    OpStack stack;         // 开个运算符栈
    initOpStack(&stack);   // 初始化运算符栈
    Token *postfix = malloc(count * sizeof(Token));  // 建立存储后缀表达式
    int idx = 0;
    for (int i = 0; i < count; i++) { // 获得中缀表达式数量
        Token token = infix[i];
        if (token.type == NUMBER) {  // 数字直接输出
            postfix[idx++] = token;  //数字直接输出
        } else if (token.value.op == '(') {  // 左括号入栈
            pushOp(&stack, '(');
        } else if (token.value.op == ')') {   // 遇到右括号弹出栈顶直到左括号
            while (topOp(&stack) != '(') {
                postfix[idx++] = (Token){OPERATOR, .value.op = popOp(&stack)};  //栈顶符号输出
            }
            popOp(&stack);  // 弹出左括号但不输出
        } else {  // 普通运算符
            // 弹出栈顶优先级≥当前运算符的运算符
            while (!isEmptyOpStack(&stack) && 
                   topOp(&stack) != '(' && 
                   getPriority(token.value.op) <= getPriority(topOp(&stack))) {  //比较符号优先级
                postfix[idx++] = (Token){OPERATOR, .value.op = popOp(&stack)};
            }
            pushOp(&stack, token.value.op);  // 当前运算符入栈
        }
    }
    // 弹出栈中剩余运算符
    while (!isEmptyOpStack(&stack)) {
        postfix[idx++] = (Token){OPERATOR, .value.op = popOp(&stack)};
    }
    *postfixCount = idx;  // 表示返回后缀表达式长度
    return postfix;    // 返回后缀表达式数组
}
// 获取运算符优先级
int getPriority(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;  // 括号优先级最低
}
// define 计算后转表达式
double evaluatePostfix(Token *postfix, int count) {
    NumStack stack;  // 数字栈
    initNumStack(&stack); // 初始化数字栈
    for (int i = 0; i < count; i++) {
        Token token = postfix[i];   //一次一次取出中缀表达式的值放入新建的token中
        if (token.type == NUMBER) {  // 数字入栈
            pushNum(&stack, token.value.num);
        } else {  // 运弹出两个操作数，计算后结果入栈
            double b = popNum(&stack);  // **先弹出的是右操作数**
            double a = popNum(&stack);  // **后弹出的是左操作数**
            switch (token.value.op) {
                case '+': pushNum(&stack, a + b); break;
                case '-': pushNum(&stack, a - b); break;
                case '*': pushNum(&stack, a * b); break;
                case '/': pushNum(&stack, a / b); break;
            }
        }
    }
    return popNum(&stack);  // 最终结果在栈顶
}