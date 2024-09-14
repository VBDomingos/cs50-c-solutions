#include <stdio.h>

int main ()
{
    int height = 0;

    do
    {
        printf("Height: ");
        scanf("%d", &height);
    } while (height < 0 || height > 8);

    for (int i = height; i > 0; i--) {
        for (int j = i - 1; j > 0; j-- ) {
            printf(" ");
        }

        for (int k = i - 1; k < height; k++) {
            printf("#");
        }

        printf("\n");
    }
}