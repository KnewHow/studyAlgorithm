#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 100
typedef int elementType;

/*collection data constructor
we use the array of this to express collection.
The root element's parent is -1
the ordinary element parent is the index of parent.
*/
typedef struct node{
    elementType data;
    int parent;
}coll,*pCollection;



/*
find the collection's root element by the element needed to find.
@param s[] The arrar yto store collections elememts
@param element The element will be searched in the array
@return The index of root element of which the element be found,-1 will be return if the
element not be found in this collection
*/
int find(coll s[],elementType element){
    int i;
    for(i=0;i<MAXSIZE&&s[i].data!=element;i++);
    if(i>=MAXSIZE){/*在数组中没有找到该元素*/
        return -1;
    }
    for(;s[i].parent>=0;i=s[i].parent);
    return i;
}


/*
unoin two collection by the two element in the two collection.
@param s[] the array to store collection element
@param x1 The element in collection one.
@param x2 The element in the collection two
*/
void unionCollection(coll s[],elementType x1,elementType x2){
    int root1 = find(s,x1);
    int root2 = find(s,x2);
    if(root1!=root2){
        s[root2].parent=root1;
    }
}

/*
unoin two collection by the two element in the two collection,and the smaller collection
will be union bigger collection.
@param s[] the array to store collection element
@param x1 The element in collection one.
@param x2 The element in the collection two
*/
void unionCollection2(coll s[],elementType x1,elementType x2){
    int root1 = find(s,x1);
    int root2 = find(s,x2);
    if(s[root1].parent<s[root2].parent){
        s[root2].parent=root1;
    }else{
         s[root1].parent=root2;
    }
}



int main(){
    printf("just test");
    return 0;
}
