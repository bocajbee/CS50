import sys # import sys module allowing us to give command line arguments to our python progam
import csv # import the CSV module that contains the reader which will load our database.CSV file


def main():

    # if there are not 3 command line arguments
    if len(sys.argv) != 3:
        print("Invalid usage, please enter: python dna.py data.csv sequence.txt")
        sys.exit(1) # exit

    # open() the large.csv database file under databases/ subdirectory + user input at command line in [2]nd command line argument
    with open(sys.argv[1], newline='') as csv_file:

        # open CSV with dictreader, generate my own list from the headerof the CSV, then using the .fieldnames we collected in our previous list,
        # make my own dictionary from this list "csv_header_counter" to store counters in for each STR Type. set the value at each keyvalue pair in this dict to 0
        csv_reader = csv.DictReader(csv_file)
        header = csv_reader.fieldnames
        csv_header_counter = dict.fromkeys(header , 0)

        # open the DNA sequence text file + read it's string into a "line" stored in memory
        with open(sys.argv[2], newline='') as text_file:
            line = text_file.readline()
            line_len = len(line)

        # outer nested forloop (through each of the my_custom_dictionary{'KEYS'} (The "STR_Types")
        for key in csv_header_counter:
            # # if the current key == 'name'
            if key == 'name':
                # run the outer loop 1x more time (and only 1x more time until key != name anymore)
                continue;
            x = len(key)
            print(f"The lengh of this key (value of x) is {x}")

            # inner nested forloop through the STRING in the line from the text file 1 char at a time
            for j in range(0, line_len, 1):
                counter = 0
                if line[j: j + x] == key:
                    # start = [j]th index in string of line + the value of x (len of key) + 1
                    start = j + x
                    # end = [j]th index in string of line + the value of x (len of key) + 1 + the value of x
                    end = j + x + x
                    # linked_STR = line from start through to end
                    linked_STR = line[start: end]

                    while linked_STR == key:
                        # set "start" inside of this loop to become "start" + the value of x (len of key) + 1, to move across the STR text file to check the next back to back STR
                        start = start + x
                        # set "end" inside of this loop to become "end" + the value of x (len of key) + 1, to move across the STR text file to check the next back to back STR
                        end = end + x
                        linked_STR = line[start: end]
                        counter += 1
                    # +1 counter outside the while loop indicating a link exists between the first str_type checked and the second one
                    counter += 1

                    if counter >= csv_header_counter[key]:
                        csv_header_counter[key] = counter

        # loop through both dictionaries looking for a match + print name of any matches found
        # loop through each row of the CSV file, and save each row into a dict
        for row in csv_reader:
            match_found = True
            # loop through for every key in my index
            for key in csv_header_counter:
                # # if the current key == 'name'
                if key == 'name':
                    # run the outer loop 1x more time (& only 1x more time until key != name)
                    continue;
                # Check the keyvaluepair at this current row at index reference [key] Does NOT match with The integer value stored at the current keyvaluepair from csv_header_counter[key] being looped though in in the outer loop.
                if int(row[key]) != csv_header_counter[key]:
                    match_found = False
                    break
            if match_found == True:
                print(row["name"])
                sys.exit(1)
        print("No match")

if __name__ == "__main__":
    main()
