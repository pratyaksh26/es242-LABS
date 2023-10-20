/*
Team:
Manas kalal
Pratyaksh Bhyare
Piyush Singh
*/
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
//for of player 2
enum {
    NO = 0,
    RED = 1,
    BLUE = 2
};

typedef char board_t[15];
typedef char player_t;

void init_board(board_t board)
{
    int i = 0;
while (i < 15) {
    board[i] = NO;
    i++;
}
}

player_t other_player(player_t player)
{
    switch (player) {
        case RED: return BLUE;
        case BLUE: return RED;
        default: assert(0);
    }
}

int has_won(board_t board, player_t player)
{
    int a[4] = {4, 7, 9, 10};
    int b[3] = {3, 5, 6};
    int c[2] = {2, 3};
    int d = 1;
    
   int i = 0;
   while (i < 4) {
    int j = i + 1;
    while (j <= 4) {
        if (board[i] == other_player(player) &&
            board[j] == other_player(player) &&
            board[j + a[i]] == other_player(player)) {
            return 1;
        }
        j++;
    }
    i++;
}


    int k = 5;
    while (k < 8) {
    int j = k + 1;
    while (j <= 8) {
        if (board[k] == other_player(player) &&
            board[j] == other_player(player) &&
            board[j + b[k - 5]] == other_player(player)) {
            return 1;
        }
        j++;
    }
    k++;
}


    int l = 9;
    while (l < 11) {
    int j = l + 1;
    while (j <= 11) {
        if (board[l] == other_player(player) &&
            board[j] == other_player(player) &&
            board[j + c[l - 9]] == other_player(player)) {
            return 1;
        }
        j++;
    }
    l++;
}


    int m = 12;
    while (m < 13) {
    int j = m + 1;
    while (j <= 13) {
        if (board[m] == other_player(player) &&
            board[j] == other_player(player) &&
            board[j + d] == other_player(player)) {
            return 1;
        }
        j++;
    }
    m++;
}


    return 0;
}

int is_full(board_t board)  //---- > no need as the game never ties....
{
    for (int i = 0; i < 15; i++) {
        if (board[i] == NO) {
            return 0;
        }
    }
    return 1;
}

typedef struct {
    int line;
    int score;
} move_t;

move_t best_move(board_t board, player_t player)
{
    move_t response;
    move_t candidate;
    int no_candidate = 1;

    //Base case
    for (int i = 0; i < 15; ++i) {
        if (board[i] == NO) {
            board[i] = player;
            if (has_won(board, player)) {
                board[i] = NO;
                return (move_t){i, 1};
            }
            board[i] = NO;
        }
    }

    //Predictions
    int n = 0;
    while (n < 15) {
    if (board[n] == NO) {
        board[n] = player;
        response = best_move(board, other_player(player));
        board[n] = NO;
        if (is_full(board)) {
            board[n] = NO;
            return (move_t){n, 0};
        }
        if (response.score == -1) {
            return (move_t){n, 1};
        } else if (response.score == 0) {
            candidate = (move_t){n, 0};
            no_candidate = 0;
        } else {
            if (no_candidate) {
                candidate = (move_t){n, -1};
                no_candidate = 0;
            }
        }
    }
    n++;
}


    return candidate;
}

void print_board(board_t board)
{
    for (int i = 0; i < 15; ++i) {
        switch (board[i]) {
            case NO: printf("0  "); break;
            case RED: printf("R  "); break;
            case BLUE: printf("B  "); break;
        }
    }
    printf("\n");
}

#include <stdio.h>

int main() {
    int move, i;
    board_t board;
    move_t response;
    int x;

    printf("You are the RED  player. Choose to be player 1 or 2: ");
    scanf("%d", &x);
    player_t current;

    if (x == 1) {
        current = RED;
    } else if (x == 2) {
        current = BLUE;
    } else {
        printf("\nInvalid choice");
        return 1; // Exit the program due to an invalid choice
    }

    init_board(board);

    while (1) {
        print_board(board);
        printf("\n\n");

        if (current == RED) {
            printf("0  1  2  3  4  5  6  7  8  9 10 11 12 13 14\n");
            printf("Enter your move: ");
            scanf("%d", &move);
            i = move;

            if (i >= 0 && i < 15 && board[i] == NO) {
                board[i] = current;
            } 
            else {
                printf("Invalid move. Try again.\n");
                continue;
            }
        } else {
            response = best_move(board, current);
            board[response.line] = current;
        }

        if (has_won(board, current)) {
            print_board(board);
            printf("Player %c has won!\n", (current == RED) ? 'R' : 'B');
            break;
        }

        current = other_player(current);
    }

    return 0;
}
