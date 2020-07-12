import sys
import csv
from cs50 import SQL

# https://cs50.harvard.edu/x/2020/psets/7/houses/

def main():

	if len(sys.argv) != 2:
		print("Invalid usage, please enter: python import.py characters.csv")
		sys.exit(1)

    # give us access to the students db within our python script
	db = SQL("sqlite:///students.db")

    # open up the CSV file that was passed in as a command line argument & begin to read this csv file, row by row with a dictreader
	with open(sys.argv[1], newline='') as characters_csv_file:
		csv_reader = csv.DictReader(characters_csv_file)

		# loop through for each row being read in dictreader
		for row in csv_reader:
			# pick the first keyvalue pair from this dictionary, parse the students name in this keyvaluepair, use split method in python to split the string in this keyvaluepair into multiple words, where there are spaces
			split_name = row["name"].split()
			# check after doing this split, if the amount of names in the first keyvaluepair = 3
			if len(split_name) == 2:
				# insert 'None' in the list at "split_name[1]" between this students first "split_name[0]" and last "split_name[2]" to make a null the middle value
				split_name.insert(1, None)

            # INSERT a row into the dbs table from the current row of keyvaluepairs, last and middle name (along with their house + birth)
			db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?);",
				split_name[0], split_name[1], split_name[2], row["house"], row["birth"])

if __name__ == "__main__":
    main()
