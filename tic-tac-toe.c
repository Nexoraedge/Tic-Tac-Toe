#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

void loadingSpinner() {
    char spinner[] = "\\|/-";  // Use box-drawing characters
    int i = 0;
    while (i < 20) {
        printf("\r%c", spinner[i % 4]);  // Cycle through the spinner characters
        fflush(stdout);  // Ensure the character is printed immediately
        Sleep(50); // Sleep for 200 milliseconds
        i++;
    }
}
int random2(int n)
{
    srand(time(NULL));
    return rand() % n + 1;
}
int is_board_full(char board[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] != 'X' && board[i][j] != 'O')
            {
                return 0; // not full
            }
        }
    }
    return 1; // full-draw
}
void printboard(char board[3][3]);
int checkwinner(char board[3][3]);
void PVP(char board[3][3]);
void bot_move(char board[3][3]);
void player_move(char board[3][3]);
void Ai_bot(char board[3][3]);
void reset_board(char board[3][3]);

int main()
{
    // getchar();
    char board[3][3] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    int game;
    int m = 0;
    // printf("~~~~~~~~~WELCOME~~~~~~~\n");
    printf("Enter 1 to play the game\nor\nEnter 0 to exit the game ");
    scanf("%d", &m);
    while (m != 0)
    { // printf("\t \tWelcome!! \n ");
        reset_board(board);
        printf("~~~~~~~~~WELCOME~~~~~~~\n");

        printf("\nPress 1 to play with computer\n \tor\nPress 0 to play 1 vs 1:\n");
        scanf("%d", &game);

        while (1)
        {
            if (game == 0)
            {
                printf("\t#GAME ON....\n");
                PVP(board);
                break;
            }
            else if (game == 1)
            {
                printf("\tYou are 'X' ...\n");
                Ai_bot(board);
                break;
            }
            else
            {
                printf("\tInvalid!!\n ");
                break;
            }
        }

        printf("\nEnter 1 to play the game\nor\nEnter 0 to exit the game ");
        scanf("%d", &m);
    }
    // PVP(board);
    return 0;
}

void printboard(char board[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf(" %c ", board[i][j]);
            if (j < 2)
            {
                printf("|");
            }
        }
        printf("\n");
        if (i < 2)
            printf("---|---|---\n");
    }
    printf("\n____________________________________\n");
}

int checkwinner(char board[3][3])
{
    // rows and columns
    for (int i = 0; i < 3; i++)
    {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] || board[i][0] == board[i][1] && board[i][1] == board[i][2])
        {
            return 1;
        }
        if (board[0][2] == board[1][1] && board[1][1] == board[2][0] || board[0][0] == board[1][1] && board[1][1] == board[2][2])
        {
            return 1;
        }
    }
    return 0;
}

void PVP(char board[3][3])
{
    int value;
    char player = 'X';

    printf("Here the the board: \n");
    // printboard(board);

    for (int turn = 0; turn < 9; turn++)
    {
        printboard(board);
        printf("Place the %c : ", player);
        scanf("%d", &value);
        if (value > 9 && value < 1)
        {
            printf("Invalid move. Try again.\n");
            turn--; // Repeat turn
            continue;
        }
        else if (board[(value - 1) / 3][(value - 1) % 3] == 'X' || board[(value - 1) / 3][(value - 1) % 3] == 'O')
        {
            printf("Invalid move. Try again.\n");
            turn--; // Repeat turn
            continue;
        }
        else
            board[(value - 1) / 3][(value - 1) % 3] = player;

        if (checkwinner(board))
        {
            printboard(board);
            printf("\n \n");
            printf("%c is Winner\n", player);
            break;
        }
        if (is_board_full(board))
        {
            printf("\t\t!!DRAW!!\n");
        }
        player = (player == 'X') ? 'O' : 'X';
    }
}
void bot_move(char board[3][3])
{
    while (1)
    {
        int randomsol = random2(9);
        int row = (randomsol - 1) / 3;
        int column = (randomsol - 1) % 3;
        if (board[row][column] != 'O' && board[row][column] != 'X')
        {
            board[row][column] = 'O';
            break;
        }
    }
}
void reset_board(char board[3][3])
{
    int k = 1;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = k + '0';
            k++;
        }
    }
}

void player_move(char board[3][3])
{
    int move;
    printf("PLce your 'X': ");
    scanf("%d", &move);
    if (move < 1 && move > 9)
    {
        printf("\tInvalid!!\n");
    }
    else if (board[(move - 1) / 3][(move - 1) % 3] == 'X' || board[(move - 1) / 3][(move - 1) % 3] == 'O')
    {
        printf("\tPLace already occupied!!\n");
        printf("Enter valid space: ");
        scanf("%d", &move);
        if (move < 1 && move > 9)
        {
            printf("\tInvalid!!\n");
        }
        else if (board[(move - 1) / 3][(move - 1) % 3] == 'X' || board[(move - 1) / 3][(move - 1) % 3] == 'O')
        {
            printf("\tPLace already occupied!!\t Chance CUT!!\n");
        }
        else
        {
            board[(move - 1) / 3][(move - 1) % 3] = 'X';
        }
    }
    else
    {
        board[(move - 1) / 3][(move - 1) % 3] = 'X';
    }
}

void Ai_bot(char board[3][3])
{
    int turn = 1;
    printboard(board);
    printf("\n");
    for (int turn = 1; turn < 10; turn++)
    {
        if (turn % 2 == 0)
        {
            printf("Bot-Moves:~\n");
            loadingSpinner();
            printf("\n");
            bot_move(board);
            printboard(board);
        }
        else if (turn % 2 == 1)
        {
            player_move(board);
            printboard(board);
        }
        if (checkwinner(board))
        {
            printboard(board);
            if (turn % 2 == 0)
            {
                printf("SORRY!!\t COMPUTER * WON *");
            }
            else
            {
                printf("CONGRATULATIONS!!\t YOU* WON *");
            }
            break;
        }
        if (is_board_full(board))
        {
            printboard(board);
            printf("\n\t\tOops!! DRAW\n");
            break;
        }
    }
}