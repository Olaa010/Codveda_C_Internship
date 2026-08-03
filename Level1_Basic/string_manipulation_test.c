/* Automated output + performance tests for string_manipulation.c */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

#define MAX_LEN 1000
#define ITERATIONS 500000

void reverseString(char *str, char *rev) {
    int len = strlen(str);
    for (int i = 0; i < len; i++)
        rev[i] = str[len - 1 - i];
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
    int left = 0, right = (int)strlen(str) - 1;
    while (left < right) {
        while (left < right && !isalnum(str[left])) left++;
        while (left < right && !isalnum(str[right])) right--;
        if (tolower(str[left]) != tolower(str[right]))
            return false;
        left++;
        right--;
    }
    return true;
}

static int tests_run = 0;
static int tests_passed = 0;

#define ASSERT(cond, msg) do { \
    tests_run++; \
    if (cond) { tests_passed++; } \
    else { printf("  FAIL: %s\n", msg); } \
} while (0)

static double bench(void (*fn)(void), const char *name) {
    clock_t start = clock();
    for (int i = 0; i < ITERATIONS; i++)
        fn();
    double ms = (double)(clock() - start) * 1000.0 / CLOCKS_PER_SEC;
    printf("  %-22s %8.2f ms  (%d iters, %.0f ops/sec)\n",
           name, ms, ITERATIONS, ITERATIONS / (ms / 1000.0));
    return ms;
}

static char long_str[MAX_LEN];
static char rev_buf[MAX_LEN];

static void bench_reverse(void) {
    reverseString(long_str, rev_buf);
}

static void bench_vowels(void) {
    volatile int v = countVowels(long_str);
    (void)v;
}

static void bench_consonants(void) {
    volatile int c = countConsonants(long_str);
    (void)c;
}

static void bench_palindrome(void) {
    volatile bool p = isPalindrome(long_str);
    (void)p;
}

int main(void) {
    char rev[MAX_LEN];

    printf("========================================\n");
    printf(" STRING MANIPULATION - OUTPUT TESTS\n");
    printf("========================================\n\n");

    reverseString("hello", rev);
    ASSERT(strcmp(rev, "olleh") == 0, "reverse 'hello' -> 'olleh'");
    reverseString("", rev);
    ASSERT(strcmp(rev, "") == 0, "reverse empty string");
    reverseString("a", rev);
    ASSERT(strcmp(rev, "a") == 0, "reverse single char");
    reverseString("12345", rev);
    ASSERT(strcmp(rev, "54321") == 0, "reverse digits");

    ASSERT(countVowels("hello") == 2, "vowels in 'hello' = 2");
    ASSERT(countVowels("AEIOU") == 5, "vowels in 'AEIOU' = 5");
    ASSERT(countVowels("xyz") == 0, "vowels in 'xyz' = 0");
    ASSERT(countVowels("") == 0, "vowels in empty = 0");
    ASSERT(countVowels("hello123") == 2, "vowels ignore digits");

    ASSERT(countConsonants("hello") == 3, "consonants in 'hello' = 3");
    ASSERT(countConsonants("aeiou") == 0, "consonants in 'aeiou' = 0");
    ASSERT(countConsonants("hello123") == 3, "consonants ignore digits");
    ASSERT(countConsonants("a b c") == 2, "consonants skip spaces (b, c)");

    ASSERT(isPalindrome("Racecar") == true, "'Racecar' is palindrome");
    ASSERT(isPalindrome("hello") == false, "'hello' not palindrome");
    ASSERT(isPalindrome("A man a plan a canal Panama") == true,
           "phrase palindrome with spaces");
    ASSERT(isPalindrome("") == true, "empty string is palindrome");
    ASSERT(isPalindrome("a") == true, "single char palindrome");
    ASSERT(isPalindrome("ab") == false, "'ab' not palindrome");

    printf("\nResults: %d / %d passed\n", tests_passed, tests_run);

    printf("\n========================================\n");
    printf(" STRING MANIPULATION - PERFORMANCE\n");
    printf(" (string length %d, %d iterations each)\n", MAX_LEN - 1, ITERATIONS);
    printf("========================================\n\n");

    memset(long_str, 'a', MAX_LEN - 1);
    long_str[0] = 'A';
    long_str[MAX_LEN / 2] = 'Z';
    long_str[MAX_LEN - 1] = '\0';

    double t1 = bench(bench_reverse, "reverseString");
    double t2 = bench(bench_vowels, "countVowels");
    double t3 = bench(bench_consonants, "countConsonants");
    double t4 = bench(bench_palindrome, "isPalindrome");

    printf("\n  Total benchmark time: %.2f ms\n", t1 + t2 + t3 + t4);
    printf("  Max input size (MAX_LEN): %d chars\n", MAX_LEN);

    return tests_passed == tests_run ? 0 : 1;
}
