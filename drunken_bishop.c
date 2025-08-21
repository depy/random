#include <stdio.h>
#include <string.h>

#define ROWS 9
#define COLS 17
#define NUM_CHARS 15

char board[ROWS][COLS];
char chars[NUM_CHARS] = {' ', '.', 'o', '+', '=', '*', 'B', '0', 'X', '@', '%', '&', '#', '/', '^'};

void init_board(char board[ROWS][COLS]) {
    for(size_t j = 0; j < ROWS; j++) {
        for(size_t i = 0; i < COLS; i++) {
            board[j][i] = 0;
        }
    }
}

void print_board(char board[ROWS][COLS]) {
    for(int j = -1; j < ROWS + 1; j++) {
        for(int i = -1; i < COLS + 1; i++) {
            if((j == -1 && i == -1) || (j == ROWS && i == COLS) || (j == -1 && i == COLS) || (j == ROWS && i == -1)) {
                printf("+");
            } else if(j == -1 || j == ROWS) {
                printf("-");
            } else if(i == -1 || i == COLS) {
                printf("|");
            } else if(board[j][i] == 'S' || board[j][i] == 'E') {
                printf("%c", board[j][i]);
            } else if(board[j][i] < 18) {
                printf("%c", chars[board[j][i]]);
            } else if(board[j][i] >= 15){
                // Not sure. Just print the max character?
                printf("%c", chars[NUM_CHARS - 1]);
            } else {
                fprintf(stderr, "ERROR: Unknown value in cell.");
            }
        }
        printf("\n");
    }
}

void drunken_walk(unsigned char input[16], int bx, int by) {
    for(size_t i = 0; i < 16; i++) {
        char c = input[i];
        int twobits;

        for(size_t x = 0; x < 4; x++) {
            twobits = (c >> (2 * x)) & 0b11;
            switch(twobits) {
                case 0: bx--; by--; break;
                case 1: bx++; by--; break;
                case 2: bx--; by++; break;
                case 3: bx++; by++; break;
            }
            if(bx < 0) { bx = 0; }
            if(by < 0) { by = 0; }  
            if(bx > COLS - 1) { bx = COLS - 1; }
            if(by > ROWS - 1) { by = ROWS - 1; }
            board[by][bx]++;      
        }
        
    }

    board[4][8] = 'S';
    board[by][bx] = 'E';
}

int main(int argc, char** argv) {
    char* hex_string = argv[1];
    if(argc != 2 || strlen(hex_string) != 32) {
        printf("String must be 32 characters long!\n");
        printf("Usage: %s <hex_string_of_length_32>\n", argv[0]);
        return 1;
    }

    unsigned char val[16];
    char* pos = hex_string;

    for (size_t count = 0; count < sizeof val/sizeof *val; count++) {
        sscanf(pos, "%2hhx", &val[count]);
        pos += 2;
    }

    int bx = 8;
    int by = 4;

    init_board(board);

    drunken_walk(val, bx, by);

    print_board(board);
    return 0;
}
