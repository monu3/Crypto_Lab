#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LENGTH 100

struct Vigenere {
    char key[MAX_LENGTH];
};

void initialize(struct Vigenere* cipher, const char* key) {
    int j = 0;
    for (int i = 0; key[i] != '\0'; ++i) {
        if (key[i] >= 'A' && key[i] <= 'Z')
            cipher->key[j++] = key[i];
        else if (key[i] >= 'a' && key[i] <= 'z')
            cipher->key[j++] = key[i] + 'A' - 'a';
    }
    cipher->key[j] = '\0';
}

void encrypt(struct Vigenere* cipher, const char* text, char* out) {
    int j = 0;
    for (int i = 0; text[i] != '\0'; ++i) {
        char c = text[i];
        if (c >= 'a' && c <= 'z')
            c += 'A' - 'a';
        else if (c < 'A' || c > 'Z')
            continue;
        out[i] = (c + cipher->key[j] - 2 * 'A') % 26 + 'A';
        j = (j + 1) % strlen(cipher->key);
    }
    out[strlen(text)] = '\0';
}

void decrypt(struct Vigenere* cipher, const char* text, char* out) {
    int j = 0;
    for (int i = 0; text[i] != '\0'; ++i) {
        char c = text[i];
        if (c >= 'a' && c <= 'z')
            c += 'A' - 'a';
        else if (c < 'A' || c > 'Z')
            continue;
        out[i] = (c - cipher->key[j] + 26) % 26 + 'A';
        j = (j + 1) % strlen(cipher->key);
    }
    out[strlen(text)] = '\0';
}

int main() {
    struct Vigenere cipher;
    char key[MAX_LENGTH];
    char original[MAX_LENGTH];
    char encrypted[MAX_LENGTH];
    char decrypted[MAX_LENGTH];

    printf("*********Vigener-ciper********");

    printf("Enter the key: ");
    fgets(key, MAX_LENGTH, stdin);
    key[strcspn(key, "\n")] = '\0';  // Remove the newline character

    initialize(&cipher, key);

    printf("Enter the message: ");
    fgets(original, MAX_LENGTH, stdin);
    original[strcspn(original, "\n")] = '\0';  // Remove the newline character

    encrypt(&cipher, original, encrypted);
    decrypt(&cipher, encrypted, decrypted);

    printf("Message: %s\n\n", original);
    printf("Encrypted Message : %s\n\n", encrypted);
    printf("Decrypted Message: %s\n\n", decrypted);

    return 0;
}
