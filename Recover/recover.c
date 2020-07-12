#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

// https://cs50.harvard.edu/x/2020/psets/4/recover/

 // give the type "uint8_t" the nickname BYTE. uint8_t is an 8 bit unsigned integer. made of 8 bits or 1 byte in binary (1111 1111)
typedef uint8_t BYTE;

 // main() takes in the name of the card.raw as argv[1] at the users command line, as a pointer to an array of characters in memory (char *).
int main(int argc, char *argv[])
{
    // create a buffer of 512 elements (of which, each element is of size 1 byte (uint8_t))
    BYTE buffer[512];

    // ensure the user enters the correct amount of command line arguments at the terminal
    if (argc != 2)
    {
        printf("invalid input, please enter ./recover card.raw");
        return 1;
    }

    // use fopen() to: 1. create a new file. 2. open the card.raw with the same name in argv[1]. 3. then create a file pointer to this card.raw "ptr_memcard"
    FILE *ptr_memcard = fopen(argv[1], "r");

    // check to ensure "ptr_memcard" is not returning a NULL value. If it's NULL, the file does not exist, and will result in an error. we can't derefernce a null pointer without a seg fault.
    if (ptr_memcard == NULL)
    {
        printf("Error, could not open ./recover ");
        return 1;
    }

    int counter = 0;  // create a counter variable to count through each JPEG file being written to.
    char filename[8];    // create an array of size 8 for every potential "filename" string for the jpgs + the null terminator. eg 024.jpg. 0 [0] 2 [1] 4 [2] . [3] j [4] p [5] g [6] "\0" [7]
    bool already_found = false; // set a flag to signify that we have already found a JPG to: FALSE;
    FILE *ptr_jpg = NULL;  // create a pointer we will use to point to jpg files further down. also set the FILE* pointer variable to point to a null value in memory

    // loop through each 512 byte block fromt he card.raw, while there are >= 512 bits in each block, read each block from the card.raw into the buffer at a time
    while (fread(buffer, sizeof(BYTE), 512, ptr_memcard) >= 512)
    {
        // check the beggining 4 bits of this 512 bit block from the card.raw to see if its teh start of a jpg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // if a jpg has already been found in a previous loop
            if (already_found == true)
            {
               fclose(ptr_jpg);  // fclose() the previous JPG file* being pointed to by using the ptr_jpg pointer
            }
            else
            {
                already_found = true;
            }

            sprintf(filename, "%03i.jpg", counter);  // use sprintf() to create a new filename CURRENT COUNTER.jpeg for our new jpeg we want to copy into; (use sprintf function to do this)
            ptr_jpg = fopen(filename, "w");  // fopen(): 1. creates a new file. 2. points the pointer variable "ptr_jpg" to this created file. 3. then ensures we open this FILE with "write" permissions
            counter++; // update current counter + 1 each time we loop through
        }

        if (already_found == true)
        {
            fwrite(buffer, sizeof(BYTE), 512, ptr_jpg);  // use frwite() to: 1. write the block we read from the buffer 2. into the file being pointed to by ptr_jpg
        }
    }
    // fclose() the previous JPG file* being pointed to by ptr_jpg when the while loop completes +  fclose() the memory card itself
    fclose(ptr_jpg);
    fclose(ptr_memcard);
    return 0;
}
