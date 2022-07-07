/****
 * @author: William Bernal
 * @date: May 31, 2020
 * @email: bern0295@algonquinlive.com
 * @program: readability.c
 * @aim:  takes a text and determines its reading level
 **** */
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int main(int argc, string argv[])
{
    // Declares the main COLEMAN-LIAU factors as a constant
    const float COLEMANLIAU_FACTOR_1 = 0.0588;
    const float COLEMANLIAU_FACTOR_2 = 0.296;
    const float COLEMANLIAU_FACTOR_3 = 15.8;

    // will be used to print when the grade rages greater than 15
    const string GRADE16PLUS = "Grade 16+";

    // will be used to print the result, when the result ranges lower than 1
    const string BEFOREGRADE1 = "Before Grade 1";

    // variables to calculate the result
    float avgLetterPer100Words = 0;
    float avgSentencesPer100Words = 0;
    float result = 0;


    int lastChar = 0;
    double numWords = 0;
    double numLetters = 0;
    double numSentences = 0;
    int numSpacestogheter = 0;
    int numDotsExclamMarks = 0;
    int numLettersInaSingleWord = 0;

    // gets the string
    string text = get_string("Text: ");

    for (int i = 0; text[i] != '\0'; i++)
    {
        // If the char i equals to an space
        if ((int)text[i] == 32)
        {
            // Increments the number of spaces togheter.
            // it is used to control that the Text could have multiple spaces in a line like "       "
            // in that case only oe word must be counted
            numSpacestogheter++;
            numDotsExclamMarks = 0;
            numLettersInaSingleWord = 0;

            // Only if it is the first space increment the number of words
            if (numSpacestogheter == 1)
            {
                numWords++;
            }
        }
        // If the char is a leter Ascii (65 - 90 for uppercase) (97 - 122 for lowercase)
        else if (((int)text[i] >= 65 && (int)text[i] <= 90) || ((int)text[i] >= 97 && (int)text[i] <= 122))
        {
            numLetters++;
            numLettersInaSingleWord++;

            // reset the numSpacestogheter and Num of numDotsExclamMarks
            // numDotsExclamMarks will be used to count the number of sentences
            numSpacestogheter = 0;
            numDotsExclamMarks = 0;
        }
        // if the char is a dot, exclamation marck or question mark
        // we identify it as a new sentence.
        // only if the number of letter togheter are greater than 3 letters.
        // it is to avoid cases as Mr. Mrs. etc. Ave. to avoid
        // sigles to be counted as a full sentence
        else if ((int)text[i] == 46 || (int)text[i] == 33 || (int)text[i] == 63)
        {
            // increments the number of numDotsExclamMarks
            // it is used to control that the text could have multiple numDotsExclamMarks in a line like "....", "!!!", "???"
            // In that case only one sentence must be counted
            numDotsExclamMarks++;
            if (numDotsExclamMarks == 1 && numLettersInaSingleWord > 3)
            {
                numSentences++;
            }
            numLettersInaSingleWord = 0;
            numSpacestogheter = 0;
        }

        //saves the last char of the text to control after the for loop if we need to add a new word.
        lastChar = (int)text[i];
    }

    // if the last char is different than a space (32),
    // it means that a new word must be counted.
    // (related with the the code line # 92)
    // if the last line is different than a space do nothing
    if (lastChar != 32)
    {
        numWords++;
    }
    //calcuate the averageof letters per a 100 words
    avgLetterPer100Words = ((float)numLetters / (float)numWords) * 100;

    //calcuate the average of sentences per a 100 words
    avgSentencesPer100Words = ((float)numSentences / (float)numWords) * 100;

    //calcuate the result using the COPLEMAN & LIAU factors
    result = (COLEMANLIAU_FACTOR_1 * avgLetterPer100Words - COLEMANLIAU_FACTOR_2 * avgSentencesPer100Words - COLEMANLIAU_FACTOR_3);

    // print the results
    if (result < 1)
    {
        printf("%s\n", BEFOREGRADE1) ;

    }
    else if (result >= 16)
    {
        printf("%s\n", GRADE16PLUS);
    }
    else
    {
        printf("Grade %.0f\n", result);
    }

    /*
    *  end of the program Cretaed By William Bernal.
    */
}
