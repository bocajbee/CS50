from cs50 import get_float

# https://cs50.harvard.edu/x/2020/psets/6/cash/

# main function
def main():
    # get user input
    change_owed = -1

    while change_owed <= 0:
        print("how much cash do you owe me?")
        change_owed = round(get_float("Enter amount: ") * 100)
    greedyAlgorithm(change_owed)

# function to execute greedy algo
def greedyAlgorithm(change):

    # declaring the starting value of my ints: quarters, dimes, nickels and pennies
    quarters = 0
    dimes = 0
    nickels = 0
    pennies = 0

    # perform greedy algo
    while change >= 25:
        quarters += 1
        change -= 25
    while change >= 10:
        dimes += 1
        change -= 10
    while change >= 5:
        nickels += 1
        change -= 5
    while change >= 1:
        pennies += 1
        change -= 1
    # print total number of coins
    print(quarters + dimes + pennies + nickels)


if __name__ == "__main__":
    main()
