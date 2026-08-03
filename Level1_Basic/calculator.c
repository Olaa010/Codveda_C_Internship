#include <stdio.h>
#include <stdlib.h>

int main() {
    double num1, num2, result;
    char op;
    char cont = 'y';

    printf("=== Basic Calculator - Codveda Level 1 Task 1 ===\n");

    while (cont == 'y' || cont == 'Y') {
        printf("\nEnter expression (e.g., 5 + 3): ");
        if (scanf(" %lf %c %lf", &num1, &op, &num2) != 3) {
            printf("Invalid input! Please use format: number operator number\n");
            while (getchar() != '\n');
            continue;
        }

        switch (op) {
            case '+':
                result = num1 + num2;
                printf("Result: %.2lf + %.2lf = %.2lf\n", num1, num2, result);
                break;
            case '-':
                result = num1 - num2;
                printf("Result: %.2lf - %.2lf = %.2lf\n", num1, num2, result);
                break;
            case '*':
                result = num1 * num2;
                printf("Result: %.2lf * %.2lf = %.2lf\n", num1, num2, result);
                break;
            case '/':
                if (num2 == 0) {
                    printf("Error: Division by zero is not allowed!\n");
                } else {
                    result = num1 / num2;
                    printf("Result: %.2lf / %.2lf = %.2lf\n", num1, num2, result);
                }
                break;
            default:
                printf("Error: Invalid operator! Use + - * /\n");
        }

        printf("\nDo you want to continue? (y/n): ");
        scanf(" %c", &cont);
    }

    printf("Calculator exited. Thank you!\n");
    return 0;
}
