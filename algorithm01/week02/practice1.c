#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
struct Node {
    ElementType Data;
    PtrToNode   Next;
};
typedef PtrToNode List;

List Read(); /* 细节在此不表 */
void Print( List L ); /* 细节在此不表；空链表将输出NULL */

List Merge( List L1, List L2 );



int main()
{
    List L1, L2, L;
    L1 = Read();
    L2 = Read();

    L = Merge(L1, L2);
    Print(L);
    Print(L1);
    Print(L2);

    return 0;
}




/* 你的代码将被嵌在这里 */
void Print(PtrToNode list){
    PtrToNode p = list->Next;
    if(p==NULL){
        printf("NULL\n");
        return;
    }
    while(p!=NULL){
        printf("%d ",p->Data);
        p = p->Next;
    }
    printf("\n");
}

List Read(){
    int count,i,value;
    scanf("%d",&count);
    PtrToNode list = (PtrToNode)malloc(sizeof(struct Node));
    PtrToNode rear = list;
    if(list){
        list->Next=NULL;
    }
    for(i=0;i<count;i++){
        PtrToNode newNode = (PtrToNode)malloc(sizeof(struct Node));
        scanf("%d",&value);
        newNode->Data=value;
        newNode->Next = rear->Next;
        rear->Next = newNode;
        rear=newNode;
    }
    return list;
}


List Merge( List L1, List L2 ){
    PtrToNode temp;
    PtrToNode list = (PtrToNode)malloc(sizeof(struct Node));
    PtrToNode rear = list;
    PtrToNode p1=L1->Next,p2=L2->Next;
    if(list){
        list->Next=NULL;
    }
    while(p1 && p2){
        if(p1->Data<=p2->Data){
            temp = p1;
            rear->Next = temp;
            rear=temp;
            p1 = p1->Next;
        }else{
            temp = p2;
            rear->Next = temp;
            rear=temp;
            p2 = p2->Next;
        }
    }

    while(p1){
        temp = p1;
        rear->Next = temp;
        rear=temp;
        //free(p1);
        p1 = p1->Next;
    }
    while(p2){
        temp = p2;
        rear->Next = temp;
        rear=temp;
        //free(p2);
        p2 = p2->Next;
    }
    L1->Next=NULL;
    L2->Next=NULL;
    //Print(list);
    return list;

}
