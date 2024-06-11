#include <stdio.h>
#include <string.h>

#define MAX_INPUT_LENGTH 16  // Maximum length of plaintext (16 characters for AES block size)

// Function to convert a character to its binary representation
void charToBinary(char c, char *binary) {
    for (int i = 7; i >= 0; --i) {
        binary[i] = (c & 1) ? '1' : '0';
        c >>= 1;
    }
    binary[8] = '\0';  // Null-terminate the string
}

// Function to pad a binary string to 128 bits
void padBinaryString(char *binaryString, int length) {
    for (int i = length; i < 128; ++i) {
        binaryString[i] = '0';
    }
    binaryString[128] = '\0';  // Null-terminate the string
}

// Function to convert plaintext to state array
void plaintextToStateArray(const char *plaintext, char stateArray[4][4][9]) {
    char binaryString[129] = "";  // To hold the 128-bit binary string
    char binary[9];  // To hold the binary representation of each character

    // Convert each character to binary and append to binaryString
    for (int i = 0; i < strlen(plaintext); ++i) {
        charToBinary(plaintext[i], binary);
        strcat(binaryString, binary);
    }

    // Pad binaryString to ensure it's 128 bits long
    padBinaryString(binaryString, strlen(binaryString));

    // Split the binaryString into 16 bytes (8 bits each)
    char bytes[16][9];
    for (int i = 0; i < 16; ++i) {
        strncpy(bytes[i], binaryString + i * 8, 8);
        bytes[i][8] = '\0';  // Null-terminate each byte string
    }

    // Form the 4x4 state array (column-major order)
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            strcpy(stateArray[row][col], bytes[row + 4 * col]);
        }
    }
}

int main() {
    char plaintext[MAX_INPUT_LENGTH + 1];  // Buffer for user input (+1 for null-terminator)
    char stateArray[4][4][9];  // 4x4 state array with 9-char strings for binary representations

    // Get user input
    printf("Enter plaintext (up to 16 characters): ");
    fgets(plaintext, sizeof(plaintext), stdin);

    // Remove newline character if present
    size_t length = strlen(plaintext);
    if (plaintext[length - 1] == '\n') {
        plaintext[length - 1] = '\0';
    }

    // Print ASCII values of the plaintext
    printf("ASCII values of plaintext:\n");
    for (int i = 0; i < length; ++i) {
        printf("%c: %d\n", plaintext[i], plaintext[i]);
    }

    // Convert plaintext to state array
    plaintextToStateArray(plaintext, stateArray);

    // Print the state array
    printf("State Array:\n");
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            printf("%s ", stateArray[row][col]);
        }
        printf("\n");
    }

    return 0;
}
