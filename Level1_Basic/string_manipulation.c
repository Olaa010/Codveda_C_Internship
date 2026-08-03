#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_LEN 1000

void reverseString(char *str, char *rev) {
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        rev[i] = str[len - 1 - i];
    }
    rev[len] = '\0';
}

int countVowels(char *str) {
    int count = 0;
    for (int i = 0; str[i]; i++) {
        char c = tolower(str[i]);
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
            count++;
    }
    return count;
}

int countConsonants(char *str) {
    int count = 0;
    for (int i = 0; str[i]; i++) {
        if (isalpha(str[i])) {
            char c = tolower(str[i]);
            if (!(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'))
                count++;
        }
    }
    return count;
}

bool isPalindrome(char *str) {
    // case-insensitive, ignore spaces
    int left = 0, right = strlen(str) - 1;
    while (left < right) {
        while (left < right && !isalnum(str[left])) left++;
        while (left < right && !isalnum(str[right])) right--;
        if (tolower(str[left]) != tolower(str[right]))
            return false;
        left++; right--;
    }
    return true;
}

int main() {
    char input[MAX_LEN];
    char reversed[MAX_LEN];
    int choice;

    printf("=== String Manipulation - Codveda Level 1 Task 3 ===\n");
    printf("Enter a string: ");
    fgets(input, MAX_LEN, stdin);
    input[strcspn(input, "\n")] = '\0'; // remove newline

    do {
        printf("\n--- MENU ---\n");
        printf("1. Reverse string\n");
        printf("2. Count vowels\n");
        printf("3. Count consonants\n");
        printf("4. Check palindrome\n");
        printf("5. Enter new string\n");
        printf("6. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);
        while (getchar() != '\n');

        switch (choice) {
            case 1:
                reverseString(input, reversed);
                printf("Original: %s\nReversed: %s\n", input, reversed);
                break;
            case 2:
                printf("Vowels: %d\n", countVowels(input));
                break;
            case 3:
                printf("Consonants: %d\n", countConsonants(input));
                break;
            case 4:
                if (isPalindrome(input))
                    printf("'%s' IS a palindrome.\n", input);
                else
                    printf("'%s' is NOT a palindrome.\n", input);
                break;
            case 5:
                printf("Enter new string: ");
                fgets(input, MAX_LEN, stdin);
                input[strcspn(input, "\n")] = '\0';
                break;
            case 6:
                printf("Exiting.\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 6);

    return 0;
}
