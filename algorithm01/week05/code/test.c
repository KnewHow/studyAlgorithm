#include<stdio.h>

int fun1(int score){
    int grade;
    if(score<60){
        grade=1;
    }else if(grade<70){
        grade=2;
    }else if(grade<80){
        grade=3;
    }else if(grade<90){
        grade=4;
    }else{
        grade=5;
    }
    return grade;
}

int fun2(int score){
     int grade;
     if(score<80){
       if(score<70){
            if(score<60){
                grade=1;
            }else{
                grade=2;
            }
       }else{
            grade=3;
       }
     }else{
         if(score<90){
            grade=4;
         }else{
            grade=5;
         }
     }

}

int main(){
    printf("just test");
    return 0;
}
