/****
 * @author: William Bernal
 * @date: June 07, 2020
 * @email: bern0295@algonquinlive.com
 * @program: substitution.c
 * @aim:  Read a text and oput the ciphered version
 **** */

#include <cs50.h>
#include <stdio.h>
#include <string.h>

int validateKey(string key);

int main(int argc, string argv[])
{
    // gets the string
    string key = argv[1];

    //this constant will be used to show an error in the Key
    const string ERRORMESSAGE = "Invalid key - Must contain 26 different letters";

    //verify the Key
    if (!(argc == 2) || (validateKey(key) == 1))
    {
        // if Key is wrong, shows the constant error
        printf("%s\n", ERRORMESSAGE);
        return 1;
    }
    else
    {
        // if the Key is correct, gets the plainText
        string plaintext = get_string("plaintext: ");

        // creates a string with the same lenght as the plaintext
        string cipherText = plaintext;

        // for each character in plaintext
        for (int i = 0; plaintext[i] != '\0'; i++)
        {
            // get the index position of the textplain char in the Key array.
            int index = ((int)plaintext[i] >= 65 && (int)plaintext[i] <= 90) ? ((int)plaintext[i]  - 64) :
                        ((int)plaintext[i] >= 97 && (int)plaintext[i] <= 122) ? ((int)plaintext[i]  - 96) : (int)plaintext[i];

            // if it is a letter a-z or A - Z
            if (((int)plaintext[i] >= 65 && (int)plaintext[i] <= 90) || ((int)plaintext[i] >= 97 && (int)plaintext[i] <= 122))
            {
                int numAsciiKeyChar = (int)key[index - 1];

                //  normalize UPPERCASE and LOWERCASE between plainText and Key
                if (((int)plaintext[i] <= 90) && ((int)key[index - 1] >= 96))
                {
                    cipherText[i] = (char)(((int)key[index - 1]) - 32);
                }
                else if (((int)plaintext[i] >= 96) && ((int)key[index - 1] <= 90))
                {
                    cipherText[i] = (char)(((int)key[index - 1]) + 32);
                }
                else
                {
                    cipherText[i] = key[index - 1];
                }

            }
            // if the char in plaintext is not a letter, doesn't cipher
            else
            {
                cipherText[i] = plaintext[i];
            }

        }
        // prints the result
        printf("ciphertext: %s\n", cipherText);
    }
}

int validateKey(string key)
{
    // result == 1 means error result == 0 means the key is valid
    int result = 1;
    int numCharsinKey = 0;

    for (int i = 0; key[i] != '\0'; i++)
    {
        numCharsinKey++;

        if (key[i] < 65  || (key[i] > 90 && key[i] < 97) || (key[i] > 122))
        {
            return 1;
        }

        for (int j = i + 1; key[j] != '\0'; j++)
        {
            if (key[i] == key[j])
            {
                return 1;
            }
        }

    }

    if (numCharsinKey != 26)
    {
        return 1;
    }

    return 0;
}
