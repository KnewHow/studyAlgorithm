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

/*二叉搜索树的递归查找*/
pTree find(elementType element,pTree tree){
    if(!tree){
        return NULL;
    }
    if(element<tree->element){
        /*查找元素比根元素小在左子树中查找*/
        return  find(element,tree->left);
    }else if(element>tree->element){
        /*查找元素比根元素小在右子树中查找*/
        return find(element,tree->right);
    }else{/*找到该节点，返回*/
        return tree;
    }
}

/*因为递归方法执行的效率低，而且上面的尾递归函数可以改写为递归函数*/
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

/*根据二叉搜索树的特点，最小元素在最左边的节点上面*/
pTree getMinElement(pTree tree){
    if(tree){
         while(tree->left){
            tree=tree->left;
         }
    }

    return tree;
}

/*获取二叉搜索树中的最大元素，最大元素的位置应该在最右边的节点上*/
pTree getMaxElement(pTree tree){
    if(tree){
        while(tree->right){
            tree = tree->right;
        }
    }

    return tree;
}


/*根据二叉搜索树的特点，最小元素在最左边的节点上面*/
pTree getMinElement(pTree tree){
    if(tree){
         while(tree->left){
            tree=tree->left;
         }
    }

    return tree;
}

/*获取二叉搜索树中的最大元素，最大元素的位置应该在最右边的节点上*/
pTree getMaxElement(pTree tree){
    if(tree){
        while(tree->right){
            tree = tree->right;
        }
    }

    return tree;
}

/*二叉搜索树的插入，知识遵循二叉搜索树的性质，但是并没有调节平衡*/
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

/*非递归的二叉搜索树的算法*/
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

/*在二叉搜索树中删除一个元素
    算法思想：
        1.首先查找到该元素
        2.如果该元素是叶子节点，直接删除
        3.如果该元素有一个孩子节点，直接把孩子节点挂载到该节点的父节点上
        4.如果该节点有两个孩子，由两种方法
            a.在该节点的左子树中找到最大元素节点T，把该节点的值替换成T的值，然后执行对T的删除操作
            b.在该节点的右子树中找最小元素的节点T，把该节点的值替换为T的值，然后执行对T的删除操作
        注：找最大或者最小元素是因为最大最小元素是叶子节点或者只有一个孩子。
*/
pTree deleteElement(pTree tree,elementType element){
    pTree temp;
    if(!tree){
        printf("the element don't search in this tree\n");
    }else if(element<tree->element){
        tree->left=deleteElement(tree->left,element);
    }else if(element>tree->element){
        tree->right = deleteElement(tree->right,element);
    }else{//找到需要删除的元素节点
        if(tree->left && tree->right){//该有两个孩子节点
            temp = getMinElement(tree->right);/*获取右子树的最小值节点*/
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

/*使用非递归的方法
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


//先序遍历
void preOrderTraversal(pTree tree){
    if(tree){
        printf("%d ",tree->element);
        preOrderTraversal(tree->left);
        preOrderTraversal(tree->right);
    }
}

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
    B->treeHeight = getMaxValue(B->left,A->treeHeight)+1;
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


void main(){
    printf("\n==========普通插入=====================================\n");
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

    printf("\n==========AVL插入=====================================\n");

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
