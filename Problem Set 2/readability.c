#include <stdio.h>
#include <ctype.h>
#include <math.h>

int countLetters(char text[]) {
    int count = 0;
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            count++;
        }
    }
    return count;
}

int countWords(char text[]) {
    int count = 0;
    int inWord = 0;

    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            if (!inWord) {
                inWord = 1;
                count++;
            }
        } else {
            inWord = 0;
        }
    }

    return count;
}

int countSentences(char text[]) {
    int count = 0;
    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?') {
            count++;
        }
    }
    return count;
}

int main(void) {
    char text[1000];
    
    printf("Text: ");
    fgets(text, sizeof(text), stdin);

    int letters = countLetters(text);
    int words = countWords(text);
    int sentences = countSentences(text);

    float L = (letters / (float) words) * 100;
    float S = (sentences / (float) words) * 100;

    float index = 0.0588 * L - 0.296 * S - 15.8;
    int grade = round(index);

    if (grade < 1) {
        printf("Before Grade 1\n");
    }
    else if (grade >= 16) {
        printf("Grade 16+\n");
    }
    else {
        printf("Grade %d\n", grade);
    }

    return 0;
}