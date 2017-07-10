#include<stdio.h>
#include<stdlib.h>

//typedef struct linkList *list;

typedef struct linkList{
    int element;
    struct linkList *next;
}list,*pList;


pList init_linkList(){
    pList head;
    head = (pList)malloc(sizeof(list));
    if(head){
        head->next = NULL;
    }
    return head;
}

int insert(pList head,int key){
    if(head==NULL){
       printf("head node is null,don't allow insert element\n");
       return 0;
    }else{
        pList newNode = (pList)malloc(sizeof(list));
        newNode->element = key;
        newNode->next = head->next;
        head->next = newNode;
        return 1;
    }
}

pList findKth(pList head,int index){
    pList p = head->next;
    int count=0;
    while(p!=NULL){
        count++;
        if(count==index){
            return p;
        }
        p=p->next;
    }
    return NULL;
}

/*
find element by
*/
pList findElementIndex(pList head,int element){
    pList p = head->next;
    int count=0;
    while(p!=NULL){
            count++;
        if(p->element==element){
            return count;
        }
        p=p->next;
    }
    return -1;
}

pList findElement(pList head,int element){
    pList p = head->next;
    while(p!=NULL){
        if(p->element==element){
            return p;
        }
        p=p->next;
    }
    return NULL;
}

void toSring(pList head){
    pList p = head->next;
    printf("toString:");
    while(p!=NULL){
        printf("%d ",p->element);
        p=p->next;
    }
    printf("\n");
}

int deleteElement(pList head,int key){
    pList p = head,tmp;
    while(p->next!=NULL){
        if(p->next->element==key){
            p->next = p->next->next;
            tmp = p->next;
            free(p->next);
            return 1;
        }else{
            p=p->next;
        }
    }
    return 0;
}

void toStringone(pList p){
    if(p==NULL){
        printf("the node is null,don't allow to print");
    }else{
        printf("one to string:%d\n",p->element);
    }
}


void main(){
    pList head = init_linkList();
    insert(head,12);
    insert(head,13);
    insert(head,14);
    toStringone(findKth(head,2));
    printf("%d\n",deleteElement(head,12));
    //printf("%d\n",findElementIndex(head,13));
    toSring(head);
}
