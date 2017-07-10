#include<stdio.h>
#include<stdlib.h>

#define m 9 //内部迷宫(不包含外墙的迷宫)的行数
#define n 9 //内部(不包含外墙的迷宫)迷宫的列数
#define MAXSIZE 100


typedef struct {
    int x,y;
}item;


//定义一个数据类型为dataType，在栈里面存在此数据
//主要作为迷宫移动位置的临时存放点，其中x为当前位置的横坐标，y为当前位置的纵坐标
//d为 搜索的次数(方向)
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
    dataType temp;//定义临时位置
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
            if(maze[i][j]==0){//表示由当前路向其他方向探测，有通路
                //把当前位置和探索的方向压入栈
                temp.x = x;
                temp.y = y;
                temp.d = d;
                push(stack,temp);
                //把以及探测可以同行的位置坐标使用x,y来保存
                x = i;
                y = j;
                maze[x][y]=-1;//把走过的路置为-1，方便将来的回溯算法

                if(x == m && y == n){//表示迷宫探测完毕，找到出口
                    while(!isStackEmpty(stack)){//把栈内元素弹出并打印
                        temp = pop(stack);
                        printf("(%d,%d,%d),<-",temp.x,temp.y,temp.d);//打印路径
                    }
                    //销毁栈
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
    //定义第一次移动 ,方向为北
	move[0].x = 0;
	move[0].y = 1;

	//定义第二次移动，方向为南
	move[1].x = 0;
	move[1].y = -1;

	//规定第三次移动，方向为东
	move[2].x = 1;
	move[2].y = 0;

	//规定第三次移动,方向为西
	move[3].x = -1;
	move[3].y = 0;
	mazePath(maze,move,1,1);
    //printf("test");
}
