#include <stdio.h>
#include <stdbool.h>

char board[3][3];

void initBoard(){
    for(int i=0;i<3;i++) for(int j=0;j<3;j++) board[i][j]=' ';
}

void displayBoard(){
    printf("\n");
    printf(" %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[2][0], board[2][1], board[2][2]);
    printf("\n");
}

bool checkWin(char player){
    // rows and cols
    for(int i=0;i<3;i++){
        if(board[i][0]==player && board[i][1]==player && board[i][2]==player) return true;
        if(board[0][i]==player && board[1][i]==player && board[2][i]==player) return true;
    }
    // diagonals
    if(board[0][0]==player && board[1][1]==player && board[2][2]==player) return true;
    if(board[0][2]==player && board[1][1]==player && board[2][0]==player) return true;
    return false;
}

bool checkDraw(){
    for(int i=0;i<3;i++) for(int j=0;j<3;j++) if(board[i][j]==' ') return false;
    return true;
}

int main(){
    printf("=== Tic-Tac-Toe - Level 3 Task 3 ===\n");
    printf("Players: X and O. Enter position 1-9 as below:\n");
    printf(" 1 | 2 | 3\n---|---|---\n 4 | 5 | 6\n---|---|---\n 7 | 8 | 9\n\n");

    char playAgain='y';
    while(playAgain=='y' || playAgain=='Y'){
        initBoard();
        char current='X';
        int move;
        bool gameOver=false;

        while(!gameOver){
            displayBoard();
            printf("Player %c turn. Enter position (1-9): ", current);
            if(scanf("%d",&move)!=1){
                printf("Invalid input! Enter number 1-9.\n");
                while(getchar()!='\n');
                continue;
            }
            if(move<1 || move>9){ printf("Invalid position! Choose 1-9.\n"); continue; }
            int r=(move-1)/3, c=(move-1)%3;
            if(board[r][c]!=' '){ printf("Position already taken! Try again.\n"); continue; }

            board[r][c]=current;

            if(checkWin(current)){
                displayBoard();
                printf("Player %c WINS!\n", current);
                gameOver=true;
            } else if(checkDraw()){
                displayBoard();
                printf("It's a DRAW!\n");
                gameOver=true;
            } else {
                current = (current=='X') ? 'O' : 'X';
            }
        }
        printf("Play again? (y/n): "); scanf(" %c", &playAgain);
    }
    printf("Thanks for playing!\n");
    return 0;
}
