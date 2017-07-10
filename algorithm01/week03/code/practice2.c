#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAXSIZE 100
//#define ElementType char
#define Tree int
#define Null -1


typedef int ElementType;
typedef struct treeNode{
    ElementType element;
    Tree left;
    Tree right;
}tree;
tree t1[MAXSIZE];

typedef tree dataType;

//定义存放队列元素(二叉树)的链表
typedef struct node4{
    dataType element;
    struct node4 *next;
}lis,*pList;

//定义队列的链式存储
typedef struct node5{
    struct node4 *font;//指向队列的头指针
    struct node4 *rear;//指向队列尾的尾指针
}que,*pQueue;

pList createEmptyList(){
    pList list = (pList)malloc(sizeof(lis));
    if(list){
        list->next=NULL;
    }
    return list;
}

pQueue createEmptyQueue(){
    pQueue queue = (pQueue)malloc(sizeof(que));
    if(queue){
        queue->font=NULL;
        queue->rear=NULL;
    }
}

int isQueueEmpty(pQueue queue){
    return (queue->font==NULL);
}


void addQueue(pQueue queue,dataType element){
    if(isQueueEmpty(queue)){
        pList list = createEmptyList();
        list->element=element;
        queue->font=list;
        queue->rear=list;
    }else{
        pList list = (pList)malloc(sizeof(lis));
        list->element=element;
        list->next = queue->rear->next;
        queue->rear->next=list;
        queue->rear=list;
    }
}

dataType deleteQueue(pQueue queue){
    if(isQueueEmpty(queue)){
        return;
    }
    dataType element = queue->font->element;
    if(queue->font==queue->rear){
        queue->font=queue->rear=NULL;
    }else{
        queue->font = queue->font->next;
    }
    return element;
}





Tree buildTree(tree t[]){
    int i,n;
    ElementType element;
    Tree root=Null;
    int check[MAXSIZE];
    char left,right;
    scanf("%d",&n);
    getchar();
    //printf("n:%d\n",n);
    if(n){
        /*定义检查数组，如果left 和right出现角标i,就把check[i]=1,表示该元素已经被指向
            最后check[root]=0,root就是根元素
        */
        for(i=0;i<n;i++){
            check[i]=0;
        }
        for(i=0;i<n;i++){
            t[i].element=i;
            scanf("%c %c",&left,&right);
            getchar();
            //printf("element:%c left:%c right:%c\n",t[i].element,left,right);
            if(left!='-'){
                t[i].left=left-'0';
                check[t[i].left]=1;
            }else{
                t[i].left=Null;
            }

            //printf("element %c,left %c rigt:%c",t[i].element,left,right);
            if(right!='-'){
                t[i].right=right-'0';
                check[t[i].right]=1;
            //printf("n:%d\n",n);
            }else{
                t[i].right=Null;
            }
        }
        for(i=0;i<n;i++){
            if(!check[i]){
                root =i;
                break;
            }
        }
    }
    return  root;
}

pQueue getLeafNode(Tree root){
    tree temp;
    pQueue queue = createEmptyQueue();
    pQueue list = createEmptyQueue();
    if(root!=Null){
        addQueue(queue,t1[root]);
    }else{
        return NULL;
    }
    while(!isQueueEmpty(queue)){
        temp = deleteQueue(queue);
        if((temp.left==Null) && (temp.right==Null)){
            addQueue(list,temp);
        }
        if(temp.left!=Null){
            addQueue(queue,t1[temp.left]);
        }
        if(temp.right!=Null){
            addQueue(queue,t1[temp.right]);
        }
    }
    return list;
}

int main(){
    Tree root = buildTree(t1);
    pQueue queue = getLeafNode(root);
    while(!isQueueEmpty(queue)){
        tree temp = deleteQueue(queue);

        if(queue->font==NULL){
            printf("%d",temp.element);
        }else{
            printf("%d ",temp.element);
        }
    }
    return 0;
}
