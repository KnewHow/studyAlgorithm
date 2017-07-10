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

int insert(pList *rear,int key){
    if((*rear)==NULL){
       printf("head node is null,don't allow insert element\n");
       return 0;
    }else{
        pList newNode = (pList)malloc(sizeof(list));
        newNode->element = key;
        newNode->next = (*rear)->next;
        (*rear)->next = newNode;
        (*rear)=newNode;
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

void toSring(pList head){
    pList p = head->next;
    printf("toString:");
    while(p!=NULL){
        printf("%d ",p->element);
        p=p->next;
    }
    printf("\n");
}

int getListLength(pList head){
    int count=0;
    pList p = head->next;
    while(p!=NULL){
        count++;
        p = p->next;
    }
    return count;
}

void toSring2(pList head){
    pList p = head;
    printf("toString:");
    while(p!=NULL){
        printf("%d ",p->element);
        p=p->next;
    }
    printf("\n");
}

pList reverse(pList list,int k,int length){
    int cnt=0;
    pList newNode = list->next;
    pList oldNode = newNode->next;
    pList temp;
    int i=0;
    if(k==1){
        return list->next;
    }
    if(k>=length){
        temp = init_linkList();
        while(temp){
            temp =  oldNode->next;
            oldNode->next = newNode;
            newNode = oldNode;
            oldNode = temp;
        }
        list->next->next=NULL;
        return newNode;

    }
    if(k<length){
        while(i<length){
            cnt=i+1;
            i = i+k;
            while(cnt<i){
                temp = oldNode->next;
                oldNode->next = newNode;
                newNode = oldNode;
                oldNode = temp;
                cnt++;

            }
            newNode ->next = temp;
            newNode = oldNode;
            oldNode = temp;

        }
        return newNode;
    }


}

int main(){
    pList head = init_linkList();
    pList rear=head;
    insert(&rear,1);
    insert(&rear,2);
    insert(&rear,3);
    insert(&rear,4);
    insert(&rear,5);
    insert(&rear,6);
    toSring(head);
    pList list = reverse(head,3,getListLength(head));
    head->next = list;
    toSring(head);
    return 0;
}
