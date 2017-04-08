#include <stdio.h>  // allows use of printf() and scanf()
#include <stdlib.h> // allows use of rand() and srand()

typedef enum faciem {LEFT, RIGHT, CENTER, PASS} faces;

int setNumOfPlayers();
int getInCount(int playersBank[], int players); // calculates the number of players left in the game (players with money)
int getMaxRolls(int playersBank[], int currentPlayer); // determines how many times a player should roll the die
int getPrevPlayer(int currentPlayer, int players);
int getNextPlayer(int currentPlayer, int players);
void findWinner(int *winningPlayer, int players, int playersBank[]); // sets the winningPlayer if found

int main()
{
    faces die[] = {LEFT, RIGHT, CENTER, PASS, PASS, PASS}; // 6 faces of each die
    const char* names[] = {"Whoopi", "Dale", "Rosie", "Jimmie", "Barbara",
                           "Kyle", "Raven", "Tony", "Jenny", "Clint"};

    unsigned int seed; // the seed to set for rand(), srand() takes in an unsigned int
    printf("Enter a seed: ");
    scanf("%u", &seed);
    srand(seed);

    int numOfPlayers = setNumOfPlayers(); 
    int curPlayer = 0; // the current player rolling the dice
    int prevPlayer, nextPlayer;
    int winner; // the player who won the pot
    int pot = 0; // number of $ in the pot

    int bank[numOfPlayers]; // each index holds a players money
    for (int player_i = 0; player_i < numOfPlayers; player_i++)
    {
        bank[player_i] = 3; // set each player's money to a default of $3
    }

    while (getInCount(bank, numOfPlayers) > 1)
    {
        if (bank[curPlayer] > 0) // if the current player has money
        {
            printf("%s rolls...", names[curPlayer]);
            int maxRolls = getMaxRolls(bank, curPlayer);
            for (int roll_i = 0; roll_i < maxRolls; roll_i++) // for each dollar that the player has, roll a dice
            {
                int roll = die[rand() % 6]; // roll a face, indeces [0, 5] of die
                switch (roll)
                {
                    case LEFT:
                        prevPlayer = getPrevPlayer(curPlayer, numOfPlayers);
                        --bank[curPlayer]; // the current player loses $1
                        ++bank[prevPlayer]; // the previous player gains $1
                        printf(" gives $1 to %s", names[prevPlayer]);
                        break;
                    case RIGHT:
                        nextPlayer = getNextPlayer(curPlayer, numOfPlayers);
                        --bank[curPlayer]; // the current player loses $1
                        ++bank[nextPlayer]; // the next player gains $1
                        printf(" gives $1 to %s", names[nextPlayer]); 
                        break;
                    case CENTER:
                        --bank[curPlayer]; // the player loses $1
                        ++pot; // the pot gains $1
                        printf(" puts $1 in the pot");
                        break;
                    case PASS:
                        printf(" gets a pass");
                        break;
                    default:
                        printf("%s cheated and brought their own die", names[curPlayer]);
                        break;
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

int setNumOfPlayers()
{
    int players = 2;
    do
    {    
        if (players < 2 || players > 10)
        {
            printf("\nYou have must at least 2 players and no more than 10.  Try again.\n");
        }
        printf("How many players?: ");
        scanf("%d", &players);
    } while (players < 2 || players > 10);
    
    return players;
}

int getInCount(int* playersBank, int players)
{
    int inCount = 0;
    for (int player_i = 0; player_i < players; player_i++)
    {
        if (playersBank[player_i] > 0)
        {
            inCount++;
        }
    }

    return inCount;
}

int getMaxRolls(int playersBank[], int currentPlayer)
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

int getPrevPlayer(int currentPlayer, int players)
{
    int prevPlayer;
    if (currentPlayer != 0)
    {
        prevPlayer = --currentPlayer;
    }
    else
    {
        prevPlayer = --players;
    }
    
    return prevPlayer;
}

int getNextPlayer(int currentPlayer, int players)
{
    int nextPlayer;
    if (currentPlayer < --players)
    {
        nextPlayer = ++currentPlayer;
    }
    else
    {
        nextPlayer = 0;
    }

    return nextPlayer;
}

void findWinner(int *winningPlayer, int players, int playersBank[])
{
    if (getInCount(playersBank, players) == 1) // if one player is in the game still, find their index because they won
    {
        for (int player_i = 0; player_i < players; player_i++)
        {
            if (playersBank[player_i] > 0)
            {
                *winningPlayer = player_i;
            }
        }
    }
}
