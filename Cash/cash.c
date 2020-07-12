#include <stdio.h>
#include <cs50.h>
#include <math.h>

// https://cs50.harvard.edu/x/2020/psets/1/cash/

// function prototype
void greedyAlgorithm(int change);

// main function
int main(void)
{
    int changeOwed = 0;
    do
    {
        printf("How much cash do you owe me? \n");
        changeOwed = round(get_float("Enter amount: ") * 100);
    }
    while (changeOwed <= 0);
    greedyAlgorithm(changeOwed);
    return 0;
}

// function to execute the greedy algorithm
void greedyAlgorithm(int change)
{
    int quarters = 0, dimes = 0, nickels = 0, pennies = 0;

    while (change >= 25)
    {
        quarters++;
        change -= 25;
    }
    while (change >= 10)
    {
        dimes++;
        change -= 10;
    }
    while (change >= 5)
    {
        nickels++;
        change -= 5;
    }
    while (change >= 1)
    {
        pennies++;
        change -= 1;
    }
    printf("%d\n", quarters + dimes + pennies + nickels);
}
