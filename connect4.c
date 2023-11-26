// CS 135
// Author: Jacob Xie
// Connect 4

#include <stdio.h>
#include <stdlib.h>

#define BOARD_WIDTH 5
#define BOARD_HEIGHT 5

int checkWinner(char c, int placeRow, int placeColumn, int rows, int columns, char board[][columns]);
int checkHorizontal(char c, int placeRow, int placeColumn, int rows, int columns, char board[][columns]);
int checkVertical(char c, int placeRow, int placeColumn, int rows, int columns, char board[][columns]);
int checkDiagonals(char c, int placeRow, int placeColumn, int rows, int columns, char board[][columns]);
int dropPiece(char c, int place, int rows, int columns, char board[][columns]); 
void displayBoard(int columns, char board[][columns]);

int main() {
    char board[BOARD_HEIGHT][BOARD_WIDTH];

    // Initialize the board with dashes
    for (int i = 0 ; i < BOARD_HEIGHT ; i++) {
        for (int j = 0 ; j < BOARD_WIDTH ; j++) {
            board[i][j] = '-';
        }
    }
    
    system("clear");
    displayBoard(BOARD_WIDTH, board);

    int winner = 0;
    while (winner == 0) {
        int result;
        int place;
       
        // Have player one choose a column to drop a piece until a successful drop
        do {
            printf("Player one, place a piece by entering a column between 1 and 5: ");
            scanf("%d", &place);

            if (place > 5 || place < 1) {
                printf("Please enter a valid column!\n");
                continue;
            }
    
            result = dropPiece('1', place-1, BOARD_HEIGHT, BOARD_WIDTH, board);

            if (result < 0) {
                printf("That space was not available!\n");
            }
        } while (result < 0);

        system("clear");
        displayBoard(BOARD_WIDTH, board);

        int win = checkWinner('1', result, place-1, BOARD_HEIGHT, BOARD_WIDTH, board); 

        if (win != 0) {
            printf("Player one won!!!!!\n");
            return 0;
        }

        // Have player two choose a column to drop a piece until a successful drop
        do {
            printf("Player two, place a piece by entering a column between 1 and 5: ");
            scanf("%d", &place);
   
            if (place > 5 || place < 1) {
                printf("Please enter a valid column!\n");
                continue;
            }

            result = dropPiece('2', place-1, BOARD_HEIGHT, BOARD_WIDTH, board);

            if (result < 0) {
                printf("That space was not available!\n");
            }
        } while (result < 0);

        system("clear");
        displayBoard(BOARD_WIDTH, board);
        
        win = checkWinner('2', result, place-1, BOARD_HEIGHT, BOARD_WIDTH, board);
        
        if (win != 0) {
            printf("Player two won!!!!!\n");
            return 0;
        } 
    }

    return 0;
}

// Returns -1 if no spot available, and the row the piece was placed in otherwise
int dropPiece(char c, int place, int rows, int columns, char board[][columns]) {
    // Go from bottom-up at the selected column and place the character at the first available spot 
    for (int i = rows ; i >= 0 ; i--) {
        if (board[i][place] == '-') {
            board[i][place] = c;
            return i;
        }
    }

    // If no spots were available
    return -1;
}

int checkWinner(char c, int placeRow, int placeColumn, int rows, int columns, char board[][columns]) {
    if (checkHorizontal(c, placeRow, placeColumn, rows, columns, board) != 0) {
       return 1;
    }
    
    if (checkVertical(c, placeRow, placeColumn, rows, columns, board) != 0) {
       return 1;
    }
    
    if (checkDiagonals(c, placeRow, placeColumn, rows, columns, board) != 0) {
       return 1;
    }

    return 0;    
}

int checkHorizontal(char c, int placeRow, int placeColumn, int rows, int columns, char board[][columns]) {
    // Check from left (horizontal)
    for (int startOffset = -3 ; startOffset <= 0 ; startOffset++) {
        int startColumn = placeColumn + startOffset;

        int count = 0;
        for (int i = 0 ; i < 4 ; i++) {
            if (startColumn + i < 0 || startColumn + i >= columns) break;

            if (board[placeRow][startColumn + i] == c) {
                count++;
            } else break;
        }

        if (count == 4) return 1;
    }
    
    return 0;
}

int checkVertical(char c, int placeRow, int placeColumn, int rows, int columns, char board[][columns]) {
    // Check from top (vertical)
    for (int startOffset = -3 ; startOffset <= 0 ; startOffset++) {
        int startRow = placeRow + startOffset;

        int count = 0;
        for (int i = 0 ; i < 4 ; i++) {
            if (startRow + i < 0 || startRow + i >= rows) break;

            if (board[startRow + i][placeColumn] == c) {
                count++;
            } else break;
        }

        if (count == 4) return 1;
    }

    return 0;
}

int checkDiagonals(char c, int placeRow, int placeColumn, int rows, int columns, char board[][columns]) {
    // Check from top-left to bottom-right
    for (int startOffset = -3 ; startOffset <= 0 ; startOffset++) {
        int startRow = placeRow + startOffset;
        int startColumn = placeColumn + startOffset;

        int count = 0;
        for (int i = 0 ; i < 4 ; i++) {
            if (startRow + i < 0 || startRow + i >= rows || startColumn + i < 0 || startColumn + i >= columns) break;

            if (board[startRow + i][startColumn + i] == c) {
                count++;
            } else break;
        }

        if (count == 4) return 1;
    }
 
    
    // Check from top-right to bottom-left
    for (int startOffset = -3 ; startOffset <= 0 ; startOffset++) {
        int startRow = placeRow + startOffset;
        int startColumn = placeColumn - startOffset;

        int count = 0;
        for (int i = 0 ; i < 4 ; i++) {
            if (startRow + i < 0 || startRow + i >= rows || startColumn - i < 0 || startColumn - i >= columns) break;
            
            if (board[startRow + i][startColumn - i] == c) {
                count++;
            } else break;
        }

        if (count == 4) return 1;
    }

    return 0;
}


void displayBoard(int columns, char board[][columns]) {
    for (int i = 0 ; i < BOARD_HEIGHT ; i++) {
        for (int j = 0 ; j < BOARD_WIDTH ; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}
