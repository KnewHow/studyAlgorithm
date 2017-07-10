#include<stdio.h>
#include<stdlib.h>

#define m 9 //�ڲ��Թ�(��������ǽ���Թ�)������
#define n 9 //�ڲ�(��������ǽ���Թ�)�Թ�������
#define MAXSIZE 100


typedef struct {
    int x,y;
}item;


//����һ����������ΪdataType����ջ������ڴ�����
//��Ҫ��Ϊ�Թ��ƶ�λ�õ���ʱ��ŵ㣬����xΪ��ǰλ�õĺ����꣬yΪ��ǰλ�õ�������
//dΪ �����Ĵ���(����)
typedef struct{
    int x,y,d;
}dataType;


typedef struct{
    dataType data[MAXSIZE];
    int top;
}sta,*pStack;


pStack createEmptyStack(){
    pStack stack = (pStack)malloc(sizeof(sta));
    if(stack){
        stack->top=-1;
    }
    return stack;
}

int isStackFull(pStack stack){
    return (stack->top==MAXSIZE-1);
}

int isStackEmpty(pStack stack){
    return (stack->top==-1);
}

void push(pStack stack,dataType data){
    if(isStackFull(stack)){
        printf("the stack is full");
        return;
    }
    stack->data[++(stack->top)]=data;
}

dataType pop(pStack stack){
    if(isStackEmpty(stack)){
        printf("the stack is empty");
        return;
    }
    return stack->data[(stack->top)--];
}



void mazePath(int maze[m+2][n+2],item move[],int x0,int y0){
    dataType temp;//������ʱλ��
    int x,y,d,i,j;
    x=x0;
    y=y0;
    temp.x=x0;
    temp.y=y0;
    temp.d=-1;
    pStack stack = createEmptyStack();
    push(stack,temp);

    while(!isStackEmpty(stack)){
        temp = pop(stack);
        x = temp.x;
        y = temp.y;
        d=temp.d+1;
        while(d<4){
            i=x+move[d].x;
            j=y+move[d].y;
            if(maze[i][j]==0){//��ʾ�ɵ�ǰ·����������̽�⣬��ͨ·
                //�ѵ�ǰλ�ú�̽���ķ���ѹ��ջ
                temp.x = x;
                temp.y = y;
                temp.d = d;
                push(stack,temp);
                //���Լ�̽�����ͬ�е�λ������ʹ��x,y������
                x = i;
                y = j;
                maze[x][y]=-1;//���߹���·��Ϊ-1�����㽫���Ļ����㷨

                if(x == m && y == n){//��ʾ�Թ�̽����ϣ��ҵ�����
                    while(!isStackEmpty(stack)){//��ջ��Ԫ�ص�������ӡ
                        temp = pop(stack);
                        printf("(%d,%d,%d),<-",temp.x,temp.y,temp.d);//��ӡ·��
                    }
                    //����ջ
                    free(stack);
                    return 1;
                }else{
                    d=0;
                }
            }else{
                d++;
            }
        }
    }

    free(stack);
    return 0;

}






void main(){

    int maze[11][11]={
	 			 {1,1,1,1,1,1,1,1,1,1,1},
		         {1,0,0,0,1,0,1,1,1,0,1},
		         {1,0,1,0,0,0,0,1,0,1,1},
		         {1,0,0,1,0,0,0,1,0,0,1},
		         {1,1,0,1,0,1,0,1,0,1,1},
		         {1,0,1,0,1,0,0,1,0,0,1},
		         {1,0,0,0,0,0,1,0,1,0,1},
		         {1,1,1,1,0,1,0,0,0,0,1},
		         {1,0,0,1,0,0,0,1,0,1,1},
		         {1,0,0,0,0,1,0,1,0,0,1},
		         {1,1,1,1,1,1,1,1,1,1,1}
				 };
    item move[4];
    //�����һ���ƶ� ,����Ϊ��
	move[0].x = 0;
	move[0].y = 1;

	//����ڶ����ƶ�������Ϊ��
	move[1].x = 0;
	move[1].y = -1;

	//�涨�������ƶ�������Ϊ��
	move[2].x = 1;
	move[2].y = 0;

	//�涨�������ƶ�,����Ϊ��
	move[3].x = -1;
	move[3].y = 0;
	mazePath(maze,move,1,1);
    //printf("test");
}
