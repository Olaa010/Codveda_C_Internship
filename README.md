# Codveda C/C++ Development Internship - Complete Solution

This repository contains solutions for ALL tasks across 3 levels. 
As per instructions: you need to complete ANY 2 tasks per level.

## Structure

```
Codveda_C_Internship/
├── Level1_Basic/
│   ├── calculator.c            -> Task 1: Basic Calculator
│   ├── guessing_game.c         -> Task 2: Number Guessing Game
│   └── string_manipulation.c   -> Task 3: String Manipulation
├── Level2_Intermediate/
│   ├── student_management.c    -> Task 1: Student Management System
│   ├── sorting_searching.c     -> Task 2: Sorting and Searching Algorithms
│   └── data_structures.c       -> Task 3: Stack & Queue Implementation
└── Level3_Advanced/
    ├── file_system_sim.c       -> Task 1: Simple File System Simulation
    ├── producer_consumer.c     -> Task 2: Multithreaded Producer-Consumer (pthread)
    └── tic_tac_toe.c           -> Task 3: Tic-Tac-Toe Game
```

## Compilation

### Linux / WSL / macOS (gcc required)

```bash
# Level 1
gcc Level1_Basic/calculator.c -o calculator
./calculator

gcc Level1_Basic/guessing_game.c -o guess
./guess

gcc Level1_Basic/string_manipulation.c -o strings
./strings

# Level 2
gcc Level2_Intermediate/student_management.c -o student_mgmt
./student_mgmt

gcc Level2_Intermediate/sorting_searching.c -o sort_search
./sort_search

gcc Level2_Intermediate/data_structures.c -o ds
./ds

# Level 3
gcc Level3_Advanced/file_system_sim.c -o fs_sim
./fs_sim

# Note -lpthread needed for producer-consumer
gcc Level3_Advanced/producer_consumer.c -o prod_cons -lpthread
./prod_cons

gcc Level3_Advanced/tic_tac_toe.c -o tictactoe
./tictactoe
```

### Windows (MinGW)

Same commands, but use .exe output.

## Task Details Covered

### Level 1 - Basic

1. **Calculator**: I/O, switch-case, division-by-zero handling
2. **Guessing Game**: rand()/srand(), loops, high/low feedback
3. **String**: Custom reverse, vowel count, palindrome with tolower/isalnum

### Level 2 - Intermediate

1. **Student Management**: struct, file I/O binary save/load, CRUD menu
2. **Sorting/Searching**: Bubble O(n^2), Quick O(n log n), Linear O(n), Binary O(log n), time comparison with clock()
3. **Data Structures**: Stack push/pop/display + Queue enqueue/dequeue/display via Linked List + malloc/free

### Level 3 - Advanced

1. **File System**: Simulated FS with meta file, create/read/write/delete/list, error handling
2. **Producer-Consumer**: pthreads, mutex, cond vars (not_full, not_empty), circular buffer
3. **Tic-Tac-Toe**: 2-player, board display, win check (rows/cols/diags), draw detection, input validation

## Internship Submission Checklist (from PDF)

- Complete 2 tasks per level (you have all 8 ready)
- Create GitHub repo and push code
- Record explanation video
- Post on LinkedIn, tag @Codveda, use #CodvedaJourney #CodvedaExperience #FutureWithCodveda #CodvedaProjects #CodvedaAchievements
- Submit via Codveda submission form within 1 month
- Include Offer Letter

All codes are in C (compiles as C++ too) and follow the exact objectives listed in CC_Development_Task_List.pdf

Author: Solution generated for Chibobo
Date: July 2026