#include<stdio.h>
#include<stdlib.h>

typedef int elementType;

/*define a binary tree*/
typedef struct node{
    elementType element;
    struct node *left;
    struct node *right;
    int treeHeight;/*Ϊ��ƽ����������㷽�㣬��������*/
}tre,*pTree;

/*=====================================������Ϊƽ�������===============================================*/

int getMaxValue(int a,int b){
    return a > b ? a : b ;
}

/*��ȡ������������*/
int getHeight(pTree tree){
    int leftHeight,rightHeight;
    if(tree){
        leftHeight = getHeight(tree->left);
        rightHeight = getHeight(tree->right);
        return (leftHeight>rightHeight ? leftHeight : rightHeight)+1;
    }
    return 0;
}
/*
������������A��B����LL��ת��������A��B���¸߶ȣ������µĸ��ڵ�B
A������һ�����ӽڵ�B
*/
pTree singleLeftRatation(pTree A){
    pTree B = A->left;
    A->left=B->right;
    B->right = A;
    A->treeHeight = getMaxValue(getHeight(A->left),getHeight(A->right))+1;
    B->treeHeight = getMaxValue(getHeight(B->left),A->treeHeight)+1;
    return B;
}

/*�ҵ���:��A��B����RR��ת��������A��B�ĸ߶�,�����µĸ��ڵ�B
ע��A������һ���ҽڵ�B
*/
pTree singleRightRatation(pTree A){
    pTree B = A->right;
    A->right = B->left;
    B->left = A;
    A->treeHeight = getMaxValue(getHeight(A->left),getHeight(A->right))+1;
    B->treeHeight = getMaxValue(getHeight(B->right),A->treeHeight);
    return B;
}

/*
��A��LR��ת�������µĸ��ڵ�C
A������һ�����Լ���B��B������һ�����ӽڵ�C
*/
pTree doubleLeftRightRatation(pTree A){
    /*�ȶ�B��C����RR��ת,C������*/
    A->left = singleRightRatation(A->left);
    /*�ڶ�A��C����LL��ת�������µĸ��ڵ�C*/
    return singleLeftRatation(A);
}

/*
��A����RL��ת�������µĸ��ڵ�C
ע��A������һ�����ӽڵ�B��B������һ�����ӽڵ�C
*/
pTree doubleRightLeftRatation(pTree A){
    /*�ȶ�B��C����LL��ת,�����µĸ��ڵ�C*/
    A->right = singleLeftRatation(A->right);
    /*�ڶ�A��C����RR��ת�������µĸ��ڵ�C*/
    return singleRightRatation(A);
}

/*�Զ������������в��룬������������ƽ��*/
pTree AVLInsert(pTree tree,elementType element){
    if(!tree){
        tree = (pTree)malloc(sizeof(tre));
        tree->element = element;
        tree->left=tree->right = NULL;
        tree->treeHeight=0;
    }else if(element<tree->element){
        tree->left = AVLInsert(tree->left,element);
        //�ж�ƽ�������Ƿ����2
        if(getHeight(tree->left)-getHeight(tree->right) == 2){
            if(element<tree->left->element){//element��tree�������������������뵼��ƽ�����Ӵ���2������LL������
                tree = singleLeftRatation(tree);
            }else{//element��tree�������������������뵼��ƽ�����Ӵ���2������LR����
                tree = doubleLeftRightRatation(tree);
            }
        }
    }else if(element>tree->element){
        tree->right = AVLInsert(tree->right,element);
        //�ж�ƽ�������Ƿ����2
        if(getHeight(tree->right)-getHeight(tree->left) == 2){
            if(element>tree->right->element){//element��tree�������������������뵼��ƽ�����Ӵ���2������RR����
                tree = singleRightRatation(tree);
            }else{//element��tree�������������������뵼��ƽ�����Ӵ���2������RL����
                tree = doubleRightLeftRatation(tree);
            }
        }
    }/* else ����ҵ��ˣ��Ͳ����в���*/

    tree->treeHeight = getMaxValue(getHeight(tree->left),(getHeight(tree->right)))+1;
    return tree;
}


int main(){
    int N,i,element;
    scanf("%d",&N);
    pTree AVLTree=NULL;
    for(i=0;i<N;i++){
        scanf("%d",&element);
        AVLTree=AVLInsert(AVLTree,element);
    }
    printf("%d",AVLTree->element);
    return 0;
}

