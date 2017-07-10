#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct TNode *Position;
typedef Position BinTree;
struct TNode{
    ElementType Data;
    BinTree Left;
    BinTree Right;
};

void PreorderTraversal( BinTree BT ); /* 先序遍历，由裁判实现，细节不表 */
void InorderTraversal( BinTree BT );  /* 中序遍历，由裁判实现，细节不表 */

BinTree Insert( BinTree BST, ElementType X );
BinTree Delete( BinTree BST, ElementType X );
Position Find( BinTree BST, ElementType X );
Position FindMin( BinTree BST );
Position FindMax( BinTree BST );

int main()
{
    BinTree BST, MinP, MaxP, Tmp;
    ElementType X;
    int N, i;

    BST = NULL;
    scanf("%d", &N);
    for ( i=0; i<N; i++ ) {
        scanf("%d", &X);
        BST = Insert(BST, X);
    }
    printf("Preorder:"); PreorderTraversal(BST); printf("\n");
    MinP = FindMin(BST);
    MaxP = FindMax(BST);
    scanf("%d", &N);
    for( i=0; i<N; i++ ) {
        scanf("%d", &X);
        Tmp = Find(BST, X);
        if (Tmp == NULL) printf("%d is not found\n", X);
        else {
            printf("%d is found\n", Tmp->Data);
            if (Tmp==MinP) printf("%d is the smallest key\n", Tmp->Data);
            if (Tmp==MaxP) printf("%d is the largest key\n", Tmp->Data);
        }
    }
    scanf("%d", &N);
    for( i=0; i<N; i++ ) {
        scanf("%d", &X);
        BST = Delete(BST, X);
    }
    printf("Inorder:"); InorderTraversal(BST); printf("\n");

    return 0;
}
/*二叉搜索树的插入，知识遵循二叉搜索树的性质，但是并没有调节平衡*/
BinTree Insert(BinTree tree,ElementType element){
    BinTree temp;
    if(!tree){
        tree = (BinTree)malloc(sizeof(struct TNode));
        tree->Data=element;
        tree->Left=tree->Right=NULL;
    }else{/**/
        if(element<tree->Data){
            tree ->Left = insert(tree->Left,element);
        }
        else if(element>tree->Data){
            tree->Right = insert(tree->Right,element);
        }
    }
    return tree;
}


/*二叉搜索树的递归查找*/
BinTree Find(BinTree tree,ElementType element){
    if(!tree){
        return NULL;
    }
    if(element<tree->Data){
        /*查找元素比根元素小在左子树中查找*/
        return  find(element,tree->Left);
    }else if(element>tree->Data){
        /*查找元素比根元素小在右子树中查找*/
        return find(element,tree->Right);
    }else{/*找到该节点，返回*/
        return tree;
    }
}

BinTree Delete(BinTree tree,ElementType element){
    BinTree temp;
    if(!tree){
        printf("the element don't search in this tree\n");
    }else if(element<tree->Data){
        tree->Left=deleteElement(tree->Left,element);
    }else if(element>tree->Data){
        tree->Right = deleteElement(tree->Right,element);
    }else{//找到需要删除的元素节点
        if(tree->Left && tree->Right){//该有两个孩子节点
            temp = getMinElement(tree->Right);/*获取右子树的最小值节点*/
            tree->Data=temp->Data;
            tree->Right=deleteElement(tree->Right,temp->Data);
        }else{
            temp=tree;
            if(!tree->Left){
                tree=tree->Right;
            }else if(!tree->Right){
                tree=tree->Left;
            }
            free(temp);
        }
    }
    return tree;
}


/*根据二叉搜索树的特点，最小元素在最左边的节点上面*/
BinTree FindMin(BinTree tree){
    if(tree){
         while(tree->Left){
            tree=tree->Left;
         }
    }

    return tree;
}

/*获取二叉搜索树中的最大元素，最大元素的位置应该在最右边的节点上*/
BinTree FindMax(BinTree tree){
    if(tree){
        while(tree->Right){
            tree = tree->Right;
        }
    }

    return tree;
}

