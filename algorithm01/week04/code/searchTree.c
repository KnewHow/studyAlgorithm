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

/*�����������ĵݹ����*/
pTree find(elementType element,pTree tree){
    if(!tree){
        return NULL;
    }
    if(element<tree->element){
        /*����Ԫ�رȸ�Ԫ��С���������в���*/
        return  find(element,tree->left);
    }else if(element>tree->element){
        /*����Ԫ�رȸ�Ԫ��С���������в���*/
        return find(element,tree->right);
    }else{/*�ҵ��ýڵ㣬����*/
        return tree;
    }
}

/*��Ϊ�ݹ鷽��ִ�е�Ч�ʵͣ����������β�ݹ麯�����Ը�дΪ�ݹ麯��*/
pTree find2(elementType element,pTree tree){
    pTree temp;
    temp = tree;
    while(temp){
        if(element<temp->element){
            temp=temp->left;
        }else if(element>temp->element){
            temp=temp->right;
        }else{
            return temp;
        }
    }
    return NULL;
}

/*���ݶ������������ص㣬��СԪ��������ߵĽڵ�����*/
pTree getMinElement(pTree tree){
    if(tree){
         while(tree->left){
            tree=tree->left;
         }
    }

    return tree;
}

/*��ȡ�����������е����Ԫ�أ����Ԫ�ص�λ��Ӧ�������ұߵĽڵ���*/
pTree getMaxElement(pTree tree){
    if(tree){
        while(tree->right){
            tree = tree->right;
        }
    }

    return tree;
}


/*���ݶ������������ص㣬��СԪ��������ߵĽڵ�����*/
pTree getMinElement(pTree tree){
    if(tree){
         while(tree->left){
            tree=tree->left;
         }
    }

    return tree;
}

/*��ȡ�����������е����Ԫ�أ����Ԫ�ص�λ��Ӧ�������ұߵĽڵ���*/
pTree getMaxElement(pTree tree){
    if(tree){
        while(tree->right){
            tree = tree->right;
        }
    }

    return tree;
}

/*�����������Ĳ��룬֪ʶ��ѭ���������������ʣ����ǲ�û�е���ƽ��*/
pTree insert(pTree tree,elementType element){
    pTree temp;
    if(!tree){
        tree = (pTree)malloc(sizeof(tre));
        tree->element=element;
        tree->left=tree->right=NULL;
    }else{/**/
        if(element<tree->element){
            tree ->left = insert(tree->left,element);
        }
        else if(element>tree->element){
            tree->right = insert(tree->right,element);
        }
    }
    return tree;
}

/*�ǵݹ�Ķ������������㷨*/
pTree insert2(pTree tree,elementType element){
    pTree temp;
    int flag;
    pTree parent;
    if(!tree){
        tree = (pTree)malloc(sizeof(tre));
        tree->element=element;
        tree->left=tree->right=NULL;
    }else{
        temp=tree;
        while(temp!=NULL){
            if(element<temp->element){
                //printf("lala\n");
                parent = temp;
                temp=temp->left;
                flag=0;
            }else if(element>temp->element){
                parent = temp;
                flag=1;
                temp=temp->right;
            }
        }

        temp = (pTree)malloc(sizeof(tre));
        temp->element=element;
        temp->left=temp->right=NULL;
        if(flag){
            parent->right=temp;
        }else{
            parent->left=temp;
        }
    }

    return tree;
}

/*�ڶ�����������ɾ��һ��Ԫ��
    �㷨˼�룺
        1.���Ȳ��ҵ���Ԫ��
        2.�����Ԫ����Ҷ�ӽڵ㣬ֱ��ɾ��
        3.�����Ԫ����һ�����ӽڵ㣬ֱ�ӰѺ��ӽڵ���ص��ýڵ�ĸ��ڵ���
        4.����ýڵ����������ӣ������ַ���
            a.�ڸýڵ�����������ҵ����Ԫ�ؽڵ�T���Ѹýڵ��ֵ�滻��T��ֵ��Ȼ��ִ�ж�T��ɾ������
            b.�ڸýڵ��������������СԪ�صĽڵ�T���Ѹýڵ��ֵ�滻ΪT��ֵ��Ȼ��ִ�ж�T��ɾ������
        ע������������СԪ������Ϊ�����СԪ����Ҷ�ӽڵ����ֻ��һ�����ӡ�
*/
pTree deleteElement(pTree tree,elementType element){
    pTree temp;
    if(!tree){
        printf("the element don't search in this tree\n");
    }else if(element<tree->element){
        tree->left=deleteElement(tree->left,element);
    }else if(element>tree->element){
        tree->right = deleteElement(tree->right,element);
    }else{//�ҵ���Ҫɾ����Ԫ�ؽڵ�
        if(tree->left && tree->right){//�����������ӽڵ�
            temp = getMinElement(tree->right);/*��ȡ����������Сֵ�ڵ�*/
            tree->element=temp->element;
            tree->right=deleteElement(tree->right,temp->element);
        }else{
            temp=tree;
            if(!tree->left){
                tree=tree->right;
            }else if(!tree->right){
                tree=tree->left;
            }
            free(temp);
        }
    }
    return tree;
}

/*ʹ�÷ǵݹ�ķ���
pTree deleteElement2(pTree tree,elementType element){
    pTree temp,maxSubNode,flag,temp2;
    if(!tree){
        printf("the tree is empty,don't allow delete elememt\n");
    }else{
       temp = find(element,tree);
       if(temp==NULL){
            printf("the element don't exsit in this tree\n");
       }else{
            if(temp->left && temp->right){
                maxSubNode = getMinElement(temp->right);
                temp->element = maxSubNode->element;
            }else{
                maxSubNode = temp;
            }

                temp2=maxSubNode;
                if(!maxSubNode->left){
                    maxSubNode=maxSubNode->right;
                }else if(!maxSubNode->right){
                    maxSubNode=maxSubNode->left;
                }
                free(temp2);
       }

    }
    return tree;
}*/


//�������
void preOrderTraversal(pTree tree){
    if(tree){
        printf("%d ",tree->element);
        preOrderTraversal(tree->left);
        preOrderTraversal(tree->right);
    }
}

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
    B->treeHeight = getMaxValue(B->left,A->treeHeight)+1;
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


void main(){
    printf("\n==========��ͨ����=====================================\n");
    int findElement=33;
    int deleteData=41;
    pTree tree=insert(NULL,30);
    tree=insert(tree,15);
    tree=insert(tree,41);
    tree=insert(tree,33);
    tree=insert(tree,50);
    tree=insert(tree,35);
    preOrderTraversal(tree);
    printf("\n");
    printf("The find element is:%d,the result is %d \n",findElement,find(findElement,tree)->element);
    printf("The min element:%d\n",getMinElement(tree)->element);
    printf("The max element:%d\n",getMaxElement(tree)->element);
    //printf("delete the elemet %d\n",deleteData);
    //deleteElement(tree,deleteData);
    printf("\nordinary tree preOrder\n");
    preOrderTraversal(tree);

    printf("\n==========AVL����=====================================\n");

    pTree AVLTree=AVLInsert(NULL,30);
    AVLTree=AVLInsert(AVLTree,15);
    AVLTree=AVLInsert(AVLTree,41);
    AVLTree=AVLInsert(AVLTree,33);
    AVLTree=AVLInsert(AVLTree,50);
    AVLTree=AVLInsert(AVLTree,35);
    printf("\n");
    printf("The find element is:%d,the result is %d \n",findElement,find(findElement,AVLTree)->element);
    printf("The min element:%d\n",getMinElement(AVLTree)->element);
    printf("The max element:%d\n",getMaxElement(AVLTree)->element);
    //printf("delete the elemet %d\n",deleteData);
    //deleteElement(AVLTree,deleteData);
     printf("\nAVL tree preOrder\n");
    preOrderTraversal(AVLTree);

}
