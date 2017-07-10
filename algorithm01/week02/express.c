#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#define MAXSIZE 100


#include<stdio.h>
#include<stdlib.h>
/*ʹ��������ģ���ջ��*/



/*=======================================================����double���͵Ķ�ջ��ʽ�洢��������ص�ѹջ����ջ�Ȳ���===============================================================*/

//����double���͵Ķ�ջ����ʽ�洢
typedef struct node3{
    double element;
    struct node3 *next;
}integerSta,*pIntegerStack;

//����һ��double���͵���ʽջ
pIntegerStack createIntegerEmptyStack(){
    pIntegerStack stack;
    stack = (pIntegerStack)malloc(sizeof(integerSta));
    if(stack){
        stack->next=NULL;
    }
    return stack;
}

//�ж�double���͵���ʽջ�Ƿ�Ϊ��
int isIntegerEmpty(pIntegerStack stack){
    if(stack->next==NULL){
        return 1;
    }else{
        return 0;
    }
}

//ѹջ
void pushInteger(pIntegerStack stack,double element){
    pIntegerStack node = (pIntegerStack)malloc(sizeof(integerSta));
    node->element=element;
    node->next=stack->next;
    stack->next=node;
}

//��ջ
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

//ȡջ��Ԫ��
double getIntegetStackTopElement(pIntegerStack stack){
    return (stack->next->element);
}

//��ӡջ��Ԫ��
void toStringInteger(pIntegerStack stack){
    pIntegerStack top = stack->next;
    printf("toString:");
    while(top!=NULL){
        printf("%f ",top->element);
        top=top->next;
    }
    printf("\n");
}




/*================================================����һ���洢�ַ������Ա�=========================================================================*/



//����һ�����Ա�洢��׺���ʽ
typedef struct node2{
    char data[MAXSIZE];
    int length;
}li,*pList;



//��ʼ�����Ա�
pList createEmptyList(){
    pList p;
    p = (pList)malloc(sizeof(li));
    if(p){
        p->length=-1;
    }
    return p;
}

//�����Ա��в���Ԫ��
void insert(pList list,char c){
    if(list){
        list->data[++(list->length)]=c;
    }
}

//�����Ա��е�Ԫ�ش�ӡ
void toStringList(pList list){
    int i;
    for(i=0;i<=list->length;i++){
        printf("%c ",list->data[i]);
    }
    printf("\n");

}



/*==================================================����һ���ַ�ջ��������ز���=================================================================*/
//�����ַ�ջ
typedef struct node{
    char element;
    struct node *next;
}sta,*pStack;

//����һ���յ��ַ���ʽջ
pStack createEmptyStack(){
    pStack stack;
    stack = (pStack)malloc(sizeof(sta));
    if(stack){
        stack->next=NULL;
    }
    return stack;
}

//�ж���ʽջ�Ƿ�Ϊ��
int isEmpty(pStack stack){
    if(stack->next==NULL){
        return 1;
    }else{
        return 0;
    }
}

//��Ԫ��ѹ��ջ
void push(pStack stack,char element){
    pStack node = (pStack)malloc(sizeof(sta));
    node->element=element;
    node->next=stack->next;
    stack->next=node;
}

//��Ԫ�ص�ջ
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

//��ȡջ��Ԫ��
char getTopElement(pStack stack){
    if(isEmpty(stack)){
        printf("the stack is empty,can not get top element");
        return;
    }else{
        return (stack->next->element);
    }
}



/*=============================================��׺���ʽת��׺���ʽ=====================================================================*/


//��ӡ�ַ�����
void charArrayToString(char *arr){
    char *p  = arr;
    while(*p!='\0'){
        printf("%c ",*p);
        p = p+1;
    }
}



/*
�ж��ַ�c�Ƿ�����ַ�����arr��
���ڣ�����1
�����ڣ�����0
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


/*����һ����������ж��������ȼ�����������Խ�����ȼ�Խ�ߣ�����
    operatorPriorityArr��һ����ά���飬������ģ������ݣ����ȼ��û������Զ��壬���鰴Ԫ�����ȼ��ɵ͵�������
        0 +-    ��0���ȼ�
        1 * /   ��1���ȼ�
        2 ()    ��2���ȼ�

    c:�ȴ��ж����ȼ��������
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
�ж��ַ�ջ��ջ��Ԫ�ص����ȼ��Ͷ����ַ������ȼ�
������
    stackTopEle��ջ��Ԫ��
    readChar�������Ԫ��
    operatorPriorityArr���û��Զ������������ȼ���ά�ַ����飬���鰴Ԫ�����ȼ��ɵ͵�������
    length:��ά���������

�ȽϹ���
    1.���������ַ�Ϊ"(",��ô"("�����ȼ���ߣ�ֱ��ѹջ
    2.���ջ��Ԫ��Ϊ"(",�����ȼ���ͣ�eadCharֱ����ջ
    3.��������Ԫ��readChar���ȼ�����ջ��Ԫ�أ���readChar��ջ������eadCharΪ"*" topCharΪ"+",��"*"��ջ
    4.��������Ԫ��readChar���ȼ�С�ڻ��ߵ���(��Ϊ������Ҫ���մ������ҵ�˳��)ջ��Ԫ�أ���topChar��ջ�����(��¼)��
        �ٴ��ж�readChar�͵�ǰջ��Ԫ�ص����ȼ��������readChar�������ȼ�С�ڻ��ߵ��ڵ�ǰջ��Ԫ�أ����ŵ�ջ�����(��¼)��
        һֱ�Ƚϣ�ֱ��readChar�����ȼ�����ջ��Ԫ�ػ���ջΪ�ա�
    5.���readCharΪ")"��һֱ��ջ������һ������"(",����"("Ҳ��ջ����"("��")"������������������ջ�����(��¼)

        ����ֵ��
            1��ѹջ
            0������")" ֱ���ѵ�һ��"("��ջջΪֹ
            2��������ǰ��ջ��Ԫ�أ��������Ƚ�
*/
int compareOperatorChar(char stackTopEle,char readChar,char operatorPriorityArr[][MAXSIZE],int length){
    int index1,index2;
    if(stackTopEle=='('){
        return 1;//ջΪ�գ�ֱ��ѹջ
    }else if(readChar==')'){
        return 0;//��������")",ֱ���ѵ�һ��"("��ջջΪֹ
    }else{
        //��ȡ��������������ȼ�
        index1 = getCharIndex(stackTopEle,operatorPriorityArr,length);
        index2 = getCharIndex(readChar,operatorPriorityArr,length);
        if(index1<index2){//�Ƚ����ȼ�
            return 1;
        }else{
            return 2;
        }
    }
}


/*
�������ȼ��ķ��ؽ�����ж�Ӧ��ѹջ�͵�ջ����
������
    stack:׼���õĿ��ַ�ջ
    readChar��������ַ�
    operatorPriorityArr:��������ȼ�����
    list�������׺���ʽ���ַ����Ա�
    length����ά���������
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
            //�ݹ��ٴαȽ�
            comparePriority(stack,readChar,operatorPriorityArr,list,length);
        }
    }
}


/*
������׺���ʽ���ߺ�׺���ʽ��ת������
    1.�������֣�����ԭ����������߼�¼
    2.������������������ȼ�����ѹջ��ջ���������ȼ��ȽϹ����������
������
    stack:׼���õĿ��ַ�ջ
    arr����׺���ʽ���ַ����飬֧�ֿո����
    operatorPriorityArr:��������ȼ�����
    list�������׺���ʽ���ַ����Ա�
    length����ά���������
*/
char* getBehindExpress(pStack stack,char *arr,char operatorPriorityArr[3][MAXSIZE],pList list,int length){
    char *p  = arr;
    while(*p!='\0'){
        if(*p>='0' && *p<='9'){
            insert(list,*p);
        }else if(*p==' '){
            p = p+1;
            continue;
        }else if(getCharIndex(*p,operatorPriorityArr,length)!=-1){//�ж�������Ƿ�ͷ�
                comparePriority(stack,*p,operatorPriorityArr,list,length);
        }else{
            printf("the operational character is illegal\n");
            return "error";
        }
        p = p+1;
    }
    //�����ֶ�ȡ��Ϻ�Ҫ��ջ����������ȫ����ջ
    while(!isEmpty(stack)){
        insert(list,pop(stack));
    }
}

//��ӡ�ַ�ջ�����Ԫ��
void toString(pStack stack){
    pStack top = stack->next;
    printf("toString:");
    while(top!=NULL){
        printf("%c ",top->element);
        top=top->next;
    }
    printf("\n");
}




/*==================================================�����׺���ʽ��ֵ==========================================================================*/
/*����������£�
���׺���ʽ��ֵ
			6 2 / 3 - 4 2 * + =

			��׺���ʽ�����ԭ��������ֵ�ȼ�¼(ѹջ)���������Ųż���(��ջ����Ԫ��)����������������������
			1.6 2 / ==> 3 ѹջ
			2.3 3 - ==> 0 ѹջ
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
            store = c-'0';//�ַ�ת��Ϊ����
            temp = store*1.0;//����ת��Ϊdouble��
            //printf("double:%f\n",temp);
            pushInteger(stack,temp);//���־�ѹջ
        }else{
            //��ջ�����������������
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
    //���յ�ջ��Ԫ�ؼ�Ϊ�����ֵ
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
    //�����ά���������
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
