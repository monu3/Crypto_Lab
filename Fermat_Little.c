#include <stdio.h>
#include <math.h>
int power_mod(int x, unsigned int y, int p) {
    int result = 1; // Initialize result
    x = x % p; // Update x if it is more than or equal to p
    while (y > 0) {
        // If y is odd, multiply x with the result
        if (y & 1)
            result = (result * x) % p;
        y = y >> 1; // y = y/2  // y must be even now
        x = (x * x) % p; // Change x to x^2
    }
    return result;
}
int main() {
    int n, a;
    printf("\n*******  Fermat's Little Algorithm ******\n");
    printf("Enter a prime number (n): ");
    scanf("%d", &n);

    printf("Enter a number (a) such that 1 < a < %d: ", n-1);
    scanf("%d", &a);
    // Fermat's Little Theorem test
    if (a <= 1 || a >= n-1) {
        printf("Invalid input: 1 < a < %d\n", n-1);
        return 1;
    }
    int result = power_mod(a, n-1, n);
    if (result == 1)
        printf("Fermat's Little Theorem holds: %d^(%d-1) ≡ 1 (mod %d)\n", a, n, n);
    else
        printf("Fermat's Little Theorem does not hold: %d^(%d-1) ≡ %d (mod %d)\n", a, n, result, n);
    return 0;
}
