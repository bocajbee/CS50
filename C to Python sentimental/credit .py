from cs50 import get_string

# https://cs50.harvard.edu/x/2020/psets/6/credit/

def main():

    CCnumber = get_string("Please enter a CC number: ") # get the credit card number from the user. this makes sure it's an integer, and that it's not empty automatically.
    CCNumberLengh = len(str(CCnumber)) # get the lengh of the credit card number the user inputted

    if CCNumberLengh < 15 or CCNumberLengh > 16:
        print("INVALID")
        return 0

    # Check starting numbers of the credit card & return VISA, AMEX or MASTERCARD
    elif CCNumberLengh == 15 and CCnumber[0] == "3" and (CCnumber[1] == "4" or CCnumber[1] == "7"): # Verify CC is American Express. All AA cards start with 34 or 37
        if lunhsAlg(CCnumber) == 0:
            print("AMEX");
        else:
            print("INVALID")

     #Verify CC is Mastercard. All MC's start with a 51, 52, 53, 54 or 55
    elif CCNumberLengh == 16 and CCnumber[0] == "5" or CCnumber[0] == "2" and CCnumber[1] >= "1" and CCnumber[1] <= "5":
        print("POO")
        if lunhsAlg(CCnumber) == 0:
            print("MASTERCARD")
        else:
            print("INVALID")

    # Verify CC is visa. All Visa's are 13 or 16 digits long and start with the string value of '4'
    elif CCNumberLengh == 13 or CCNumberLengh == 16 and CCnumber[0] == "4":
        print("WEE")
        if lunhsAlg(CCnumber) == 0:
            print("VISA")
        else:
            print("INVALID")
    else:
        print("INVALID")


def lunhsAlg(CCnumber):

    l = len(CCnumber)
    s = 0
    t = 0

    # start at the end of the CC - 2 spaces against its len() then deincreiment to 0 by 2
    for i in range(l - 2, -1, -2):
        t = int(CCnumber[i])
        s = s + add_digits(t * 2)

    print(i)

    # start at the end of the CC - 1 space against its len() then deincreiment to 0 by 2
    for i in range(l - 1, -1, -2):
        t = int(CCnumber[i])
        s = s + t

    if s % 10 == 0:
        return 0

# for this example we will pass in 17
def add_digits(n):

    d = 0

    while n > 0:
        d = d + (n % 10)
        n = int(n / 10)

    print(d)
    return d # return this integer value

if __name__ == "__main__":
    main()
