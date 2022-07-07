/****
 * @author: William Bernal
 * @date: May 20, 2020
 * @email: bern0295@algonquinlive.com
 **** */

#include<stdio.h>
#include<cs50.h>

int main(void)
{
    // Define three constants for space ' ', hash '#' and the gap between the first hash inthe right side and the first has in the left side
    const char SPACE = ' ';
    const char HASH = '#';
    const int GAP = 4;

    // Define variable numBlock to hold the number that the user will enter,
    //spaceLeft will hold the number of spaces on the lef. It will be decremented for each row
    //space right will hold the number of spaces on the right, it will incremented for each row

    int numBlocks = 0;
    int spaceLeft = 0;
    int spaceRight = 0;

    // do while loops to get a number between 1 and 8
    do
    {

        // get th number of blocks an integer between 1 and 8
        numBlocks = get_int("Input the number of blocks (integer 1 - 8)\n");

    }
    while ((numBlocks < 1) | (numBlocks > 8));  // ask for the number until the user enter an integer between 1 and 8

    spaceLeft = numBlocks - 1;
    spaceRight = numBlocks + GAP;

    // start a loop to represent the rows vertically
    for (int i = 1; i <= numBlocks; i++)
    {
        // start a loop to represent the number of character for each row
        for (int j = 1; j <= ((numBlocks * 2) + 2); j++)
        {
            // decides if should print a hash or space o a gap.
            if (j <= spaceLeft |  j == (numBlocks + 1) | j == (numBlocks + 2))
            {
                printf("%c", SPACE);
            }
            else
            {
                // if j i lower than he number of blocks and grater than spacelef imdex, then print a hash

                if (j <= numBlocks)
                {
                    printf("%c", HASH);
                }
                // else if the index j is greater than numblocks + 2 (plus 2 spaces between each pyramid) the print a hash
                // print a hash if the index j is lower than spaceRight.  spaceRight is incrementes each row
                else if ((j > (numBlocks + 2)) & (j < spaceRight))
                {
                    printf("%c", HASH);
                }
            }
        }
        // print new line
        printf("\n");

        // decrement the left space index
        spaceLeft--;

        // increment the right space index
        spaceRight++;
    }
}