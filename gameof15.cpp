/*
 * Hello!
 * Name: Baibhav Vatsa
 * Class: XI - I
 * Roll: 10
 * School: DPS RK Puram
 * 
 * C++ Project
 * Game of 15
 * It is a puzzle game played on a square board. The goal is to arrange it in a ascending order.
 */


// header files
#include <fstream.h>
#include <iostream.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

// constants declared
#define DIM_MIN 3
#define DIM_MAX 9

// board declared with global scope
int board[DIM_MAX][DIM_MAX];

// d is for dimension, declared with global scope
int d;

// function prototypes
void clear(void);
void init(void);
void draw(void);
int move(int tile);
int won(void);
int isCompleted(void);

int main()
{
    //starting up
    clrscr();
    cout<<"WELCOME TO GAME OF FIFTEEN!\n\nInstructions:\n1. Enter the tile number which you want to move\n2. Enter '0' anytime you want to exit.\n3. The goal is to arrange all the numbers in ascending order.\n\nEnter the dimensions: ";
    cin>>d;

    //checking that the dimensions are legal
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // opening file to record everything
    FILE* file = fopen("log.txt", "w");

    //if file doesn't open, exit
    if (file == NULL)
    {
        return 3;
    }

    // initialize the game
    init();

    // setting up an infinite loop
    while (1==1)
    {
        // clear the screen
        clrscr();

        // draw the game
        draw();

        // keeping a log
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // you won! yaaayyy!!!
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // moving the tile
        printf("\nTile to move: ");
        int tile;
        cin>>tile;

        // if you want to exit
        if (tile == 0)
        {
            break;
        }

        // logging everything
        fprintf(file, "%i\n", tile);
        fflush(file);

        // checking for illegal moves
        if (move(tile)==0)
        {
            printf("\nIllegal move.\n");
        }
    }

    // logging done
    fclose(file);

    // end :D
    return 0;
}

/*
 * Initializes the board 2d array
 */
void init(void)
{
    // Choosing the numbers and initializing the board
    int total = (d * d) - 1;

    // If even
    if ((total) % 2 == 0)
    {
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                board[i][j] = total;
                total--;
            }
        }
    }

    // If odd
    else
    {
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                board[i][j] = total;
                total--;
            }
        }
        int r_last = d - 1;
        int c_last = d - 2;
        int c_slast = d - 3;
        board[r_last][c_slast] = 1;
        board[r_last][c_last] = 2;
    }
    return;
}

/*
 * Draws the board
 */
void draw(void)
{
    cout<<endl;
    for (int i = 0; i < d; i++)
    {
        printf(" | ");
        for (int j = 0; j < d; j++)
        {
            int digit = board[i][j];
            if (digit > 0)
            {
                printf("%2i", digit);
            }
            else
            {
                printf("__");
            }
            printf(" | ");
        }
        printf("\n");
    }
}

/*
 * Moving a tile and checking that it is legal
*/
int move(int tile)
{
    // variables for the nearby tiles
    int r_left;
    int r_right;
    int c_up;
    int c_down;

    // Checking and moving
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            if (board[i][j] == tile)
            {
                if (i == 0)
                {
                    r_left = 0;
                }
                else
                {
                    r_left = i - 1;
                }

                if (j == 0)
                {
                    c_up = 0;
                }
                else
                {
                    c_up = j - 1;
                }

                if (i == d - 1)
                {
                    r_right = d - 1;
                }
                else
                {
                    r_right = i + 1;
                }

                if (j == d - 1)
                {
                    c_down = d - 1;
                }
                else
                {
                    c_down = j + 1;
                }

                if (board[r_left][j] == 0 || board[r_right][j] == 0 || board[i][c_up] == 0 || board[i][c_down] == 0)
                {
                    for (int k = 0; k < d; k++)
                    {
                        for (int l = 0; l < d; l++)
                        {
                            if (board[k][l] == 0)
                            {

                                // If everything is fine, move the tile
                                int swap = board[k][l];
                                board[k][l] = board[i][j];
                                board[i][j] = swap;
                                return 1;
                            }
                        }
                    }
                }
            }
        }
    }

    // Failed to move
    return 0;
}

/*
 * Checking if the game has been won
 */
int won(void)
{
    // Checking that everything is arranged in a perfect way
    int  total = 1;
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            if (board[i][j] == total)
            {
                total++;
                if (total == ((d * d) - 1) && board[(d - 1)][(d - 1)] == 0 )
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}
