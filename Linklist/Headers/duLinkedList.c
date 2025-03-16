#include<stdio.h>
#include<stdlib.h>
#include "duLinkedList.h"

int main()
{
	DuLinkedList head = NULL;
	
	int chioce,position,data;

	
	while(1){
		printf("\n*************************\n");
		printf("* 1.初始化链表*\n");
		printf("* 2.插入新节点*\n");
		printf("* 3.反转链表  *\n");
		printf("* 4.输出链表  *\n");
		printf("* 5.中间链表  *\n");
		printf("* 6.判断是否成环*\n");
		printf("* 7.删除节点  *\n");
		printf("* 8.奇偶反转  *\n");
		printf("* 9.查询链表  *\n");
		printf("* 10.构造循环链表*\n");
		printf("* 11.退出系统 *\n");
		printf("\n*************************\n");
		printf("请输入对应数字(0~11):");
		scanf("%d",&chioce);
		
		switch(chioce){
			case 1:	
				InitList_DuL(&head);
				break;
			case 2:
				printf("输入要插入的节点：");
				scanf("%d",&position);
				printf("要插入节点的数据:");
				scanf("%d",&data);
				InsertAtPosition_DuL(& head, position, data);
				break;
			case 3:
			if(ReverseList_DuL(&head)==SUCCESS){
				printf("反转成功");
			}else{
				printf("反转失败");
			}
				break;
			case 4:
				PrintList_DuL( head);
				break;
			case 5:
				printf("中间链表是%d\n",FindMiddleData_DuL(head));
				break;
			case 6:
			if(IsCircular(head)==SUCCESS){
				printf("是循环链表");
			}else{
				printf("不是循环链表");
			}
				break;
			case 7:
				printf("要删除的节点数据:");
				scanf("%d",&data);
				DeleteNodeByValue_DuL(& head,  data);
				break;
			case 8:
				SwapOddEvenNodes(& head);
				printf("奇偶反转成功");
				break;
			case 9:
				printf("要查询的节点数据:");
				scanf("%d",&data);
				SearchNode_DuL( head, data);
				break;
			case 10:
				ConvertToCircular_DuL(& head);
				break;
			case 11:
				
			return 0;
				
		}
		
	}
	
	
}


void InitList_DuL(DuLinkedList* head) {
    int count;
    printf("创建几个节点（不超过20）：");
    while(1) {
        if(scanf("%d", &count) != 1 || count < 1 || count > 20) {
            printf("输入无效！请输入1-20的整数：");
            while(getchar() != '\n'); 
            continue;
        }
        break;
    }
    DuLNode* tail = NULL;
    for(int i = 0; i < count; i++) {
        DuLNode* newNode = (DuLNode*)malloc(sizeof(DuLNode));
        if(!newNode) {
            printf("内存分配失败！\n");
            exit(EXIT_FAILURE);
        }
        printf("请输入第%d个节点的数据：", i+1);
        while(1) {
            if(scanf("%d", &(newNode->data)) != 1) {
                printf("输入错误！请重新输入：");
                while(getchar() != '\n'); 
                continue;
            }
            break;
        }
        newNode->prior = tail;
        newNode->next = NULL;
        if(*head == NULL) {
            *head= newNode;
        } else {
            tail->next = newNode;
        }
        tail = newNode;
    }
    printf("成功创建包含%d个节点的双向链表！\n", count);
}
Status ReverseList_DuL(DuLinkedList *head){
 if (*head == NULL || (*head)->next == NULL) {
        return ERROR;
    }

    DuLNode* current = *head;
    DuLNode* temp = NULL;
    while (current != NULL) {
        temp = current->prior;
        current->prior = current->next;
        current->next = temp;
        current = current->prior;
    }
    if (temp != NULL) {
        *head = temp->prior;
    }
    return SUCCESS;
}
void PrintList_DuL(DuLinkedList L) {
    if (!L || L->next == L) {
        printf("空链表\n");
        return;
    }
    DuLNode *p = L;
    while (p != NULL) {
        printf("%d -> ", p->data);
        p = p->next;
    }
    printf("NULL\n");
}
void InsertAtPosition_DuL(DuLinkedList* head, int position, int data) {
    if (position < 1) {
        printf("插入位置无效！\n");
        return;
    }
    DuLNode* newNode = (DuLNode*)malloc(sizeof(DuLNode));
    if (!newNode) {
        printf("内存分配失败！\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    DuLNode* current = *head;
    for (int i = 1; i < position - 1 && current != NULL; i++) {
        current = current->next;
    }
    if (current == NULL) {
        printf("插入位置超出链表长度！\n");
        free(newNode);
        return;
    }
    newNode->next = current->next;
    newNode->prior = current;
    if (current->next != NULL) {
        current->next->prior = newNode;
    }
    current->next = newNode;
    printf("成功在第 %d 个位置插入节点，数据为：%d\n", position, data);
}
int FindMiddleData_DuL(DuLinkedList head) {
    if (head == NULL) {
        printf("链表为空，无法查找中间节点！\n");
        return -1; 
    }
    DuLNode* slow = head; 
    DuLNode* fast = head;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;      
        fast = fast->next->next;
    }
    return slow->data;
}
void DeleteNodeByValue_DuL(DuLinkedList* head, int data) {
    if (*head == NULL) {
        printf("链表为空，无法删除节点！\n");
        return;
    }
    DuLNode* current = *head;
    while (current != NULL && current->data != data) {
        current = current->next;
    }
    if (current == NULL) {
        printf("未找到数据为 %d 的节点！\n", data);
        return;
    }
    if (current == *head) {
        *head = current->next; 
        if (*head != NULL) {
            (*head)->prior = NULL; 
        }
    } else {
        if (current->prior != NULL) {
            current->prior->next = current->next; 
        }
        if (current->next != NULL) {
            current->next->prior = current->prior;
        }
    }
    free(current);
    printf("成功删除数据为 %d 的节点！\n", data);
}
void SearchNode_DuL(DuLinkedList head, int data) {
    if (head == NULL) {
        printf("链表为空，无法查询节点！\n");
        return;
    }
    DuLNode* current = head;
    int position = 1; 
    int found = 0; 
    while (current != NULL) {
        if (current->data == data) {
            printf("找到数据为 %d 的节点，位置为第 %d 个节点。\n", data, position);
            found = 1;
            break;
        }
        current = current->next;
        position++;
    }
    if (!found) {
        printf("未找到数据为 %d 的节点！\n", data);
    }
}
void ConvertToCircular_DuL(DuLinkedList* head) {
    if (*head == NULL) {
        printf("链表为空，无法转换为循环链表！\n");
        return;
    }
    DuLNode* tail = *head;
    while (tail->next != NULL) {
        tail = tail->next;
    }
    tail->next = *head;
    (*head)->prior = tail;
    printf("成功将双向链表转换为循环双向链表！\n");
}
Status IsCircular(DuLinkedList head) {
    if (head == NULL) return ERROR; 
    DuLNode* slow = head;
    DuLNode* fast = head;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;          
        fast = fast->next->next;   
        if (slow == fast) {
            return SUCCESS;
        }
    }
    return ERROR; 
}
void SwapOddEvenNodes(DuLinkedList* head) {
    if (*head == NULL || (*head)->next == NULL) {
        return;
    }
    DuLNode* current = *head;
    *head = (*head)->next; 
    while (current != NULL && current->next != NULL) {
        DuLNode* nextNode = current->next; 
        DuLNode* nextPair = nextNode->next; 
        nextNode->prior = current->prior;
        if (current->prior != NULL) {
            current->prior->next = nextNode;
        }
        current->next = nextNode->next;
        if (nextNode->next != NULL) {
            nextNode->next->prior = current;
        }
        nextNode->next = current;
        current->prior = nextNode;
        current = nextPair;
    }
}