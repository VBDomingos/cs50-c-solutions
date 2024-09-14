#include <stdio.h>
#include <ctype.h>

int computeScore(char word[]) {
    int points[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
    int score = 0;
    int i = 0;

    while (word[i] != '\0') {
        if (isalpha(word[i])) {
            int letterIndex = toupper(word[i]) - 'A';
            score += points[letterIndex];
        }
        i++;
    }

    return score;
}

int main(void) {
    char player1Word[100];
    char player2Word[100];

    printf("Player 1: ");
    scanf("%s", player1Word);

    printf("Player 2: ");
    scanf("%s", player2Word);

    int player1Score = computeScore(player1Word);
    int player2Score = computeScore(player2Word);

    if (player1Score > player2Score) {
        printf("Player 1 wins!\n");
    }
    else if (player2Score > player1Score) {
        printf("Player 2 wins!\n");
    }
    else {
        printf("Tie!\n");
    }
}
