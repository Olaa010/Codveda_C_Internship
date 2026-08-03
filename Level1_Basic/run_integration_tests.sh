#!/bin/bash
# Integration tests for string_manipulation interactive program
set -e
cd "$(dirname "$0")"
gcc -Wall -Wextra -o string_manipulation string_manipulation.c

pass=0
fail=0

check() {
    local name="$1"
    local input="$2"
    local expect="$3"
    local out
    out=$(printf '%s' "$input" | ./string_manipulation 2>&1)
    if echo "$out" | grep -qF "$expect"; then
        echo "  PASS: $name"
        ((pass++)) || true
    else
        echo "  FAIL: $name"
        echo "    Expected substring: $expect"
        echo "    Got output:"
        echo "$out" | tail -20
        ((fail++)) || true
    fi
}

echo "========================================"
echo " STRING MANIPULATION - INTEGRATION TESTS"
echo "========================================"
echo ""

check "reverse string"        $'hello\n1\n6\n'           "Reversed: olleh"
check "count vowels"          $'hello\n2\n6\n'           "Vowels: 2"
check "count consonants"      $'hello\n3\n6\n'           "Consonants: 3"
check "palindrome yes"        $'Racecar\n4\n6\n'         "IS a palindrome"
check "palindrome no"         $'hello\n4\n6\n'           "is NOT a palindrome"
check "phrase palindrome"     $'A man a plan a canal Panama\n4\n6\n' "IS a palindrome"
check "invalid menu choice"   $'test\n99\n6\n'            "Invalid choice"
check "new string (case 5)"   $'old\n5\nnew\n1\n6\n'     "Original: new"

echo ""
echo "Integration: $pass passed, $fail failed"
exit "$fail"
