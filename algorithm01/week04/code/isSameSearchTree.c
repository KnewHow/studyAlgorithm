#include<stdio.h>
#include<stdlib.h>



/*
    需求：比较是否为相同的二叉搜索树
    我们知道的是：给定一个插入序列可以唯一的确定一棵二叉搜索树
    但是对于相同的一个二叉搜索树，不一定有同一个插入序列
    例如{2 3 1}和{2 1 3}就是相同的二叉搜索树

    输入要求：
    4 2     源二叉搜索树的节点个数N 有L个二叉搜索树需要和源二叉搜索进行比较
    3 1 4 2 源二叉搜索树
    3 4 1 2 需要进行比较的二叉搜索树
    3 2 4 1 被比较的二叉搜索树
    2 1     源二叉搜索树的节点个数 有几个二叉搜索树需要和源二叉搜索进行比较
    2 1     源二叉搜索树
    1 2     需要进行比较的二叉搜索树
    0       程序结束的标志

    输出
    ### 输出样例:
    Yes
    No
    No

    算法思路
    我们先使用源二叉树的节点建立一棵二叉搜索树
    然后在源二叉树中国对每个目的二叉树的每个元素进行查找

    如果每次搜索所经过的结点在前面均出现过，则一致
    否则（某次搜索中遇到前面未出现的结点），则不一致

    程序设计的思路：
    int main(){
        读入N和L
        建立源二叉树T
        比较T是否和L个二叉树一致，并打印结果
        return 0;
    }

    需要设计的主要函数
    1.读数据建树T
    2.判断一个序列是否和T构成相同的搜索树
*/

typedef int elementType;

/*define a binary tree*/
typedef struct node{
    elementType element;
    struct node *left;
    struct node *right;
    int flag;/*为了标记某个节点是以及被访问过 1表示以及被访问过了，0表示没有被访问过*/
}tre,*pTree;

/*构造二叉搜索树
@param N 二叉搜索树节点的个数
@return 返回一个二叉搜索树的根节点
*/
pTree buildTree(int N);

/*
把一个节点插入二叉搜索树中
@param tree 已经存在的二叉搜索树
@param element 需要插入到二叉搜索树的元素
*/
pTree insert(pTree tree,elementType element);

/*
创建一个树的节点
@param element 需要创建树节点的元素值
*/
pTree newNode(int element);

/*对二叉树进行先序遍历
@param tree 需要进行先序遍历的二叉树
*/
void preOrderTraversal(pTree tree);
/*
判断一棵二叉树是否和源二叉树一致
@param tree 源二叉搜索树
@param N 二叉搜索树的节点个数
@return 如果相同 返回1，否则返回0
*/
int judge(pTree tree,int N);

/*把二叉搜索树的flag标志全部置0
@param tree 需要把flag全部置0的二叉搜索树
*/
void  resetTree(pTree tree);

/*
检查该元素是否是按照源二叉树的顺序插入二叉树
在二叉树中搜索该元素，如果之前搜索到的元素flag都为1，当flag不为1时
正是element==tree->element.表示此节点为正确插入节点，否则就为错误插入节点
@param tree 源二叉搜索
@param element 需要检测的元素
@return 元素正确插入 返回1 否则返回0
*/
int check(pTree tree,elementType element);

/*释放tree
@param tree 需要被释放的tree
*/
void freeTree(pTree tree);
int main(){
    int N,L;
    int i;
    scanf("%d",&N);
    while(N){
        scanf("%d",&L);
        pTree tree = buildTree(N);
        //preOrderTraversal(tree);
        for(i=0;i<L;i++){
            if(judge(tree,N)){
                printf("Yes\n");
            }else{
                printf("No\n");
            }
            resetTree(tree);
        }
        /*释放已经判断过得二叉搜索树*/
        freeTree(tree);
        scanf("%d",&N);
    }
    return 0;
}

pTree newNode(int element){
    pTree tree = (pTree)malloc(sizeof(tre));
    tree->element = element;
    tree->left=tree->right = NULL;
    //设置初始的标记位都为0，没有被访问
    tree->flag=0;
    return tree;
}

pTree insert(pTree tree,elementType element){
    if(!tree){
        tree = newNode(element);
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


pTree buildTree(int N){
    int ele,i;
    pTree tree;
    scanf("%d",&ele);
    tree = newNode(ele);
    for(i=1;i<N;i++){
        scanf("%d",&ele);
        tree = insert(tree,ele);
    }
    return tree;
}

void preOrderTraversal(pTree tree){
    if(tree){
        printf("%d ",tree->element);
        preOrderTraversal(tree->left);
        preOrderTraversal(tree->right);
    }
}

int check(pTree tree,elementType element){
    if(tree->flag){
        if(element<tree->element){
            check(tree->left,element);
        }else if(element>tree->element){
            check(tree->right,element);
        }else{
            return 0;
        }
    }else{
        if(tree->element==element){
            tree->flag=1;
            return 1;
        }else{
            return 0;
        }
    }
}


int judge(pTree tree,int N){
    int elemen,i,flag=0;
    scanf("%d",&elemen);
    if(elemen!=tree->element){
        flag=1;
    }else{
        tree->flag=1;
    }
    for(i=1;i<N;i++){
        scanf("%d",&elemen);
        /*当已经判断出该二叉搜索树和源二叉搜索树不一致时，需要继续把数据读完，不然未读完的数据就会变成下一个树的元素*/
        if((!flag) && (!check(tree,elemen))){
            flag=1;
        }
    }
    if(flag){
        return 0;
    }else{
        return 1;
    }

}

void  resetTree(pTree tree){
    if(tree->left){
        resetTree(tree->left);
    }
    if(tree->right){
        resetTree(tree->right);
    }
    tree->flag=0;
}

void freeTree(pTree tree){
    if(tree->left){
        freeTree(tree->left);
    }
    if(tree->right){
        free(tree->right);
    }
    free(tree);
}
