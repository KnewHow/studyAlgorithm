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
��ʹ���ڱ����㷨�ͻᵼ��ÿ��ѭ������һ��i<=list->length���жϣ�
Ϊ����ʾ���㣬�������������Ǳ��1��ʼ��0�Ǳ��ŵ�������ĳ���+1
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
ʹ��˳����ң�ʹ���ڱ��㷨��
���ʹ���ڱ��㷨����ô����ĵ�һ��Ԫ�ؾ�ֻ�ܴ������ĳ���
����������ĽǱ��Ǵ�1��ʼ�ġ�0�ŽǱ��ŵ���Ҫ���ҵ�Ԫ��element��
��ѭ���˳��ǣ�Ҫô���ҵ��ˣ������ҵ�Ԫ�صĽǱ�i
Ҫô��i=0;û�ҵ�
*/
int orderSearch2(pList list,int element){
    int i;
    list->data[0]=element;
    for(i=list->length;list->data[i]!=element;i--);
    return i;//0��ʾû���ҵ�
}

/*���ֲ��ң�ȥ�յ���Ϊ�ָ��*/
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
    return -1;//û�ҵ�������-1
}

/*
���ֲ��ң�ȡ�ƽ�ָ����Ϊ�е�
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
    return -1;//û�ҵ�������-1
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
            binarySearch(list,i);//ʹ���е�ָ�
        }
    }
    end=clock();
    duration=((double)(end-start))/CLK_TCK/MAXSIZE/count;
    printf("use middle as the split point:%f\n",duration);


    start=clock();
    for(j=0;j<count;j++){
        for(i=0;i<MAXSIZE;i++){
            binarySearch2(list,i);//ʹ�ûƽ�ָ��ָ�
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
