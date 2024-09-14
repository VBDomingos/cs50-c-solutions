#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

bool isValidKey(char *key);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    char *key = argv[1];

    if (!isValidKey(key)) {
        printf("Key must contain 26 unique alphabetic characters.\n");
        return 1;
    }

    char plaintext[256];
    printf("plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);

    printf("ciphertext: ");
    for (int i = 0, n = strlen(plaintext); i < n; i++) {
        char c = plaintext[i];
        if (isalpha(c)) {
            if (isupper(c)) {
                printf("%c", toupper(key[c - 'A']));
            } else {
                printf("%c", tolower(key[c - 'a']));
            }
        } else {
            printf("%c", c);
        }
    }
    printf("\n");

    return 0;
}

bool isValidKey(char *key) {
    if (strlen(key) != 26) {
        return false;
    }

    bool used[26] = {false};
    for (int i = 0; i < 26; i++) {
        if (!isalpha(key[i])) {
            return false;
        }
        int index = toupper(key[i]) - 'A';
        if (used[index]) {
            return false;
        }
        used[index] = true;
    }
    return true;
}
