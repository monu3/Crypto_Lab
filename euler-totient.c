#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int isPrime(int n) {
    if (n <= 1) return 0; // 0 and 1 are not prime numbers

    for (int i = 2; i <= n / 2; ++i) {
        if (n % i == 0) {
            return 0; // Not a prime number
        }
    }
    return 1; // Prime number
}

void generatePrimeFactors(int n, int *prime1, int *prime2) {
    for (int i = 2; i <= n / 2; ++i) {
        if (n % i == 0 && isPrime(i)) {
            *prime1 = i;
            break;
        }
    }

    for (int i = n / 2; i >= 2; --i) {
        if (n % i == 0 && isPrime(i)) {
            *prime2 = i;
            break;
        }
    }
}

int main() {
    int n;
    printf("Enter any positive integer (n) greater than 1: ");
    scanf("%d", &n);

    if (isPrime(n)) {
        printf("The number %d is a prime number.\n", n);
        printf("Result: %d\n", n - 1);
    } else {
        int prime1 = 0, prime2 = 0;
        generatePrimeFactors(n, &prime1, &prime2);

        if (prime1 != 0 && prime2 != 0) {
            int result = (prime1 - 1) * (prime2 - 1);
            printf("The number %d is not a prime number.\n", n);
            printf("Prime factors are: %d and %d\n", prime1, prime2);
            printf("Result: (%d - 1) * (%d - 1) = %d\n", prime1, prime2, result);
        } else {
            printf("Error: Could not find two prime factors.\n");
        }
    }

    return 0;
}