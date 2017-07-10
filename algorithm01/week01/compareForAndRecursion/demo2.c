#include<stdio.h>
#include<math.h>
#include<time.h>

#define MAXK 1e6
/*
you can get the question fromE:\project\java_algorithm\C_Algorithem\algorithm01\week01\compareForAndRecursion demo2.bmp
or from web:http://www.icourse163.org/learn/ZJU-93001?tid=1002019005#/learn/content?type=detail&id=1002635001&cid=1002891006
*/

/*
implement this question using violence loop
the T(n)=O(n^2);
*/
double fun1(double x,int n){
    double sum=1.0;
    int i;
    for(i=1;i<=100;i++){
        sum+=pow(x,i)/i;
    }
    return sum;
}

/*
we can store x^i into a temp, every time
we only need to multiply i base on last time value.
T(n)=2n
*/
double fun2(double x,int n){
    double sum=1.0;
    double temp=1;
    int i;
    for(i=1;i<100;i++){
        temp=temp*x;
        sum=sum+temp/i;
    }
    return sum;
}


/*Just a main method used to test*/
void main(){
    int i;
    //start the time,use the second
    clock_t start,end;
    double duration;//used to stored top - end
    start=clock();
    for(i=0;i<MAXK;i++){
        fun1(1.1,100);
    }
    end=clock();
    duration=((double)(end-start))/CLK_TCK/MAXK;
    printf("every method fun1 using average time:%f\n",duration);

    start=clock();
    for(i=0;i<MAXK;i++){
        fun2(1.1,100);
    }
    end=clock();
    duration=((double)(end-start))/CLK_TCK/MAXK;
    printf("every method fun2 using average time:%f\n",duration);

    /*
    summary:sometimes,you can using temporary variable to reduce the T(n)
    */
}




