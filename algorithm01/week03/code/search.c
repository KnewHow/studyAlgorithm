#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

#define MAXSIZE 1000000

typedef int dataType;

typedef struct node{
    dataType data[MAXSIZE];
    int length;
}lis,*pList;


pList createEmptyList(){
    pList list = (pList)malloc(sizeof(lis));
    if(list){
        list->length=-1;
    }
    return list;
}

int isFull(pList list){
    return (list->length==MAXSIZE-1);
}

int isEmpty(pList list){
    return (list->length==-1);
}

void insert(pList list,dataType element){
    if(isFull(list)){
        printf("the list has full");
        return;
    }
    list->data[++(list->length)]=element;

}

dataType findIndex(pList list,int index){
    if(isEmpty(list)){
        printf("the list is empty");
        return;
    }
    return list->data[index];
}

void toString(pList list){
    int length=0;
    printf("\ntoString:");
    while(length<=list->length){
        printf("%d ",list->data[length]);
        length++;
    }
}


/*
不使用哨兵是算法就会导致每次循环进行一次i<=list->length的判断，
为了演示方便，我们这里的数组角标从1开始，0角标存放的是数组的长度+1
*/
int orderSearch(pList list,int element){
    int i;
    for(i=0;i<=list->length && list->data[i]!=element;i++);
    if(i>list->length){
        return -1;
    }else{
        return i;
    }
}

/*
使用顺序查找，使用哨兵算法，
如果使用哨兵算法，那么数组的第一个元素就只能存放数组的长度
数组的真正的角标是从1开始的。0号角标存放的需要查找的元素element，
当循环退出是，要么是找到了，返回找到元素的角标i
要么是i=0;没找到
*/
int orderSearch2(pList list,int element){
    int i;
    list->data[0]=element;
    for(i=list->length;list->data[i]!=element;i--);
    return i;//0表示没有找到
}

/*二分查找，去终点作为分割点*/
int binarySearch(pList list,int element){
    int left=1;
    int right=list->length;
    while(left<=right){
        int mid=(right+left)/2;
        if(element>list->data[mid]){
            left=mid+1;
        }else if(element<list->data[mid]){
            right = mid - 1;
        }else{
            return mid;
        }
    }
    return -1;//没找到，返回-1
}

/*
二分查找，取黄金分割点作为中点
*/
int binarySearch2(pList list,int element){
    int left=1;
    int right=list->length;
    while(left<=right){
        int mid=left+0.618*(right-left);
        if(element>list->data[mid]){
            left=mid+1;
        }else if(element<list->data[mid]){
            right = mid - 1;
        }else{
            return mid;
        }
    }
    return -1;//没找到，返回-1
}


void main(){
    int i=0,j=0;
    clock_t start,end;
    double duration;//used to stored top - end

    int count =10;
    pList list = createEmptyList();

    insert(list,MAXSIZE);
    for(i=1;i<MAXSIZE;i++){
        insert(list,i);
    }



    start=clock();
    start=clock();
    for(j=0;j<count;j++){
        for(i=0;i<MAXSIZE;i++){
            binarySearch(list,i);//使用中点分割
        }
    }
    end=clock();
    duration=((double)(end-start))/CLK_TCK/MAXSIZE/count;
    printf("use middle as the split point:%f\n",duration);


    start=clock();
    for(j=0;j<count;j++){
        for(i=0;i<MAXSIZE;i++){
            binarySearch2(list,i);//使用黄金分割点分割
        }
    }
    end=clock();
    duration=((double)(end-start))/CLK_TCK/MAXSIZE/count;
    printf("use huangJinFenGeDian as the split point:%f\n",duration);


    //toString(list);

/*
    insert(list,10);
    for(i=1;i<=10;i++){
        insert(list,i);
    }
    printf("%d ",orderSearch2(list,7));
    printf("%d ",orderSearch2(list,11));
    printf("%d ",binarySearch(list,9));
    printf("%d ",binarySearch(list,11));
    toString(list);
*/
}
