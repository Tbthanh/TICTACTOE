#include <stdio.h>
#include <stdlib.h>

// Function to draw the game board with numbered cells
void drawBoard(char board[3][3]) {
    printf(" 1 | 2 | 3 \n");
    printf("-----------\n");
    printf(" 4 | 5 | 6 \n");
    printf("-----------\n");
    printf(" 7 | 8 | 9 \n");

    printf("Current Board:\n");
    printf(" %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
    printf("-----------\n");
    printf(" %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
    printf("-----------\n");
    printf(" %c | %c | %c \n", board[2][0], board[2][1], board[2][2]);
}

// Function to check for a winner
int checkWin(char board[3][3], char symbol) {
    for (int i = 0; i < 3; i++) {
        if ((board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol) ||
            (board[0][i] == symbol && board[1][i] == symbol && board[2][i] == symbol)) {
            return 1; // Winner
        }
    }
    
    if ((board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol) ||
        (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol)) {
        return 1; // Winner
    }
    
    return 0; // No winner yet
}

// Function to check if a cell is still vacant
int isMoveValid(char board[3][3], int position) {
    int row = (position - 1) / 3;
    int col = (position - 1) % 3;
    return board[row][col] == ' ';
}

int main() {
    char board[3][3] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };

    int position;
    char currentPlayer = 'X';

    printf("Tic Tac Toe Game\n");

    do {
        // Display the game board with numbered cells
        drawBoard(board);

        // Player enters position
        printf("Player %c, enter position (1-9): ", currentPlayer);
        if (scanf("%d", &position) != 1 || position < 1 || position > 9 || !isMoveValid(board, position)) {
            // Invalid input
            while (getchar() != '\n'); // Clear the input buffer
            printf("Invalid input. Please choose again.\n");
            continue;
        }

        // Check if the move is valid
        int row = (position - 1) / 3;
        int col = (position - 1) % 3;
        board[row][col] = currentPlayer;

        // Check if the player has won
        if (checkWin(board, currentPlayer)) {
            // Display the game board and announce the winner
            drawBoard(board);
            printf("Player %c wins!\n", currentPlayer);
            break;
        }

        // Switch players
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';

    } while (1);

    return 0;
}
