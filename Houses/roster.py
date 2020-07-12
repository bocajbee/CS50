import sys
import csv
from cs50 import SQL

# https://cs50.harvard.edu/x/2020/psets/7/houses/

def main():

    if len(sys.argv) != 2:
        print("Invalid usage, please enter: python import.py HOUSE")
        sys.exit(1)

    # give us access to the students db within our python script
    db = SQL("sqlite:///students.db")

    # give us access to the students db within our python script. then in the SQL query, SELECT all from the Students table where the house = argv1 input
    # this function call automatically makes the list of dicts for us to use later for everyone we pulled from this house in the SQL query
    houses_dict = db.execute("SELECT * FROM students WHERE house = ? ORDER BY last, first",
       sys.argv[1])

    # loop through each dictionary generated for each row from the database.
    for row in houses_dict:

        # if the key collcted in this keyvaluepair being checked in 'middle' is 'None' indicating its NULL, print 2 names, otherwise print 3
        if row['middle'] == None:
            print(f"{row['first']} {row['last']}, born {row['birth']}")
        else:
            # otherwise print:
            print(f"{row['first']} {row['middle']} {row['last']}, born {row['birth']}")

if __name__ == "__main__":
    main()
