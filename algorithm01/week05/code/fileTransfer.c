#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 100000
#include<string.h>

typedef int elementType;

/*
define the data constructor of element of set.
we use SET ARRAY index to stand for the data to reduce the time at <code>find<code> method
the element of data is from  1 to N
the index of the SET ARRAY is from 0 to N-1.
This is good idea to use this method.
*/
/*
typedef struct node{
    //elementType data;
    int parent;
}coll,pCollection;

Above equal following
*/
/*use the root node index to stand for set*/
typedef int setName;
typedef elementType setType[MAXSIZE];


/*
find the x's set root element
@param s The SET ARRAY
@param x The element needed to be searched in this array.
*/
setName find(setType s,elementType x){
    /*init the array all elements to -1*/
    for(;s[x]>=0;x=s[x]);
    return x;

}

/*
Find the x's set root element,and set x's and it's parent root's but not root array's value is
root element index. So,fisrt find, we not only find the root element and let the tree height
become lower. When we find this set secound,we will find several times to get the root element.
@param s The SET ARRAY
@param x The element needed to be searched in this array.
*/
setName findCompressPath(setType s,elementType x){
    if(s[x]<0){
        return x;
    }else{
        return s[x]=findCompressPath(s,s[x]);
    }
}


/*
union two collection.
we think the root1 not equal root2
@param s The SET ARRAY
@param root1 The root element of the collection one
@param root2 The root element of the collection two
*/
void unionCollection(setType s,setName root1,setName root2){
    s[root1]=root2;
}

/*
union two collection.
we think the root1 not equal root2
We will add lower to higher tree.If the two tree height is equal,we let the tree's
height increase one
@param s The SET ARRAY
@param root1 The root element of the collection one
@param root2 The root element of the collection two
*/
void unionCollectionByTreeHeight(setType s,setName root1,setName root2){
    if(s[root2]<s[root1]){
        s[root1]=root2;
    }else{
        if(s[root1]==s[root2]){
            s[root1]--;/*Ê÷¸ß×ÔÔö*/
        }
        s[root2]=root1;
    }
}

/*
union two collection.
we think the root1 not equal root2
We will add smaller scale tree to bigger scale tree.
@param s The SET ARRAY
@param root1 The root element of the collection one
@param root2 The root element of the collection two
*/
void unionCollectionMount(setType s,setName root1,setName root2){
    if(s[root2]<s[root1]){
        s[root2]+=s[root1];
        s[root1]=root2;

    }else{
        s[root1]+=s[root2];
        s[root2]=root1;
    }
}


/*initialize the collection to -1
@param s The array stoteing set's element index
@param n The length of the set
*/
void initializeCollection(setType s,int n){
    int i;
    for(i=0;i<n;i++){
        s[i]=-1;
    }
}

/*
"I C1 C2"
build connection about two set.
input two number,use <code>find<code> method to find the root element
of the set,if the collection is not equal,union them.
@param s The SET ARRAY to store the set's element parent index
*/
void input_connection(setType s){
    elementType u,v;
    setName root1,root2;
    scanf("%d %d\n",&u,&v);
    root1 = findCompressPath(s,u-1);
    root2 = findCompressPath(s,v-1);
    if(root1!=root2){
        unionCollectionMount(s,root1,root2);
    }
}

/*
"C C1 C2"
check the two conputer whether can transfer file each other.
First we will find the element C1 and C2 and get the root element root1 and root2
if the root1 equal root2 indicates the C1 and C2 in the same set,print "yse", otherwise
indicates the C1 and C2 not in the same set, print the "no"
@param s The SET ARRAY to store the set's element parent index
*/
void check_connection(setType s){
    elementType u,v;
    setName root1,root2;
    scanf("%d %d",&u,&v);
    root1 = findCompressPath(s,u-1);
    root2 = findCompressPath(s,v-1);
    if(root1==root2){
        printf("yes\n");
    }else{
        printf("no\n");
    }
}

/*
check how many different set in this SET ARRAY
the algorithem is to calculate how many "-1" elements in the SET ARRAY.
if the count is equal one, indicate all computer can transfer file each other
then we will print "The network is connected.\n". Otherwise we will print
"printf("There are %d components.\n",count);"
*/
void check_network(setType s,int n){
    int i,count=0;
    for(i=0;i<n;i++){
        if(s[i]<0){
            count++;
        }
    }
    if(count==1){
        printf("The network is connected.\n");
    }else{
        printf("There are %d components.\n",count);
    }
}

int main(){
    setType s;
    int n;
    char in;
    scanf("%d",&n);
    getchar();
    initializeCollection(s,n);
    do{
        scanf("%c",&in);
        //putchar(in);
        switch(in){
            case 'I':input_connection(s);break;
            case 'C':check_connection(s);break;
            case 'S':check_network(s,n);break;
        }
    }while(in!='S');
    return 0;
}
