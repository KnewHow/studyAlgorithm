#include<stdio.h>
#include<stdlib.h>

/*
�ʼǣ����������еĽڵ��ָ������ж��������������ӣ�������next�ͷ�ʽsubList����ָ����
���ǰ������ָ����Ĳ�һ���Ƕ�����������˫������Ͳ��Ƕ�������

���ã�����ͼ���ָ��ӵ����ݽṹ����ʹ������������洢��
*/
typedef struct node{
    int tag;//���λ�����tagΪ0����ʾ��Ԫ�ؽڵ㣬����Ϊ�����
    union{//�ӱ�ָ�����ubList�뵥Ԫ������element���ã�������洢�ռ�
        int element;
        struct node *subList
    }uRegion;
    struct node *next;
}list,*pList;




void main(){
    printf("just test");
}
