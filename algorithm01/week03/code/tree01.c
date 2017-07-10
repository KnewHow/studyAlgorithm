#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>

//define binary tree element type
typedef char elementType;

//define binary tree
typedef struct node{
    elementType element;
    struct node *left;
    struct node *right;
    int flag;//Ϊ�˽��зǵݹ�ĺ��������������ջ��־λ��0��ʾ��һ��ѹջ����ջ��1��ʾ�ڶ���ѹջ����ջ
}bTree,*pBinTree;


//define the stack element type
typedef pBinTree dataType;


//define a stack to store binary tyoe
typedef struct node2{
    dataType element;
    struct node2 *next;
}sta,*pStack;


/*=======================����ջ�Ĳ���==============================*/
pStack createEmptyStack(){
    pStack stack = (pStack)malloc(sizeof(sta));
    if(stack){
        stack->next=NULL;
    }
}

int isStackEmpty(pStack stack){
    return(stack->next==NULL);
}

void push(pStack stack,dataType element){
    pStack newNode = (pStack)malloc(sizeof(sta));
    newNode->element = element;
    newNode->next = stack->next;
    stack->next = newNode;
}

dataType pop(pStack stack){
    if(isStackEmpty(stack)){
        printf("the stack has been empty\n");
        return NULL;
    }
    pStack temp = stack->next;
    stack->next = temp->next;
    return temp->element;
}

int getStackSize(pStack stack){
    pStack p = stack->next;
    int size=0;
    while(p){
        size++;
        p=p->next;
    }
    return size;
}



dataType getTop(pStack stack){
    if(isStackEmpty(stack)){
        printf("the stack has been empty\n");
        return NULL;
    }
    return (stack->next->element);
}

//����һ���ַ���ջ
typedef struct node3{
    elementType element;
    struct node3 *next;
}charSta,*pCharStack;

/*====================================���ַ�ջ�Ĳ���========================================*/
pCharStack createEmptyCharStack(){
    pCharStack stack = (pCharStack)malloc(sizeof(charSta));
    if(stack){
        stack->next=NULL;
    }
    return stack;
}

int isCharStackEmpty(pCharStack stack){
    return(stack->next==NULL);
}

void pushCharStack(pCharStack stack,char ch){
    pCharStack newNode = (pCharStack)malloc(sizeof(charSta));
    newNode->element = ch;
    newNode->next = stack->next;
    stack->next=newNode;
}


elementType popCharStack(pCharStack stack){
    if(isCharStackEmpty(stack)){
        return;
    }
    pCharStack temp=stack->next;
    stack->next=temp->next;
    return temp->element;
}

/*============================Ϊ�˶Զ��������в�α���������һ����ʽ���д�Ŷ�����=================================*/

//�����Ŷ���Ԫ��(������)������
typedef struct node4{
    dataType element;
    struct node4 *next;
}lis,*pList;

//������е���ʽ�洢
typedef struct node5{
    struct node4 *font;//ָ����е�ͷָ��
    struct node4 *rear;//ָ�����β��βָ��
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


/*==========================�������Ĺ���ͱ���==================================*/
/*
����һ�ö�������
sΪ�洢��������Ԫ�ص��ַ����飬sΪ����A(B,C(D,E))��ʽ���ַ���
treeΪ�����������õĸ��ڵ㣬����Ԫ��Ϊ��
*/
pBinTree createBinTree(char *s){
    int i,isRight;
    pStack treeStack = createEmptyStack();//��Žڵ�
    pCharStack charStack = createEmptyCharStack();//��ŷָ���
    pBinTree root = (pBinTree)malloc(sizeof(bTree));
    pBinTree temp,p;
    root->element=s[0];
    root->left=NULL;
    root->right=NULL;
    push(treeStack,root);
    i=1;
    while(i<strlen(s)){
        if(s[i]=='('){
            pushCharStack(charStack,s[i]);
            isRight=0;
        }else if(s[i]==','){
            isRight=1;
        }else if(s[i]==')'){
            pop(treeStack);
            popCharStack(charStack);
        }else if(isalpha(s[i])){
            p=(pBinTree)malloc(sizeof(bTree));
            p->element=s[i];
            p->left=NULL;
            p->right=NULL;
            temp=getTop(treeStack);
            //printf("%c %c\n",s[i],s[i+1]);
            if(isRight==1){
                temp->right=p;
            }else{
                temp->left=p;
            }

            if(s[i+1]=='('){
                push(treeStack,p);
            }
        }
        i++;
    }
    return root;
}

//�������
void preOrderTraversal(pBinTree tree){
    if(tree){
        printf("%c ",tree->element);
        preOrderTraversal(tree->left);
        preOrderTraversal(tree->right);
    }
}

//��������ķǵݹ鷽��
void preOrderTraversalStack(pBinTree tree){
    pBinTree t = tree;
    pStack stack = createEmptyStack();
    while(t || !isStackEmpty(stack)){
        while(t){
            printf("%c ",t->element);
            push(stack,t);
            t = t->left;
        }

        if(!isStackEmpty(stack)){
            t = pop(stack);
            t = t->right;
        }

    }

}
//�������
void middlerOrderTraversal(pBinTree tree){
    if(tree){
        middlerOrderTraversal(tree->left);
        printf("%c ",tree->element);
        middlerOrderTraversal(tree->right);
    }
}

//��������ķǵݹ鷽��
void middlerOrderTraversalStack(pBinTree tree){
    pStack stack = createEmptyStack();
    pBinTree t =tree;;
    while(!isStackEmpty(stack) || t){
        while(t){
            push(stack,t);
            t=t->left;
        }
        if(!isStackEmpty(stack)){
            t = pop(stack);
            printf("%c ",t->element);
            t = t->right;
        }
    }

}

//�������
void postOrderTraversal(pBinTree tree){
    if(tree){
        postOrderTraversal(tree->left);
        postOrderTraversal(tree->right);
        printf("%c ",tree->element);
    }
}

//��������ķǵݹ鷽��
void postOrderTraversalStack(pBinTree tree){
    pBinTree t = tree;
    pStack stack = createEmptyStack();
    while(t || !isStackEmpty(stack)){
        while(t){
            t->flag=0;
            push(stack,t);
            t=t->left;
        }
        if(!isStackEmpty(stack)){
            t = pop(stack);
            if(t->flag==0){
                t->flag=1;
                push(stack,t);
                t=t->right;
            }else{
                printf("%c ",t->element);
                t=NULL;
            }
        }
    }
}

/*�������Ĳ�α���*/
void levelOrderTraversal(pBinTree tree){
    pQueue queue = createEmptyQueue();
    pBinTree tr = tree;
    if(!tree){
        return;
    }
    addQueue(queue,tr);
    while(!isQueueEmpty(queue)){
        tr = deleteQueue(queue);
        printf("%c ",tr->element);
        if(tr->left){
            addQueue(queue,tr->left);
        }
        if(tr->right){
            addQueue(queue,tr->right);
        }
    }
}

/*Application of binary tree teaversal*/

//get the mount of leaf node,we just need add condition at preOrderTraversal
int getMountOfLeaves(pBinTree tree){
    pStack stack = createEmptyStack();
    pBinTree tr =tree;
    int mount=0;
    while(tr || !isStackEmpty(stack)){
        while(tr){
            if(tr->left==NULL && tr->right==NULL){
                mount++;
            }
            push(stack,tr);
            tr=tr->left;
        }
        if(!isStackEmpty(stack)){
            tr = pop(stack);
            tr=tr->right;
        }
    }
    return mount;
}

/*get the height of  binary tree, the hight of binary is max(subLeftTree,subRightTree)*/
int getHeigthOfBinaryTree(pBinTree tree){
    int hl,hr,maxH;
    if(tree){
        hl=getHeigthOfBinaryTree(tree->left);
        hr=getHeigthOfBinaryTree(tree->right);
        maxH=(hl>hr)?hl:hr;
        return maxH+1;
    }
    return 0;
}

//�ǵݹ�ķ�����ȡ�������ĸ߶ȣ���ʵ�������ĸ߶Ⱦ���ջ��Ԫ�ص����ֵ
int getHeigthOfBinaryTreeStack(pBinTree tree){
    pBinTree t = tree;
    int hMax=0,stackSize;
    pStack stack = createEmptyStack();
    while(t || !isStackEmpty(stack)){
        while(t){
            t->flag=0;
            push(stack,t);
            t=t->left;
        }
        if(!isStackEmpty(stack)){
            t = pop(stack);
            if(t->flag==0){
                t->flag=1;
                push(stack,t);
                t=t->right;
            }else{
                /*�����Ѿ���ջһ��Ԫ�أ����ջ������ӦΪ getSize+1*/
                stackSize=getStackSize(stack)+1;
                //printf("stackSize %d",stackSize);
                if(stackSize>hMax){
                    hMax=stackSize;
                }
                t=NULL;
            }
        }
    }
    return hMax;
}



void main(){
    char s[]="A(B(D,F(E)),C(G(,H),I))";
    //char s[]="A(B,C)";
    pBinTree root =createBinTree(s);
    printf("preOrderTraversal\n");
    preOrderTraversal(root);
    printf("\nPreOrderTraversalStack\n");
    preOrderTraversalStack(root);

    printf("\n\n================================\n");

    printf("\nmiddleOrderTraversal\n");
    middlerOrderTraversal(root);
    printf("\nmiddleOrderTraversalStack\n");
    middlerOrderTraversalStack(root);

    printf("\n\n================================\n");

    printf("\npostOrderTraversal\n");
    postOrderTraversal(root);
    printf("\npostOrderTraversalStack\n");
    postOrderTraversalStack(root);

    printf("\n\n================================\n");


    printf("\nThe level order traversal\n");
    levelOrderTraversal(root);

    printf("\n\n=========the application of binary tree traversal===========\n");
    int leavesMount = getMountOfLeaves(root);
    printf("\nnumber one:get the leaves mount:%d\n",leavesMount);

    int maxHeight = getHeigthOfBinaryTreeStack(root);
    printf("\nnuber two:get height of the binary tree:%d",maxHeight);

}
