#include<stdio.h>
#include<stdlib.h>

/*
笔记：多重链表中的节点的指针域会有多个，如下面的例子，包含了next和方式subList两个指针域
但是包含多个指针域的不一定是多重链表，比如双向链表就不是多重链表

作用：树，图这种复杂的数据结构可以使多重链表的来存储。
*/
typedef struct node{
    int tag;//标记位，如果tag为0，表示单元素节点，否则为广义表
    union{//子表指针域和ubList与单元数据域element复用，即共享存储空间
        int element;
        struct node *subList
    }uRegion;
    struct node *next;
}list,*pList;




void main(){
    printf("just test");
}
