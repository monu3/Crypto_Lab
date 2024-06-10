//RSA algor
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
// Function to compute the greatest common divisor
int gcd(int a, int b) 
{
    while (b != 0) 
	{
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
long long mod_pow(long long base, long long exponent, long long mod) {
    long long result = 1;
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exponent /= 2;
    }
    return result;
}

// Extended Euclidean Algorithm to find the modular multiplicative inverse
long long mod_inverse(long long a, long long m) {
    long long m0 = m, t, q;
    long long x0 = 0, x1 = 1;

    if (m == 1)
        return 0;

    while (a > 1) {
        // q is quotient
        q = a / m;
        t = m;

        // m is remainder now, process same as Euclid's algo
        m = a % m;
        a = t;
        t = x0;

        x0 = x1 - q * x0;
        x1 = t;
    }

    // Make x1 positive
    if (x1 < 0)
        x1 += m0;

    return x1;
}

// Function to check if a number is prime
int is_prime(int num) {
    if (num <= 1) return 0;
    if (num <= 3) return 1;
    if (num % 2 == 0 || num % 3 == 0) return 0;
    for (int i = 5; i * i <= num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0) return 0;
    }
    return 1;
}

int main() 
{
	printf("*******  RSA Algorithm  *****:\n");
    int p, q;
    printf("\nEnter two large prime numbers p and q: ");
    scanf("%d %d", &p, &q);

    if (!is_prime(p) || !is_prime(q)) {
        printf("Both numbers must be prime.\n");
        return 1;
    }

    long long n = (long long)p * q;
    long long phi = (long long)(p - 1) * (q - 1);

    long long e;
    printf("\nEnter a number e (1 < e < %lld) such that gcd(e, %lld) = 1: ", phi, phi);
    scanf("%lld", &e);

    if (gcd(e, phi) != 1) {
        printf("e is not relatively prime to %lld.\n", phi);
        return 1;
    }

    long long d = mod_inverse(e, phi);
    if (d == 0) {
        printf("Error computing modular inverse.\n");
        return 1;
    }

    printf("Public key: (%lld, %lld)\n", e, n);
    printf("Private key: (%lld, %lld)\n", d, n);
    printf("Euler's Totient value: %lld\n", phi);

    char message[256];
    printf("\nEnter a message to encrypt (uppercase A-Z only): ");
    getchar(); // To consume the newline left by scanf
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0'; // Remove the newline character

    // Convert the message to uppercase
    for (int i = 0; i < strlen(message); i++) {
        message[i] = toupper(message[i]);
    }
    printf("Encryption formula: M^e mod n \n");

    printf("Original message: %s\n", message);
    printf("Character values: ");
    for (int i = 0; i < strlen(message); i++) {
        if (message[i] >= 'A' && message[i] <= 'Z') {
            printf("%d ", message[i] - 'A');
        }
    }
    printf("\n");

    // Encrypting each character
    long long encrypted[strlen(message)];
    for (int i = 0; i < strlen(message); i++) {
        if (message[i] >= 'A' && message[i] <= 'Z') {
            int m = message[i] - 'A';
            encrypted[i] = mod_pow(m, e, n);
            printf("Encryption formula for '%c': %d^%lld mod %lld = %lld\n", message[i], m, e, n, encrypted[i]);
        } else {
            encrypted[i] = -1; // Mark non-alphabetic characters
        }
    }

    // Save encrypted message to a file
    FILE *file = fopen("encrypted_message.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return 1;
    }
    printf("Encrypted message: ");
    for (int i = 0; i < strlen(message); i++) {
        if (encrypted[i] != -1) {
            fprintf(file, "%lld ", encrypted[i]);
            printf("%lld ", encrypted[i]);
        } else {
            fprintf(file, "? ");
            printf("? ");
        }
    }
	    fprintf(file, "\n");
    fclose(file);
   printf("\nEncrypted message saved to encrypted_message.txt\n");

    // Convert encrypted numeric values to A-Z
    printf("\nEncrypted message in A-Z: ");
    for (int i = 0; i < strlen(message); i++) {
        if (encrypted[i] != -1) {
            printf("%c ", (char)((encrypted[i] % 26) + 'A'));
        } else {
            printf("? ");
        }
    }
    printf("\n");

    printf("Decryption formula: c^d mod n\n");

    // Read encrypted message from the file
    file = fopen("encrypted_message.txt", "r");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return 1;
    }

    long long decrypted_values[strlen(message)];
    for (int i = 0; i < strlen(message); i++) {
        if (fscanf(file, "%lld", &decrypted_values[i]) != 1) {
            decrypted_values[i] = -1;
        }
    }
    fclose(file);

    // Decrypting each character
    char decrypted[strlen(message) + 1];
    for (int i = 0; i < strlen(message); i++) {
        if (decrypted_values[i] != -1) {
            long long c = decrypted_values[i];
            long long decrypted_value = mod_pow(c, d, n);
            decrypted[i] = (char)(decrypted_value + 'A');
            printf("Decryption formula for '%lld': %lld^%lld mod %lld = %lld, which is '%c'\n", c, c, d, n, decrypted_value, decrypted[i]);
        } else {
            decrypted[i] = message[i]; // Preserve non-alphabetic characters
        }
    }
    decrypted[strlen(message)] = '\0';

    printf("\nDecrypted message: %s\n", decrypted);

    return 0;
}
