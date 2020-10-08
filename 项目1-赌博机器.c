#include <stdio.h>
#include <stdlib.h>
#include <time.h>
enum Status
{
    CONTINUE,
    WON,
    LOST
};

int rollDice();
int main()
{
    int restart = 0;
    int sum;
    int myPoint;
    int wager, balance = 1000;
    enum Status gameStatus;
    printf("game start\n");
    do
    {
        do
        {
            printf("Enter your wager,please:");
            scanf("%d", &wager);
            if (wager > balance)
            {
                printf("You don't have enough money\n");
            }
        } while (wager < 0 || wager > 1000);

        srand(time(NULL));

        sum = rollDice();
        switch (sum)
        {
        case 7:
        case 11:
            gameStatus = WON;
            balance += wager;
            printf("player win\n");
            break; //WON

        case 2:
        case 3:
        case 12:
            gameStatus = LOST;
            balance -= wager;
            printf("player lose\n");
            break; //LOSE

        default:
            gameStatus = CONTINUE;
            myPoint = sum;
            printf("Point is %d\n", myPoint);
            break;
        } //switch

        while (gameStatus == CONTINUE)
        {
            sum = rollDice();
            if (sum == myPoint)
            {
                gameStatus = WON;
                balance += wager;
                printf("player win\n");
            }
            if (sum == 7)
            {
                gameStatus = LOST;
                balance -= wager;
                printf("lose \n");
            } //if
             //else z
        }         //while

        if (gameStatus == WON)
        {
            printf("Player wins\n");
        } //end if
        else
        {
            printf("Player loses\n");
        } // end else
        printf("You have $%d left\n", balance);
        if (balance <= 0)
        {
            printf("Sorry.You busted\n");
            break;
        }
    } while (restart == 0);
} //main

//roll dice
int rollDice()
{
    int die1;    /* first die */
    int die2;    /* second die */
    int diceSum; /* sum of dice */

    die1 = 1 + (rand() % 6);
    die2 = 1 + (rand() % 6);
    diceSum = die1 + die2;

    printf("Player rolled %d + %d = %d\n", die1, die2, diceSum);
    return diceSum;
} //end rollRice
