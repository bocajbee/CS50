from cs50 import get_int

# https://cs50.harvard.edu/x/2020/psets/6/mario/more/

# get user input, initally set input to == a value of -1
user_input = -1
# run this while loop forever until the users input is > 0 or < 10
while user_input < 1 or user_input > 8:
    user_input = get_int("Please enter pyramid height? ")

# nested outer forloop needed incrementing i up to the users input in order to build the spaces before the pyramid + pyramid itself
for i in range(1, user_input + 1):
    print(" "*(user_input-i), end="")
    print("#"*(i), end="  ")
    print("#"*(i))
