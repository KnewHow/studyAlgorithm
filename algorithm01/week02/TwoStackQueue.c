#include<stdio.h>
#include<stdlib.h>

#define M 95
#define N 10

/*
讨论2.3 如何用两个堆栈模拟实现一个队列?
老师参与

我认为队列的最大长度为M+N,下面是我的算法思想。
1.入队列时，当小栈不满时，一直向小栈里面压入元素(入队)，
如果小栈满了但是大栈为空，那么就把小栈里面的元素分别弹栈并一一压入大栈里面。
如此以来，小栈就为空，大栈未满被(M>N),此时可以执行继续入队列(元素压入小栈)，或者出队列(元素从大栈弹栈)。
如果入队列(元素压入小栈)，则小栈会逐渐被放满。此时就有如下情况：
1.如果大栈为空，那么按照上面的方法，把小栈内元素分别弹栈并压入大栈

2.如果大栈中有元素，并且大栈的剩余空间R>N(小栈容量)，建立一个临时数组，先把大栈中的元素
全部弹栈并用数组保存，在把小栈的元素分别弹栈并一一压入大栈。在把临时数组中元素的按照出队列的顺序一一压入大栈中

3.如果大栈中有元素而且大栈的剩余空间R<N(小栈的容量)，那么此时我们的想法是把小栈中栈底的R个运算弹栈并压栈大栈中。
    首先用临时数组arr2保存小栈弹出的N-R个元素，在把大栈中的所有元素弹栈并放入一个临时数组中arr1中。
    把小栈中剩余的元素依次弹栈并压入大栈，再把临时数组arr1和临时数组arr2中的元素，按照之前的顺序压入大栈和小栈中、
    此时大栈已满，小栈还有N-R个元素可用。所有可用继续入队列(元素压入小栈)，直到小栈也满为止。

    根据上树的算法，队列的最大容量为大栈满且小栈满，即为M+N

下面是代码的具体实现：
*/


//构造长度较小的栈
typedef struct node1{
    int data[N];
    int top;
}smallerStack,*pSmallerStack;

//构造长度较大的栈
typedef struct node2{
    int data[M];
    int top;
}greaterStack,*pGreaterStack;


/*==============================对长度较小的栈的操作=======================================*/
pSmallerStack createSmallerStack(){
    pSmallerStack stack;
    stack = (pSmallerStack)malloc(sizeof(smallerStack));
    if(stack){
        stack->top=-1;
    }
    return stack;
}

int isSmallerStackFull(pSmallerStack stack){
    return stack->top== (N-1);
}

int isSmallerStackEmpty(pSmallerStack stack){
    return stack->top==-1;
}

void pushSmallerStack(pSmallerStack stack,int element){
    if(isSmallerStackFull(stack)){
        //printf("the smaller stack has been filled,don't allow push\n");
        return;
    }else{
        stack->data[++(stack->top)]=element;
    }
}

int popSmallerStack(pSmallerStack stack){
    if(isSmallerStackEmpty(stack)){
        //printf("the smaller stack is empty,don't pop\n");
    }else{
        return (stack->data[(stack->top)--]);
    }
}

//按照从top-->0 打印小栈元素
void toStringSmallerStack(pSmallerStack stack){
    int n = stack->top;
    printf("\ntoSmallerStackString:");
    if(n==-1){
        printf("the smaller stack is empty");
    }else{
        while(n>=0){
            printf("%d ",stack->data[n]);
            n--;
        }
    }
    printf("\n");

}




/*======================对长度较大的栈的操作===============================*/
pGreaterStack createGreaterStack(){
    pGreaterStack stack;
    stack = (pGreaterStack)malloc(sizeof(greaterStack));
    if(stack){
        stack->top=-1;
    }
    return stack;
}

int isGreaterStackFull(pGreaterStack stack){
    return stack->top== (M-1);
}

int isGreaterStackEmpty(pGreaterStack stack){
    return stack->top==-1;
}

void pushGreaterStack(pGreaterStack stack,int element){
    if(isGreaterStackFull(stack)){
        printf("the Greater stack has been filled,don't allow push\n");
        return;
    }else{
        stack->data[++(stack->top)]=element;
    }
}

int popGreaterStack(pGreaterStack stack){
    if(isGreaterStackEmpty(stack)){
        printf("the Greater stack is empty,don't pop\n");
    }else{
        return (stack->data[(stack->top)--]);
    }
}

//按照从top-->0打印大栈元素
void toStringGreaterStack(pGreaterStack stack){
    int n = stack->top;
    printf("\ntoGreaterStackString:");
    if(n==-1){
        printf("the greater stack is empty");
    }else{
        while(n>=0){
            printf("%d ",stack->data[n]);
            n--;
        }
    }
    printf("\n");

}



/*
把小栈中n个元素分别弹栈并且分别压入大栈
*/
void popSmallerStackPushGreaterStack(pSmallerStack stack1,pGreaterStack stack2,int n){
    int i=0;
    while(!isSmallerStackEmpty(stack1) && i<n){
        //printf("move\n");
        pushGreaterStack(stack2,popSmallerStack(stack1));
        i++;
    }
    //printf("is stack1 full %d\n",isSmallerStackFull(stack1));
}

/*
这个函数实现当小栈满但是大栈未满时，如何把小栈元素(全部或者部分)弹栈并压入大栈
*/
int buildTempArrayThenpopSmallerStackPushGreaterStack(pSmallerStack stack1,pGreaterStack stack2){
    int n = stack2->top+1;//获取大栈的元素个数
    int arr1[n];//定义临时数组，用于存放大栈元素
    int temp = M-n;//获取大栈空余空间个数
    //printf("test2,%d",N-temp);
    int arr2[N];//定义临时数组arr2，用于存放小栈元素
    int i=0;

    if(temp>=N){
        /*
        如果大栈中的空余空间大于小栈的长度,
        先把大栈元素全部弹栈并用数组保存，在把小栈元素一一弹栈并分别压入大栈，在按顺序把临时
        数组中的元素压入大栈。
        */
        while(!isGreaterStackEmpty(stack2)){//把大栈元素全部弹栈
            arr1[i]=popGreaterStack(stack2);
            i++;
        }
        popSmallerStackPushGreaterStack(stack1,stack2,N);//把小栈元素全部弹栈并压入大栈
        i=n-1;
        while(i>=0){//按顺序把临时数组的元素压入大栈
            pushGreaterStack(stack2,arr1[i]);
            i--;
        }
    }else{
        /*
        大栈空间剩余空间不足以放入全部的小栈元素
        求出大栈的空余空间temp
        1.先把大栈中所有元素弹栈并用临时数组保存
        2.先把小栈中的N-temp个元素弹栈用临时数组保存
        3.在小栈中的temp个元素分别弹栈并一一压栈大栈。
        4.分别按照顺序把临时数组中的元素一一压栈回大栈和小栈
        */
        i=0;
        while(!isGreaterStackEmpty(stack2)){//弹栈大栈中所有元素
            arr1[i]=popGreaterStack(stack2);
            i++;
        }
        i=0;
        while(!isSmallerStackEmpty(stack1) && i<N-temp){//把小栈中N-temp个元素弹栈
            arr2[i]=popSmallerStack(stack1);
            i++;
        }
        popSmallerStackPushGreaterStack(stack1,stack2,temp);//在小栈中的temp个元素分别弹栈并一一压栈大栈。

        //分别按照顺序把临时数组中的元素一一压栈回大栈和小栈
        i=n-1;
        while(i>=0){
            pushGreaterStack(stack2,arr1[i]);
            i--;
        }
        i=N-temp-1;
        while(i>=0){
            pushSmallerStack(stack1,arr2[i]);
            i--;
        }
    }
        return 1;
}

/*
入队列，思路：
1.如果小栈不满，压入小栈，
2.如果小栈满了，大栈为空，把小栈元素分别弹栈并压入大栈，并把元素压入已经为空的小栈中
3.如果小栈满了，大栈不为空且大栈不满，分为下面两种情况
    3.1.如果大栈中有元素，并且大栈的剩余空间R>N(小栈容量)，建立一个临时数组，先把大栈中的元素
        全部弹栈并用数组保存，在把小栈的元素分别弹栈并一一压入大栈。在把临时数组中元素的按照出队列的顺序一一压入大栈中
    3.2.如果大栈中有元素而且大栈的剩余空间R<N(小栈的容量)，那么此时我们的想法是把小栈中栈底的R个运算弹栈并压栈大栈中。
    首先用临时数组arr2保存小栈弹出的N-R个元素，在把大栈中的所有元素弹栈并放入一个临时数组中arr1中。
    把小栈中剩余的元素依次弹栈并压入大栈，再把临时数组arr1和临时数组arr2中的元素，按照之前的顺序压入大栈和小栈中、
    此时大栈已满，小栈还有N-R个元素可用。所有可用继续入队列(元素压入小栈)，直到小栈也满为止。
4.如果大栈元素满了小栈元素也满了，则队列满了
最大的队列容量：为 M+N
*/
int addQueue(pSmallerStack stack1,pGreaterStack stack2,int element){
    if(isSmallerStackFull(stack1) && isGreaterStackEmpty(stack2)){
        //printf("stack1 fill\n");
        popSmallerStackPushGreaterStack(stack1,stack2,N);
        //printf("is stack1 full %d\n",isSmallerStackFull(stack1));
        pushSmallerStack(stack1,element);
        return 1;
    }else if(isSmallerStackFull(stack1) && !isGreaterStackEmpty(stack2) && !isGreaterStackFull(stack2)){
        buildTempArrayThenpopSmallerStackPushGreaterStack(stack1,stack2);
        pushSmallerStack(stack1,element);
        return 1;
    }else if(!isSmallerStackFull(stack1)){
        pushSmallerStack(stack1,element);
        return 1;
    }else{
            //printf(" greater index %d ",stack2->top);
            //toStringGreaterStack(stack2);
            printf("the stack has been filled\n");
            return 0;
        }
}

/*
出队列：
1.如果大栈不为空，大栈进行弹栈
2.如果大栈为空，小栈不为空，把小栈元素分别弹栈并压入大栈，对大栈进行一次弹栈操作
3.如果大栈为空，小栈也为空，那么队列为空
*/
int deleteQueue(pSmallerStack stack1,pGreaterStack stack2){
    if(!isGreaterStackEmpty(stack2)){
        return popGreaterStack(stack2);
    }else if(isGreaterStackEmpty(stack2) && !isSmallerStackEmpty(stack1)){
        popSmallerStackPushGreaterStack(stack1,stack2,N);
        return popGreaterStack(stack2);
    }else{
        printf("the stack has been empty\n");
        return;
    }
}

/*根据入队列的顺序打印队列中的元素，和出队列规则一致*/
void toString(pSmallerStack stack1,pGreaterStack stack2){
    int top;
    printf("Queue toString:");
    if(!isGreaterStackEmpty(stack2)){
        top = stack2->top;
        while(top>=0){
            printf("%d ",stack2->data[top]);
            top--;
        }
    }
    if(!isSmallerStackEmpty(stack1)){
        top = 0;
        while(top<=stack1->top){
            printf("%d ",stack1->data[top]);
            top++;
        }
    }
    printf("\n");

    if(isSmallerStackEmpty(stack1) && isGreaterStackEmpty(stack2)){
        printf("the queue is empry\n");
    }
}

void main(){
    /*在第四行和第五行调整M和N的大小，来查看测试结果
        当 M=89 N=10，队列容量为99
        当M=90 N=10 队列容量为100
        当M=91 N=10,队列容量为101
    */
    pSmallerStack stack1 = createSmallerStack();
    pGreaterStack stack2 = createGreaterStack();
    int i=0;
    for(i=1;i<=100;i++){
        int result =  addQueue(stack1,stack2,i);
        if(result){
            toString(stack1,stack2);
        }else{
            break;
        }
    }
}


