from cs50 import get_string

# https://cs50.harvard.edu/x/2020/psets/6/readability/

article = get_string("Please enter your article ") # get plaintext from the user

# counting variable to count number of letters, words and sentances in an article
letter = 0
word = 1
sentance = 0

# calculate stringlengh of entire article and store this in variable n
n = len(article)

# nested forloop needed incrementing i up to "n", 1 unit at a time
for i in range(0, n, 1):

    # count the number of chars in the article
    if article[i].isalnum() == True:
        letter += 1
    # count the number of words in the article
    if article[i].isspace() == True:
        word += 1
    # count the number of sentances in the article
    if article[i] == '!' or article[i] == '.' or article[i] == '?' and article[i - 1].isalnum() == True:
        sentance += 1

# print("# of letters = ", letter)
# print("# of words = ", word)
# print("# of sentances = ", sentance)

# calculate Coleman-Liau index. This is: grade = 0.0588 * (Letters per 100 words) - 0.296 * (Sentences per 100 words) - 15.8
grade = 0.0588 * (100 * letter / word) - 0.296 * (100 * sentance / word) - 15.8

# check grade
if grade < 1:
    print("Before Grade 1")
elif grade < 16:
    print("Grade", round(grade))
else:
    print("Grade 16+")
