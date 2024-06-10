#include <stdio.h>
#include <stdlib.h>

int mod_inverse(int num, int n) {
    int t = 0, newt = 1;
    int r = n, newr = num;
    while (newr != 0) {
        int quotient = r / newr;
        int temp = t;
        t = newt;
        newt = temp - quotient * newt;
        temp = r;
        r = newr;
        newr = temp - quotient * newr;
    }
    if (r > 1) {
        printf("num is not invertible\n");
        exit(1);
    }
    if (t < 0) {
        t = t + n;
    }
    return t;
}

int main() {
    int num, n;
    
    printf("\n****** Modulo Inverse ******\n");
    printf("Enter the number to find the inverse: ");
    scanf("%d", &num);
    
    printf("Enter the modulo value: ");
    scanf("%d", &n);
    
    int inverse = mod_inverse(num, n);
    
    printf("The modular inverse of %d mod %d is: %d\n", num, n, inverse);
    
    return 0;
}
