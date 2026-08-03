#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int secret, guess, attempts = 0;
    int max_attempts = 10;
    int lower = 1, upper = 100;
    char playAgain = 'y';

    srand(time(0));
    printf("=== Number Guessing Game - Codveda Level 1 Task 2 ===\n");
    printf("Guess the number between %d and %d\n", lower, upper);

    while (playAgain == 'y' || playAgain == 'Y') {
        secret = (rand() % (upper - lower + 1)) + lower;
        attempts = 0;
        printf("\nNew game started! You have %d attempts.\n", max_attempts);

        while (attempts < max_attempts) {
            printf("Attempt %d/%d - Enter your guess: ", attempts + 1, max_attempts);
            if (scanf("%d", &guess) != 1) {
                printf("Invalid input! Enter a number.\n");
                while (getchar() != '\n');
                continue;
            }
            attempts++;

            if (guess == secret) {
                printf("Congratulations! You guessed %d correctly in %d attempts!\n", secret, attempts);
                break;
            } else if (guess < secret) {
                printf("Too low! Try higher.\n");
            } else {
                printf("Too high! Try lower.\n");
            }

            if (attempts == max_attempts) {
                printf("Game Over! The number was %d\n", secret);
            }
        }

        printf("Play again? (y/n): ");
        scanf(" %c", &playAgain);
    }

    printf("Thanks for playing!\n");
    return 0;
}
