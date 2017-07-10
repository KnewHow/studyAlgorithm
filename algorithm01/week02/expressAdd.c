#include<stdio.h>
#include<stdlib.h>
/*使用链表实习多项式的加法运算*/
typedef struct linkList{
    int xiShu;
    int ciShu;
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

int insert(pList *rear,int xiShu,int ciShu){
    if((*rear)==NULL){
       printf("head node is null,don't allow insert element\n");
       return 0;
    }else{
        pList newNode = (pList)malloc(sizeof(list));
        newNode->xiShu=xiShu;
        newNode->ciShu=ciShu;
        newNode->next = (*rear)->next;
        (*rear)->next = newNode;
        *rear = newNode;
        return 1;
    }
}


void toString(pList list){
    pList p = list->next;
    printf("\ntoString:");
    while(p!=NULL){
        printf("%dx^%d ",p->xiShu,p->ciShu);
        p=p->next;
    }
    printf("\n");
}

void print(pList list){
    pList p = list->next;
    int flag=0;
    if(!list){
        print("0 0\n");
        return;
    }
    while(p!=NULL){
        if(!flag){
            flag=1;
        }else{
            printf(" ");
        }
        printf("%d %d",p->xiShu,p->ciShu);
        p=p->next;
    }
    printf("\n");
}

int compare(pList p1,pList p2){
    if(p1->ciShu>p2->ciShu){
        return 1;
    }else if(p1->ciShu<p2->ciShu){
        return -1;
    }else{
        return 0;
    }
}

void attach(int xiShu,int ciShu,pList *rear){
    pList p = (pList)malloc(sizeof(list));
    p->ciShu=ciShu;
    p->xiShu=xiShu;
    p->next=(*rear)->next;
    (*rear)->next=p;
    (*rear)=p;
}



pList polyAdd(pList list1,pList list2){
    int sum;
    pList rear = init_linkList();
    pList font = rear;
    pList p1 =list1->next;
    pList p2 = list2->next;
    while(p1 && p2){
        switch(compare(p1,p2)){
            case 1:
                attach(p1->xiShu,p1->ciShu,&rear);
                p1=p1->next;
                break;

            case -1:
                attach(p2->xiShu,p2->ciShu,&rear);
                p2 = p2->next;
                break;
            case 0:
                sum = p1->xiShu+p2->xiShu;
                if(sum){
                    attach(sum,p1->ciShu,&rear);
                }
                p1 = p1->next;
                p2 = p2->next;
                break;
        }

    }

    for(;p1;p1=p1->next){
        attach(p1->xiShu,p1->ciShu,&rear);
    }

    for(;p2;p2=p2->next){
        attach(p2->xiShu,p2->ciShu,&rear);
    }
    rear->next=NULL;
    return font;
}

pList mult(pList p1,pList p2){
    pList p,rear,t1,t2,t;
    int c,e;
    if(!p1 || !p2){
        return NULL;
    }
    t1=p1;
    t2=p2;
    p = (pList)malloc(sizeof(list));
    p->next = NULL;
    rear =p;
    while(t2){//先用p1的第一项乘以p2,得到p
        attach(t1->xiShu*t2->xiShu,t1->ciShu+t2->ciShu,&rear);
        t2 = t2->next;
    }
    t1=t1->next;
    while(t1){
        t2=p2;
        rear=p;
        while(t2){
            e=t1->ciShu+t2->ciShu;
            c=t1->xiShu*t2->xiShu;
            while(rear->next && rear->next->ciShu>e){
                rear=rear->next;
            }
            if(rear->next && rear->next->ciShu==e){
                if(rear->next->xiShu+c){
                    rear->next->xiShu+=c;
                }else{
                    t=rear->next;
                    rear->next = t->next;
                    free(t);
                }
            }else{
                t = (pList)malloc(sizeof(list));
                t->ciShu=e;
                t->xiShu=c;
                t->next=rear->next;
                rear->next=t;
                rear=rear->next;
            }
            t2 = t2->next;
        }
        t1=t1->next;
    }

    return p;
}

pList readLine(){
    int n,i,xiShu,ciShu;
    scanf("%d",&n);
    pList list = init_linkList();
    pList listRear = list;
    for(i=0;i<n;i++){
        scanf("%d %d",&xiShu,&ciShu);
        insert(&listRear,xiShu,ciShu);
    }

    return list;
}


void main(){
    /*
    pList list1 = init_linkList();
    pList list2 = init_linkList();
    pList list1Rear = list1;
    pList list2Rear = list2;
    insert(&list1Rear,3,4);
    insert(&list1Rear,-5,2);
    insert(&list1Rear,6,1);
    insert(&list1Rear,-2,0);
    //insert(&list1Rear,-1,0);

    insert(&list2Rear,5,20);
    insert(&list2Rear,-7,4);
    insert(&list2Rear,3,1);
    //insert(&list2Rear,1,1);
    //toString(list1);
    //toString(list2);
    */
    pList list1 = readLine();
    //toString(list1);
    pList list2 = readLine();
    pList result = polyAdd(list1,list2);
    pList p = mult(list1->next,list2->next);
    print(p);
    print(result);
}
