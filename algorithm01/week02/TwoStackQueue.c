#include<stdio.h>
#include<stdlib.h>

#define M 95
#define N 10

/*
����2.3 �����������ջģ��ʵ��һ������?
��ʦ����

����Ϊ���е���󳤶�ΪM+N,�������ҵ��㷨˼�롣
1.�����ʱ����Сջ����ʱ��һֱ��Сջ����ѹ��Ԫ��(���)��
���Сջ���˵��Ǵ�ջΪ�գ���ô�Ͱ�Сջ�����Ԫ�طֱ�ջ��һһѹ���ջ���档
���������Сջ��Ϊ�գ���ջδ����(M>N),��ʱ����ִ�м��������(Ԫ��ѹ��Сջ)�����߳�����(Ԫ�شӴ�ջ��ջ)��
��������(Ԫ��ѹ��Сջ)����Сջ���𽥱���������ʱ�������������
1.�����ջΪ�գ���ô��������ķ�������Сջ��Ԫ�طֱ�ջ��ѹ���ջ

2.�����ջ����Ԫ�أ����Ҵ�ջ��ʣ��ռ�R>N(Сջ����)������һ����ʱ���飬�ȰѴ�ջ�е�Ԫ��
ȫ����ջ�������鱣�棬�ڰ�Сջ��Ԫ�طֱ�ջ��һһѹ���ջ���ڰ���ʱ������Ԫ�صİ��ճ����е�˳��һһѹ���ջ��

3.�����ջ����Ԫ�ض��Ҵ�ջ��ʣ��ռ�R<N(Сջ������)����ô��ʱ���ǵ��뷨�ǰ�Сջ��ջ�׵�R�����㵯ջ��ѹջ��ջ�С�
    ��������ʱ����arr2����Сջ������N-R��Ԫ�أ��ڰѴ�ջ�е�����Ԫ�ص�ջ������һ����ʱ������arr1�С�
    ��Сջ��ʣ���Ԫ�����ε�ջ��ѹ���ջ���ٰ���ʱ����arr1����ʱ����arr2�е�Ԫ�أ�����֮ǰ��˳��ѹ���ջ��Сջ�С�
    ��ʱ��ջ������Сջ����N-R��Ԫ�ؿ��á����п��ü��������(Ԫ��ѹ��Сջ)��ֱ��СջҲ��Ϊֹ��

    �����������㷨�����е��������Ϊ��ջ����Сջ������ΪM+N

�����Ǵ���ľ���ʵ�֣�
*/


//���쳤�Ƚ�С��ջ
typedef struct node1{
    int data[N];
    int top;
}smallerStack,*pSmallerStack;

//���쳤�Ƚϴ��ջ
typedef struct node2{
    int data[M];
    int top;
}greaterStack,*pGreaterStack;


/*==============================�Գ��Ƚ�С��ջ�Ĳ���=======================================*/
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

//���մ�top-->0 ��ӡСջԪ��
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




/*======================�Գ��Ƚϴ��ջ�Ĳ���===============================*/
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

//���մ�top-->0��ӡ��ջԪ��
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
��Сջ��n��Ԫ�طֱ�ջ���ҷֱ�ѹ���ջ
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
�������ʵ�ֵ�Сջ�����Ǵ�ջδ��ʱ����ΰ�СջԪ��(ȫ�����߲���)��ջ��ѹ���ջ
*/
int buildTempArrayThenpopSmallerStackPushGreaterStack(pSmallerStack stack1,pGreaterStack stack2){
    int n = stack2->top+1;//��ȡ��ջ��Ԫ�ظ���
    int arr1[n];//������ʱ���飬���ڴ�Ŵ�ջԪ��
    int temp = M-n;//��ȡ��ջ����ռ����
    //printf("test2,%d",N-temp);
    int arr2[N];//������ʱ����arr2�����ڴ��СջԪ��
    int i=0;

    if(temp>=N){
        /*
        �����ջ�еĿ���ռ����Сջ�ĳ���,
        �ȰѴ�ջԪ��ȫ����ջ�������鱣�棬�ڰ�СջԪ��һһ��ջ���ֱ�ѹ���ջ���ڰ�˳�����ʱ
        �����е�Ԫ��ѹ���ջ��
        */
        while(!isGreaterStackEmpty(stack2)){//�Ѵ�ջԪ��ȫ����ջ
            arr1[i]=popGreaterStack(stack2);
            i++;
        }
        popSmallerStackPushGreaterStack(stack1,stack2,N);//��СջԪ��ȫ����ջ��ѹ���ջ
        i=n-1;
        while(i>=0){//��˳�����ʱ�����Ԫ��ѹ���ջ
            pushGreaterStack(stack2,arr1[i]);
            i--;
        }
    }else{
        /*
        ��ջ�ռ�ʣ��ռ䲻���Է���ȫ����СջԪ��
        �����ջ�Ŀ���ռ�temp
        1.�ȰѴ�ջ������Ԫ�ص�ջ������ʱ���鱣��
        2.�Ȱ�Сջ�е�N-temp��Ԫ�ص�ջ����ʱ���鱣��
        3.��Сջ�е�temp��Ԫ�طֱ�ջ��һһѹջ��ջ��
        4.�ֱ���˳�����ʱ�����е�Ԫ��һһѹջ�ش�ջ��Сջ
        */
        i=0;
        while(!isGreaterStackEmpty(stack2)){//��ջ��ջ������Ԫ��
            arr1[i]=popGreaterStack(stack2);
            i++;
        }
        i=0;
        while(!isSmallerStackEmpty(stack1) && i<N-temp){//��Сջ��N-temp��Ԫ�ص�ջ
            arr2[i]=popSmallerStack(stack1);
            i++;
        }
        popSmallerStackPushGreaterStack(stack1,stack2,temp);//��Сջ�е�temp��Ԫ�طֱ�ջ��һһѹջ��ջ��

        //�ֱ���˳�����ʱ�����е�Ԫ��һһѹջ�ش�ջ��Сջ
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
����У�˼·��
1.���Сջ������ѹ��Сջ��
2.���Сջ���ˣ���ջΪ�գ���СջԪ�طֱ�ջ��ѹ���ջ������Ԫ��ѹ���Ѿ�Ϊ�յ�Сջ��
3.���Сջ���ˣ���ջ��Ϊ���Ҵ�ջ��������Ϊ�����������
    3.1.�����ջ����Ԫ�أ����Ҵ�ջ��ʣ��ռ�R>N(Сջ����)������һ����ʱ���飬�ȰѴ�ջ�е�Ԫ��
        ȫ����ջ�������鱣�棬�ڰ�Сջ��Ԫ�طֱ�ջ��һһѹ���ջ���ڰ���ʱ������Ԫ�صİ��ճ����е�˳��һһѹ���ջ��
    3.2.�����ջ����Ԫ�ض��Ҵ�ջ��ʣ��ռ�R<N(Сջ������)����ô��ʱ���ǵ��뷨�ǰ�Сջ��ջ�׵�R�����㵯ջ��ѹջ��ջ�С�
    ��������ʱ����arr2����Сջ������N-R��Ԫ�أ��ڰѴ�ջ�е�����Ԫ�ص�ջ������һ����ʱ������arr1�С�
    ��Сջ��ʣ���Ԫ�����ε�ջ��ѹ���ջ���ٰ���ʱ����arr1����ʱ����arr2�е�Ԫ�أ�����֮ǰ��˳��ѹ���ջ��Сջ�С�
    ��ʱ��ջ������Сջ����N-R��Ԫ�ؿ��á����п��ü��������(Ԫ��ѹ��Сջ)��ֱ��СջҲ��Ϊֹ��
4.�����ջԪ������СջԪ��Ҳ���ˣ����������
���Ķ���������Ϊ M+N
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
�����У�
1.�����ջ��Ϊ�գ���ջ���е�ջ
2.�����ջΪ�գ�Сջ��Ϊ�գ���СջԪ�طֱ�ջ��ѹ���ջ���Դ�ջ����һ�ε�ջ����
3.�����ջΪ�գ�СջҲΪ�գ���ô����Ϊ��
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

/*��������е�˳���ӡ�����е�Ԫ�أ��ͳ����й���һ��*/
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
    /*�ڵ����к͵����е���M��N�Ĵ�С�����鿴���Խ��
        �� M=89 N=10����������Ϊ99
        ��M=90 N=10 ��������Ϊ100
        ��M=91 N=10,��������Ϊ101
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


