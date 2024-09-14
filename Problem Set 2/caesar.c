#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void encryptText(char text[], int key);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ./caesar key\n");
        return;
    }

    for (int i = 0; argv[1][i] != '\0'; i++) {
        if (!isdigit(argv[1][i])) {
            printf("Usage: ./caesar key\n");
            return;
        }
    }

    int key = atoi(argv[1]);

    char plaintext[1000];
    printf("plaintext:  ");
    fgets(plaintext, sizeof(plaintext), stdin);

    printf("ciphertext: ");
    encryptText(plaintext, key);
    printf("\n");
}

void encryptText(char text[], int key) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            char offset = islower(text[i]) ? 'a' : 'A';
            char encryptedChar = (text[i] - offset + key) % 26 + offset;
            printf("%c", encryptedChar);
        } else {
            printf("%c", text[i]);
        }
    }
}
