// CS 135
// Author: Jacob Xie
// Connect 4

#include <stdio.h>

#define BOARD_WIDTH 5
#define BOARD_HEIGHT 5
#define MAX_NAME_LENGTH 50

int checkWinner(char c, int placeRow, int placeColumn, int rows, int columns, char board[][columns]);
int checkHorizontal(char c, int placeRow, int placeColumn, int rows, int columns, char board[][columns]);
int checkVertical(char c, int placeRow, int placeColumn, int rows, int columns, char board[][columns]);
int checkDiagonals(char c, int placeRow, int placeColumn, int rows, int columns, char board[][columns]);
int dropPiece(char c, int place, int rows, int columns, char board[][columns]); 
int checkTie(int rows, int columns, char board[][columns]);
void displayBoard(int rows, int columns, char board[][columns]);
void getBoard(FILE* fptr, int rows, int columns, char board[][columns]);
void saveBoard(FILE* fptr, int rows, int columns, char board[][columns]);

int main() {
    // Prompt the user with game menu
    printf("CONNECT-4\n");
    printf("1) Start a new game\n");
    printf("2) Load an existing game\n");
    printf("0) Exit\n\n");

    int option;
    printf("Please choose an option from the menu above: ");
    scanf("%d", &option);
    
    char board[BOARD_HEIGHT][BOARD_WIDTH];
    switch (option) {
        case 0:
            return 0;
        case 1:
            // Initialize the board with dashes
            for (int i = 0 ; i < BOARD_HEIGHT ; i++) {
                for (int j = 0 ; j < BOARD_WIDTH ; j++) {
                    board[i][j] = '-';
                }
            }
            break;
        case 2:
            // Initialize the board from a file
            FILE* fptr = fopen("saved_game.txt", "r");
            
            if (fptr == NULL) {
                printf("Error opening game file!\n");
                return 1;
            }
            
            getBoard(fptr, BOARD_HEIGHT, BOARD_WIDTH, board);
            fclose(fptr);
            break;
    }

    char name1[MAX_NAME_LENGTH];
    printf("Player 1, enter your name: ");
    scanf(" %s", name1);

    char name2[MAX_NAME_LENGTH];
    printf("Player 2, enter your name: ");
    scanf(" %s", name2);

    displayBoard(BOARD_HEIGHT, BOARD_WIDTH, board);

    int winner = 0;
    while (winner == 0) {
        int result;
        int place;
       
        // Have player one choose a column to drop a piece until a successful drop
        do {
            printf("%s, place a piece by entering a column between 1 and 5 or save and exit the game by entering 0: ", name1);
            scanf("%d", &place);

            if (place == 0) {
                FILE* fptr = fopen("saved_game.txt", "w");
                
                if (fptr == NULL) {
                    printf("There was an error saving the game!\n");
                    return 1;
                }
                
                saveBoard(fptr, BOARD_HEIGHT, BOARD_WIDTH, board);
                fclose(fptr);
                return 0;
            }
            

            if (place > 5 || place < 1) {
                printf("Please enter a valid column!\n");
                continue;
            }
    
            result = dropPiece('1', place-1, BOARD_HEIGHT, BOARD_WIDTH, board);

            if (result < 0) {
                printf("That space was not available!\n");
            }
        } while (result < 0);

        printf("\n");
        displayBoard(BOARD_HEIGHT, BOARD_WIDTH, board);

        int win = checkWinner('1', result, place-1, BOARD_HEIGHT, BOARD_WIDTH, board); 

        if (win > 0) {
            printf("%s won!!!!!\n", name1);
            return 0;
        }

        if (win < 0) {
            printf("The game is tied!\n");
            return 0;
        }

        // Have player two choose a column to drop a piece until a successful drop
        do {
            printf("%s, place a piece by entering a column between 1 and 5 or save and exit the game by entering 0: ", name2); 
            scanf("%d", &place);
  
            if (place == 0) {
                FILE* fptr = fopen("saved_game.txt", "w");
                
                if (fptr == NULL) {
                    printf("There was an error saving the game!\n");
                    return 1;
                }
                
                saveBoard(fptr, BOARD_HEIGHT, BOARD_WIDTH, board);
                fclose(fptr);
                return 0;
            }


            if (place > 5 || place < 1) {
                printf("Please enter a valid column!\n");
                continue;
            }

            result = dropPiece('2', place-1, BOARD_HEIGHT, BOARD_WIDTH, board);

            if (result < 0) {
                printf("That space was not available!\n");
            }
        } while (result < 0);

        printf("\n");
        displayBoard(BOARD_HEIGHT, BOARD_WIDTH, board);
        
        win = checkWinner('2', result, place-1, BOARD_HEIGHT, BOARD_WIDTH, board);
        
        if (win > 0) {
            printf("%s won!!!!!\n", name2);
            return 0;
        }

        if (win < 0) {
            printf("The game is tied!\n");
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

int checkTie(int rows, int columns, char board[][columns]) {
    int sum = 0;
    for (int column = 0 ; column < columns ; column++) {
        if (board[0][column] != '-') {
            sum++;
        }
    }

    if (sum == rows) {
        return 1;
    }

    return 0;
}

int checkWinner(char c, int placeRow, int placeColumn, int rows, int columns, char board[][columns]) {
    if (checkTie(rows, columns, board) != 0) {
        return -1;
    }
    
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
 
void displayBoard(int rows, int columns, char board[][columns]) {
    for (int i = 0 ; i < rows ; i++) {
        for (int j = 0 ; j < columns ; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

void getBoard(FILE* fptr, int rows, int columns, char board[][columns]) {
    for (int row = 0 ; row < rows ; row++) {
        for (int column = 0 ; column < columns ; column++) {
            fscanf(fptr, "%c ", &board[row][column]);
        }
    }
}

void saveBoard(FILE* fptr, int rows, int columns, char board[][columns]) {
    for (int row = 0 ; row < rows ; row++) {
        for (int column = 0 ; column < columns ; column++) {
            fprintf(fptr, "%c ", board[row][column]);
        }
        fprintf(fptr, "\n");
    }
}

