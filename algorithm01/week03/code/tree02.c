#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXSIZE 10
//#define ElementType char
#define Tree int
#define Null -1

/*判断两个树是否同构，左右还在颠倒算是同构*/

/*定义树的数据结构，这里的树的数据结构如下所示：
index   element     leftChildIndex      rightChildIndex
0       G           -                   4
1       B           7                   6
2       F           -                   -
3       A           5                   1
4       H           -                   -
5       C           0                   -
6       D           -                   -
7       E           2                   -

-:indicate the child is null
a index that has not been used in the leftChildIndex and rightChildIndex indicates
it is the root, for example  3(A).
So we using following data constructor to stotre the type binary tree who is s static link table
*/

typedef char ElementType;
typedef struct treeNode{
    ElementType element;
    Tree left;
    Tree right;
}tree;
tree t1[MAXSIZE],t2[MAXSIZE];


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
            scanf("%c %c %c",&t[i].element,&left,&right);
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

/*
Tree bulidTree(tree T[])
{
    int N, check[MAXSIZE], root = Null;    //root = Null 空树则返回Null
    char cl, cr;        //左右孩子序号
    scanf("%d\n",&N);
    if(N) {
        for(int i = 0; i < N; i++)
            check[i] = 0;
        for(int i = 0; i < N; i++) {
            scanf("%c %c %c\n",&T[i].element,&cl,&cr);
            //找root
            if(cl != '-') {
                T[i].left = cl - '0';
                check[T[i].left] = 1;    //不是根节点
            }else {
                T[i].left = Null;
            }
            if(cr != '-') {
                T[i].right = cr - '0';
                check[T[i].right] = 1;    //不是根节点
            }else {
                T[i].right = Null;
            }
        }

        for(int i = 0; i < N; i++)        //check[]=0的为根节点
            if(!check[i]) {
                root = i;
                break;
            }
    }
    return root;
}
*/

int isomorphic(Tree r1,Tree r2){
    if(r1==Null && r2==Null){
        return 1;
    }
    if((r1==Null && r2!=Null) || (r1!=Null && r2==Null)){
        return 0;
    }

    if(t1[r1].element != t2[r2].element){
        return 0;
    }
    if((t1[r1].left==Null) && (t2[r2].left==Null)){
        return isomorphic(t1[r1].right,t2[r2].right);
    }

    if((t1[r1].left!=Null) && (t2[r2].left!=Null) &&((t1[t1[r1].left].element) == (t2[t2[r2].left].element))){
        return (isomorphic(t1[r1].left,t2[r2].left) && isomorphic(t1[r1].right,t2[r2].right));
    }else{
        return (isomorphic(t1[r1].left,t2[r2].right) && isomorphic(t1[r1].right,t2[r2].left));
    }

}


int main(){
    Tree r1,r2;
    r1 =buildTree(t1);
    r2 = buildTree(t2);
    if(isomorphic(r1,r2)){
        printf("Yes\n");
    }else{
        printf("No\n");
    }
    return 0;
}
