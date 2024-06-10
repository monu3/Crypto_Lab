#include <stdio.h>
#include <math.h>

int gcd(int a,int b){
    if(b==0){
        return a;
    } else
    {
        //printf("\n%d , %d \n",a,b);
        printf("\n%d = %d * %d + %d ",a,b,(a/b),((a-(b*(a/b)))));
        return gcd(b,a % b);
    }
}

int main(){

    int a,b;
    printf("\n*****  Euclidean Algorithm  ******\n");
    printf("Enter the value of a : ");
    scanf("%d",&a);
    printf("Enter the value of b : ");
    scanf("%d",&b);

    if(a<b){
        printf("The value of b is greater then a !!");
    }
    else if(gcd(a,b)==1 && a>b){
        printf("\n The %d and %d are a relatively prime and GCD is 1 .",a,b);
    }
    else if(a>b){
        printf("\nThe gcd of %d and %d is : %d\n",a,b,gcd(a,b));
    }


};