#include <stdio.h>
#include <stdint.h>
#include <string.h>
// Number of rounds
#define NUM_ROUNDS 16
// Permutation tables (PC1 and PC2) - Actual tables
int PC1[56] = {
        57, 49, 41, 33, 25, 17, 9,
        1,  58, 50, 42, 34, 26, 18,
        10, 2,  59, 51, 43, 35, 27,
        19, 11, 3,  60, 52, 44, 36,
        63, 55, 47, 39, 31, 23, 15,
        7,  62, 54, 46, 38, 30, 22,
        14, 6,  61, 53, 45, 37, 29,
        21, 13, 5,  28, 20, 12, 4
};

int PC2[48] = {
        14, 17, 11, 24, 1,  5,
        3,  28, 15, 6,  21, 10,
        23, 19, 12, 4,  26, 8,
        16, 7,  27, 20, 13, 2,
        41, 52, 31, 37, 47, 55,
        30, 40, 51, 45, 33, 48,
        44, 49, 39, 56, 34, 53,
        46, 42, 50, 36, 29, 32
};

// Key schedule left rotation values
int KEY_shift[NUM_ROUNDS] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

// Function to perform permutation based on table
uint64_t permutation(uint64_t input, const int *table, int n) {
    uint64_t output = 0;
    for (int i = 0; i < n; i++) {
        output <<= 1;
        output |= (input >> (64 - table[i])) & 0x01;
    }
    return output;
}

// Function to generate keys
void generate_keys(uint64_t key, uint64_t keys[NUM_ROUNDS]) {
    // Apply PC1 (64 bits to 56 bits)
    key = permutation(key, PC1, 56);
    uint32_t left = (key >> 28) & 0xFFFFFFF;
    uint32_t right = key & 0xFFFFFFF;

    // Generate 16 subkeys
    for (int i = 0; i < NUM_ROUNDS; i++) {
        // Left rotate
        left = ((left << KEY_shift[i]) | (left >> (28 - KEY_shift[i]))) & 0xFFFFFFF;
        right = ((right << KEY_shift[i]) | (right >> (28 - KEY_shift[i]))) & 0xFFFFFFF;

        // Combine left and right halves
        uint64_t concat = ((uint64_t)left << 28) | right;

        // Apply PC2 (56 bits to 48 bits)
        keys[i] = permutation(concat, PC2, 48);
    }
}

// Function to print a 48-bit key in binary
void print_key_binary(uint64_t key) {
    for (int i = 47; i >= 0; i--) {
        printf("%d", (key >> i) & 0x01);
    }
    printf("\n");
}

int main() {
    char key_input[65];
    uint64_t key = 0;
    uint64_t keys[NUM_ROUNDS];


    printf("\n*******   DES ********\n");
    // User input for 64-bit binary key
    printf("Enter a 64-bit key in binary : ");
    scanf("%64s", key_input);

    // Convert binary string to uint64_t
    for (int i = 0; i < 64; i++) {
        key <<= 1;
        if (key_input[i] == '1') {
            key |= 1;
        }
    }

    // Generate subkeys
    generate_keys(key, keys);

    // Print all 16 subkeys in binary
    printf("Generated subkeys:\n");
    for (int i = 0; i < NUM_ROUNDS; i++) {
        printf("Subkey %2d: ", i + 1);
        print_key_binary(keys[i]);
    }

    return 0;
}