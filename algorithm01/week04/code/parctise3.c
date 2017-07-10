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

void PreorderTraversal( BinTree BT ); /* ����������ɲ���ʵ�֣�ϸ�ڲ��� */
void InorderTraversal( BinTree BT );  /* ����������ɲ���ʵ�֣�ϸ�ڲ��� */

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
/*�����������Ĳ��룬֪ʶ��ѭ���������������ʣ����ǲ�û�е���ƽ��*/
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


/*�����������ĵݹ����*/
BinTree Find(BinTree tree,ElementType element){
    if(!tree){
        return NULL;
    }
    if(element<tree->Data){
        /*����Ԫ�رȸ�Ԫ��С���������в���*/
        return  find(element,tree->Left);
    }else if(element>tree->Data){
        /*����Ԫ�رȸ�Ԫ��С���������в���*/
        return find(element,tree->Right);
    }else{/*�ҵ��ýڵ㣬����*/
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
    }else{//�ҵ���Ҫɾ����Ԫ�ؽڵ�
        if(tree->Left && tree->Right){//�����������ӽڵ�
            temp = getMinElement(tree->Right);/*��ȡ����������Сֵ�ڵ�*/
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


/*���ݶ������������ص㣬��СԪ��������ߵĽڵ�����*/
BinTree FindMin(BinTree tree){
    if(tree){
         while(tree->Left){
            tree=tree->Left;
         }
    }

    return tree;
}

/*��ȡ�����������е����Ԫ�أ����Ԫ�ص�λ��Ӧ�������ұߵĽڵ���*/
BinTree FindMax(BinTree tree){
    if(tree){
        while(tree->Right){
            tree = tree->Right;
        }
    }

    return tree;
}

