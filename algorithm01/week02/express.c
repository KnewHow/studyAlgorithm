#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#define MAXSIZE 100


#include<stdio.h>
#include<stdlib.h>
/*使用链表来模拟堆栈，*/



/*=======================================================定义double类型的堆栈链式存储并进行相关的压栈，弹栈等操作===============================================================*/

//定义double类型的堆栈的链式存储
typedef struct node3{
    double element;
    struct node3 *next;
}integerSta,*pIntegerStack;

//构造一个double类型的链式栈
pIntegerStack createIntegerEmptyStack(){
    pIntegerStack stack;
    stack = (pIntegerStack)malloc(sizeof(integerSta));
    if(stack){
        stack->next=NULL;
    }
    return stack;
}

//判断double类型的链式栈是否为空
int isIntegerEmpty(pIntegerStack stack){
    if(stack->next==NULL){
        return 1;
    }else{
        return 0;
    }
}

//压栈
void pushInteger(pIntegerStack stack,double element){
    pIntegerStack node = (pIntegerStack)malloc(sizeof(integerSta));
    node->element=element;
    node->next=stack->next;
    stack->next=node;
}

//弹栈
double popInteger(pIntegerStack stack){
    double element;
    pIntegerStack topHead;
    if(isEmpty(stack)){
        printf("the stack is empty,can not pop");
        return;
    }else{
        topHead = stack->next;
        stack->next = topHead->next;
        element = topHead->element;
        free(topHead);
        return element;
    }
}

//取栈顶元素
double getIntegetStackTopElement(pIntegerStack stack){
    return (stack->next->element);
}

//打印栈内元素
void toStringInteger(pIntegerStack stack){
    pIntegerStack top = stack->next;
    printf("toString:");
    while(top!=NULL){
        printf("%f ",top->element);
        top=top->next;
    }
    printf("\n");
}




/*================================================定义一个存储字符的线性表=========================================================================*/



//构造一个线性表存储后缀表达式
typedef struct node2{
    char data[MAXSIZE];
    int length;
}li,*pList;



//初始化线性表
pList createEmptyList(){
    pList p;
    p = (pList)malloc(sizeof(li));
    if(p){
        p->length=-1;
    }
    return p;
}

//向线性表中插入元素
void insert(pList list,char c){
    if(list){
        list->data[++(list->length)]=c;
    }
}

//将线性表中的元素打印
void toStringList(pList list){
    int i;
    for(i=0;i<=list->length;i++){
        printf("%c ",list->data[i]);
    }
    printf("\n");

}



/*==================================================定义一个字符栈并进行相关操作=================================================================*/
//定义字符栈
typedef struct node{
    char element;
    struct node *next;
}sta,*pStack;

//创建一个空的字符链式栈
pStack createEmptyStack(){
    pStack stack;
    stack = (pStack)malloc(sizeof(sta));
    if(stack){
        stack->next=NULL;
    }
    return stack;
}

//判断链式栈是否为空
int isEmpty(pStack stack){
    if(stack->next==NULL){
        return 1;
    }else{
        return 0;
    }
}

//把元素压入栈
void push(pStack stack,char element){
    pStack node = (pStack)malloc(sizeof(sta));
    node->element=element;
    node->next=stack->next;
    stack->next=node;
}

//把元素弹栈
char pop(pStack stack){
    char element;
    pStack topHead;
    if(isEmpty(stack)){
        printf("the stack is empty,can not pop");
        return NULL;
    }else{
        topHead = stack->next;
        stack->next = topHead->next;
        element = topHead->element;
        free(topHead);
        return element;
    }
}

//获取栈顶元素
char getTopElement(pStack stack){
    if(isEmpty(stack)){
        printf("the stack is empty,can not get top element");
        return;
    }else{
        return (stack->next->element);
    }
}



/*=============================================中缀表达式转后缀表达式=====================================================================*/


//打印字符数组
void charArrayToString(char *arr){
    char *p  = arr;
    while(*p!='\0'){
        printf("%c ",*p);
        p = p+1;
    }
}



/*
判断字符c是否存在字符数组arr中
存在，返回1
不存在，返回0
*/
int isCharArrContainChar(char arr[],char c){
    char *p =arr;
    while(*p!='\0'){
        if(*p==c){
            return 1;
        }
        p = p+1;
    }
    return 0;
}


/*给定一个运算符，判断他的优先级，返回数字越大，优先级越高，例如
    operatorPriorityArr是一个二维数组，下面是模拟的内容，优先级用户可以自定义，数组按元素优先级由低到高排列
        0 +-    第0优先级
        1 * /   第1优先级
        2 ()    第2优先级

    c:等待判断优先级的运算符
*/
int getCharIndex(char c,char operatorPriorityArr[][MAXSIZE],int length){
    int i;
    for(i=0;i<length;i++){
        if(isCharArrContainChar(operatorPriorityArr[i],c)){
            return i;
        }
    }
    return -1;
}


/*
判断字符栈的栈顶元素的优先级和读入字符的优先级
参数：
    stackTopEle：栈顶元素
    readChar：读入的元素
    operatorPriorityArr：用户自定义的运算符优先级二维字符数组，数组按元素优先级由低到高排列
    length:二维数组的行数

比较规则：
    1.如果读入的字符为"(",那么"("的优先级最高，直接压栈
    2.如果栈顶元素为"(",其优先级最低，eadChar直接入栈
    3.如果读入的元素readChar优先级大于栈顶元素，则readChar入栈。例如eadChar为"*" topChar为"+",则"*"入栈
    4.如果读入的元素readChar优先级小于或者等于(因为运算需要按照从左往右的顺序)栈顶元素，则topChar弹栈并输出(记录)。
        再次判断readChar和当前栈顶元素的优先级，如果当readChar还是优先级小于或者等于当前栈顶元素，接着弹栈并输出(记录)。
        一直比较，直到readChar的优先级大于栈顶元素或者栈为空。
    5.如果readChar为")"，一直弹栈到到第一次遇到"(",并把"("也弹栈，对"("和")"不做输出，其运算符弹栈且输出(记录)

        返回值：
            1：压栈
            0：读入")" 直到把第一个"("弹栈栈为止
            2：弹出当前的栈顶元素，并继续比较
*/
int compareOperatorChar(char stackTopEle,char readChar,char operatorPriorityArr[][MAXSIZE],int length){
    int index1,index2;
    if(stackTopEle=='('){
        return 1;//栈为空，直接压栈
    }else if(readChar==')'){
        return 0;//读入遇到")",直到把第一个"("弹栈栈为止
    }else{
        //获取两个运算符的优先级
        index1 = getCharIndex(stackTopEle,operatorPriorityArr,length);
        index2 = getCharIndex(readChar,operatorPriorityArr,length);
        if(index1<index2){//比较优先级
            return 1;
        }else{
            return 2;
        }
    }
}


/*
根据优先级的返回结果进行对应的压栈和弹栈操作
参数：
    stack:准备好的空字符栈
    readChar：读入的字符
    operatorPriorityArr:定义的优先级规则
    list：储存后缀表达式的字符线性表
    length：二维数组的行数
*/
void comparePriority(pStack stack,char readChar,char operatorPriorityArr[][MAXSIZE],pList list,int length){
    if(isEmpty(stack)){
        push(stack,readChar);
        return 1;
    }else{
        char topEle = getTopElement(stack);
        int result = compareOperatorChar(topEle,readChar,operatorPriorityArr,length);
        if(result==0){
            while(getTopElement(stack)!='('){
                insert(list,pop(stack));
            }
            pop(stack);
            return;
        }else if(result==1){
            push(stack,readChar);
            return;
        }else{
            insert(list,pop(stack));
            //递归再次比较
            comparePriority(stack,readChar,operatorPriorityArr,list,length);
        }
    }
}


/*
根据中缀表达式或者后缀表达式，转换规则：
    1.对于数字，进行原样的输出或者记录
    2.对于运算符，根据优先级进行压栈弹栈操作，优先级比较规则参照上面
参数：
    stack:准备好的空字符栈
    arr：中缀表达式的字符数组，支持空格隔开
    operatorPriorityArr:定义的优先级规则
    list：储存后缀表达式的字符线性表
    length：二维数组的行数
*/
char* getBehindExpress(pStack stack,char *arr,char operatorPriorityArr[3][MAXSIZE],pList list,int length){
    char *p  = arr;
    while(*p!='\0'){
        if(*p>='0' && *p<='9'){
            insert(list,*p);
        }else if(*p==' '){
            p = p+1;
            continue;
        }else if(getCharIndex(*p,operatorPriorityArr,length)!=-1){//判断运算符是否和法
                comparePriority(stack,*p,operatorPriorityArr,list,length);
        }else{
            printf("the operational character is illegal\n");
            return "error";
        }
        p = p+1;
    }
    //当数字读取完毕后，要把栈里面的运算符全部弹栈
    while(!isEmpty(stack)){
        insert(list,pop(stack));
    }
}

//打印字符栈里面的元素
void toString(pStack stack){
    pStack top = stack->next;
    printf("toString:");
    while(top!=NULL){
        printf("%c ",top->element);
        top=top->next;
    }
    printf("\n");
}




/*==================================================计算后缀表达式的值==========================================================================*/
/*计算规则如下：
求后缀表达式的值
			6 2 / 3 - 4 2 * + =

			后缀表达式的求解原理：遇到数值先记录(压栈)，遇到符号才计算(弹栈两个元素)。计算离符号最近的两个数
			1.6 2 / ==> 3 压栈
			2.3 3 - ==> 0 压栈
			3.0 4 2 * ==> 0 8
			4.0 8 + ==>8
			5.8 = ==> 8
*/
double getValueByAfterExpress(pList list,pStack stack){
    int i,store;
    double temp,a1,a2;
    for(i=0;i<=list->length;i++){
        //printf("test");
        char c = list->data[i];
        if(c>='0' && c<='9'){
            store = c-'0';//字符转换为数字
            temp = store*1.0;//整形转换为double型
            //printf("double:%f\n",temp);
            pushInteger(stack,temp);//数字就压栈
        }else{
            //弹栈并根据运算符做运算
            double a1 = popInteger(stack);
            double a2 = popInteger(stack);
            if(list->data[i]=='+'){
                temp = a1+a2;
                pushInteger(stack,temp);
            }

            if(list->data[i]=='-'){
                temp = a2-a1;
                pushInteger(stack,temp);
            }
            if(list->data[i]=='*'){
                temp = a1*a2;
                pushInteger(stack,temp);
            }
            if(list->data[i]=='/'){
                temp = a2/a1;
                pushInteger(stack,temp);
            }

        }
        //toStringInteger(stack);
    }
    //最终的栈顶元素即为所求的值
    return getIntegetStackTopElement(stack);
}



void main(){
    int n = 3,i;
    pStack stack  = createEmptyStack();
    pStack numberStack   = createIntegerEmptyStack();
    pList list = createEmptyList();

    char arr1[] = "2 * ( 9 + 6 / 3 - 5 ) + 4";
    char arr2[] = "2 + 9 / 3 - 5";
    char arr3[] = "3*(2*3-4*1+(3*5)/3)*3+2";
    char operatorPriorityArr[3][MAXSIZE]={"+-","*/","()"};
    //计算二维数组的行数
    int length=sizeof(operatorPriorityArr)/sizeof(operatorPriorityArr[0]);
    //char operatorArr[] = "+-*/()";
    getBehindExpress(stack,arr3,operatorPriorityArr,list,length);
    //toStringList(list);
    double value = getValueByAfterExpress(list,numberStack);
    printf("the express %s caculate result is %f",arr3,value);
    //double c = (double)('9.23');
    //printf("test:%f",c);
    //printf("%d",length);
}
