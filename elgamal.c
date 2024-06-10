#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// Function to calculate gcd of two numbers
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Function to perform modular exponentiation
long long mod_exp(long long base, long long exp, long long mod) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

int main() {
    long long p, g, a, k, M;

    // User inputs

    printf("\n********    Elgamal algorithm ********* \n");
    
    printf("Enter a prime number p: ");
    scanf("%lld", &p);
    printf("Enter a primitive root g: ");
    scanf("%lld", &g);
    printf("Enter Bob's private key a: ");
    scanf("%lld", &a);
    printf("Enter the random integer k: ");
    scanf("%lld", &k);
    printf("Enter the message M to encrypt (integer): ");
    scanf("%lld", &M);

    // Check if gcd(k, p-1) = 1
    if (gcd(k, p-1) != 1) {
        printf("k is not coprime with p-1, choose another k.\n");
        return -1;
    }

    // Bob's public key
    long long h = mod_exp(g, a, p);
    printf("Bob's public key: (p, g, h) = (%lld, %lld, %lld)\n", p, g, h);

    // Alice encrypts the message
    long long p_enc = mod_exp(g, k, p);      // p = g^k mod p
    long long s = mod_exp(h, k, p);          // s = h^k mod p
    long long encrypted_message = (M * s) % p;  // M * s mod p

    printf("Encrypted message: (p_enc, encrypted_message) = (%lld, %lld)\n", p_enc, encrypted_message);

    // Bob decrypts the message
    long long s_prime = mod_exp(p_enc, a, p);  // s' = p^a mod p
    long long decrypted_message = (encrypted_message * mod_exp(s_prime, p-2, p)) % p; // M = (M * s) / s'

    printf("Decrypted message: %lld\n", decrypted_message);

    return 0;
}
