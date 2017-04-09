#include <stdio.h>  // allows use of printf() and scanf()
#include <stdlib.h> // allows use of rand() and srand()

typedef enum faciem {LEFT, RIGHT, CENTER, PASS} faces; // each face is a possible roll on a dice

int setNumOfPlayers(); // sets the number of players playing the game at the start from user input
int getInCount(int playersBank[], int players); // counts the number of players left in the game (players with money)
int getMaxRolls(int playersBank[], int currentPlayer); // determines how many times a player should roll the die
int getPrevPlayer(int currentPlayer, int players); // returns the previous player's index from the current player's
int getNextPlayer(int currentPlayer, int players); // returns the next player's index from the current player's
void findWinner(int *winningPlayer, int players, int playersBank[]); // sets the winningPlayer if found

int main()
{
    faces die[] = {LEFT, RIGHT, CENTER, PASS, PASS, PASS}; // 6 faces of each die
    const char* names[] = {"Whoopi", "Dale", "Rosie", "Jimmie", "Barbara", "Kyle", "Raven", "Tony", "Jenny", "Clint"};

    unsigned int seed; // the seed to set for rand(), srand() takes in an unsigned int
    printf("Enter a seed: ");
    scanf("%u", &seed);
    srand(seed);

    int numOfPlayers = setNumOfPlayers(); // number of players playing the game at the start
    int curPlayer = 0; // the current player rolling the dice
    int prevPlayer, nextPlayer;
    int winner; // the player who won the pot
    int pot = 0; // number of $ in the pot

    int bank[numOfPlayers]; // each index holds a players money
    for (int player_i = 0; player_i < numOfPlayers; player_i++)
    {
        bank[player_i] = 3; // set each player's money to a default of $3
    }

    while (getInCount(bank, numOfPlayers) > 1) // while at least 2 people are 'in' the game
    {
        if (bank[curPlayer] > 0) // if the current player has money
        {
            printf("%s rolls...", names[curPlayer]);
            int maxRolls = getMaxRolls(bank, curPlayer); // determine how many times they should roll the die
            for (int roll_i = 0; roll_i < maxRolls; roll_i++) // for each roll
            {
                int roll = die[rand() % 6]; // roll a face, indeces [0, 5] of die
                switch (roll)
                {
                    case LEFT:
                    {
                        prevPlayer = getPrevPlayer(curPlayer, numOfPlayers);
                        --bank[curPlayer]; // the current player loses $1
                        ++bank[prevPlayer]; // the previous player gains $1
                        printf(" gives $1 to %s", names[prevPlayer]);
                        break;
                    }
                    case RIGHT:
                    {
                        nextPlayer = getNextPlayer(curPlayer, numOfPlayers);
                        --bank[curPlayer]; // the current player loses $1
                        ++bank[nextPlayer]; // the next player gains $1
                        printf(" gives $1 to %s", names[nextPlayer]); 
                        break;
                    }
                    case CENTER:
                    {
                        --bank[curPlayer]; // the current player loses $1
                        ++pot; // the pot gains $1
                        printf(" puts $1 in the pot");
                        break;
                    }
                    case PASS:
                    {
                        printf(" gets a pass");
                        break;
                    }
                    default:
                    {
                        printf("%s cheated and brought their own die", names[curPlayer]);
                        break;
                    }
                }
            } // end of a player's rolls
            printf("\n");
            curPlayer = getNextPlayer(curPlayer, numOfPlayers); // set the next player
            findWinner(&winner, numOfPlayers, bank);
        }
        else // the current player has no money, go to the next player in the rotation
        {
            curPlayer = getNextPlayer(curPlayer, numOfPlayers);
        }
    }
    printf("%s wins the $%d pot with $%d left in the bank!\n", names[winner], pot, bank[winner]);
    return 0;
}

int setNumOfPlayers() // sets the number of players playing the game at the start from user input
{
    int players = 2; // minimum number of players for a game to be played
    do
    {    
        if (players < 2 || players > 10) // if an invalid number of players is entered
        {
            printf("\nYou have must at least 2 players and no more than 10.  Try again.\n");
        }
        printf("How many players?: ");
        scanf("%d", &players);
    } while (players < 2 || players > 10); // while the number of players is invalid, keep asking for a valid number
    
    return players;
}

int getInCount(int playersBank[], int players) // counts the number of players left in the game (players with money)
{
    int inCount = 0; // counter that holds the number of players 'in' the game (that have at least $1)
    for (int player_i = 0; player_i < players; player_i++)
    {
        if (playersBank[player_i] > 0) // if the player has at least $1
        {
            ++inCount; // they are 'in', increment the counter
        }
    }

    return inCount;
}

int getMaxRolls(int playersBank[], int currentPlayer) // determines how many times a player should roll the die
{
    int rolls;
    if (playersBank[currentPlayer] >= 3) // if the player has $3 or more
    {
        rolls = 3; // they roll 3 times
    }
    else
    {
        rolls = playersBank[currentPlayer]; // 1 roll per $1
    }

    return rolls;
}

int getPrevPlayer(int currentPlayer, int players) // returns the previous player's index from the current player's
{
    int prevPlayer;
    if (currentPlayer != 0) // if the current player is not the left most index (0)
    {
        prevPlayer = --currentPlayer; // the previous player in rotation is the current index - 1
    }
    else // the current player is the left most index (0)
    {
        prevPlayer = --players; // the previous player in rotation is the furthest index (number of players - 1)
    }
    
    return prevPlayer;
}

int getNextPlayer(int currentPlayer, int players) // returns the next player's index from the current player's
{
    int nextPlayer;
    if (currentPlayer < --players) // if the current player is not the furthest index (number of players - 1)
    {
        nextPlayer = ++currentPlayer; // the next player in rotation is the (current player's index + 1)
    }
    else // the current player is the furthest index
    {
        nextPlayer = 0; // the next player in rotation is the 0 index
    }

    return nextPlayer;
}

void findWinner(int *winningPlayer, int players, int playersBank[]) // sets the winningPlayer if found
{
    if (getInCount(playersBank, players) == 1) // if exactly one player is 'in' the game still, find their index because they won
    {
        for (int player_i = 0; player_i < players; player_i++) // scan through the bank of every player
        {
            if (playersBank[player_i] > 0) // if they have money,
            {
                *winningPlayer = player_i; // they are the winner.
            }
        }
    }
}
