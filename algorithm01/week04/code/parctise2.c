#include<stdio.h>
#include<stdlib.h>

typedef int elementType;

/*define a binary tree*/
typedef struct node{
    elementType element;
    struct node *left;
    struct node *right;
    int treeHeight;/*为了平衡二叉树计算方便，定义树高*/
}tre,*pTree;

/*=====================================调整树为平衡二叉树===============================================*/

int getMaxValue(int a,int b){
    return a > b ? a : b ;
}

/*获取二叉树的树高*/
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
左单旋操作：将A与B进行LL旋转，并更新A和B的新高度，返回新的根节点B
A必须有一个左子节点B
*/
pTree singleLeftRatation(pTree A){
    pTree B = A->left;
    A->left=B->right;
    B->right = A;
    A->treeHeight = getMaxValue(getHeight(A->left),getHeight(A->right))+1;
    B->treeHeight = getMaxValue(getHeight(B->left),A->treeHeight)+1;
    return B;
}

/*右单旋:将A与B进行RR旋转，并更新A与B的高度,返回新的根节点B
注：A必须有一个右节点B
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
将A做LR旋转，返回新的根节点C
A必须有一个左自己的B，B必须有一个右子节点C
*/
pTree doubleLeftRightRatation(pTree A){
    /*先对B，C进行RR旋转,C被返回*/
    A->left = singleRightRatation(A->left);
    /*在对A和C进行LL旋转，返回新的根节点C*/
    return singleLeftRatation(A);
}

/*
对A进行RL旋转，返回新的根节点C
注：A必须有一个右子节点B，B必须有一个左子节点C
*/
pTree doubleRightLeftRatation(pTree A){
    /*先对B，C进行LL旋转,返回新的根节点C*/
    A->right = singleLeftRatation(A->right);
    /*在对A，C进行RR旋转，返回新的根节点C*/
    return singleRightRatation(A);
}

/*对二叉搜索树进行插入，插入后调整树的平衡*/
pTree AVLInsert(pTree tree,elementType element){
    if(!tree){
        tree = (pTree)malloc(sizeof(tre));
        tree->element = element;
        tree->left=tree->right = NULL;
        tree->treeHeight=0;
    }else if(element<tree->element){
        tree->left = AVLInsert(tree->left,element);
        //判断平衡因子是否等于2
        if(getHeight(tree->left)-getHeight(tree->right) == 2){
            if(element<tree->left->element){//element往tree的左子树的左子树插入导致平衡因子大于2，进行LL调整的
                tree = singleLeftRatation(tree);
            }else{//element往tree的左子树的右子树插入导致平衡因子大于2，进行LR调整
                tree = doubleLeftRightRatation(tree);
            }
        }
    }else if(element>tree->element){
        tree->right = AVLInsert(tree->right,element);
        //判断平衡因子是否等于2
        if(getHeight(tree->right)-getHeight(tree->left) == 2){
            if(element>tree->right->element){//element往tree的右子树的右子树插入导致平衡因子大于2，进行RR调整
                tree = singleRightRatation(tree);
            }else{//element往tree的右子树的左子树插入导致平衡因子大于2，进行RL调整
                tree = doubleRightLeftRatation(tree);
            }
        }
    }/* else 如果找到了，就不进行插入*/

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

