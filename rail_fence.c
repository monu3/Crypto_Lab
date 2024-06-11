#include <stdio.h>
#include <string.h>
#include <stdbool.h>
void encryptRailFence(char *text, int key, char *result) {
    int len = strlen(text);
    char rail[key][len];
    for (int i = 0; i < key; i++)
        for (int j = 0; j < len; j++)
            rail[i][j] = '\n';
    // to find the direction
    bool dir_down = false;
    int row = 0, col = 0;
    for (int i = 0; i < len; i++) {
        if (row == 0 || row == key - 1)     
            dir_down = !dir_down;
        // fill the corresponding alphabet
        rail[row][col++] = text[i];
        // find the next row using direction flag
        dir_down ? row++ : row--;
    }
    int k = 0;
    for (int i = 0; i < key; i++)
        for (int j = 0; j < len; j++)
            if (rail[i][j] != '\n')
                result[k++] = rail[i][j];
    result[k] = '\0';
}
void decryptRailFence(char *cipher, int key, char *result) {
    int len = strlen(cipher);
    char rail[key][len];
    for (int i = 0; i < key; i++)
        for (int j = 0; j < len; j++)
            rail[i][j] = '\n';
    // to find the direction
    bool dir_down;
    int row = 0, col = 0;
    for (int i = 0; i < len; i++) {    // mark the places with '*'
        if (row == 0)
            dir_down = true;
        if (row == key - 1)
            dir_down = false;
        rail[row][col++] = '*';
        dir_down ? row++ : row--;
    }
    int index = 0;
    for (int i = 0; i < key; i++)
        for (int j = 0; j < len; j++)
            if (rail[i][j] == '*' && index < len)
                rail[i][j] = cipher[index++];
    // now read the matrix in zig-zag manner to construct the resultant text
    row = 0, col = 0;
    for (int i = 0; i < len; i++) {
        if (row == 0)
            dir_down = true;
        if (row == key - 1)
            dir_down = false;

        if (rail[row][col] != '*')
            result[i] = rail[row][col++];

        dir_down ? row++ : row--;
    }
    result[len] = '\0';
}

int main() {
    char text[100], result[100];
    int key;
    printf("\n******* Rail Fence Ciper  ********* \n");

    printf("\nEnter the message : ");
    fgets(text, 100, stdin);
    text[strcspn(text, "\n")] = '\0'; // Remove newline character

    printf("Enter the no. of rails: ");
    scanf("%d", &key);

    encryptRailFence(text, key, result);
    printf("Encrypted Message : %s\n", result);

    char encrypted_text[100];
    strcpy(encrypted_text, result); // Save the encrypted text for decryption

    decryptRailFence(encrypted_text, key, result);
    printf("Decrypted Message : %s\n", result);

    return 0;
}
