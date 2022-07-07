/****
 * @author: William Bernal
 * @date: May 28, 2020
 * @email: bern0295@algonquinlive.com
 * @program: credit.c
 **** */

#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(void)
{
    // define a variable to gets the credit card number
    unsigned long creditCardNumber = get_long("Number: ");
    // will get the head of credit card after truncate the last digit
    unsigned long head = creditCardNumber;
    // will get the last digit after apply the module operator
    unsigned long tail = 0;
    // will get the sum of digits that weren't multiply by 2
    int sumWerentMultiply = 0;
    // will get the sum of digits multipiedy by 2
    int sumProductsBy2 = 0;
    // will get the total number of digits
    int numDigist = 0;
    // will get the most left two digist to calcuylate the credit card brand
    int numBrand = 0;
    int flag = 0;
    // will show teh brand result or "INVALID"
    string brand = "INVALID";
    // Loop to read digit by digit
    while (head > 0)
    {
        // getthe the last digit
        tail = head % 10;
        // getthe the remaining digits but the last one
        head = head / 10;
        // if flag == 0 multiply every other digit by 2
        if (flag == 0)
        {
            sumWerentMultiply += tail;
            flag = 1;
        }
        else
        {
            // if tail > 10 means that the mutiplication result in more than one digit i.e.12
            if (tail > 4)
            {
                sumProductsBy2 += (tail * 2) % 10;
                sumProductsBy2 += (tail * 2) / 10;
            }
            else
            {
                sumProductsBy2 += (tail * 2);
            }
            flag = 0;
        }

        if (head >= 34 && head <= 55)
        {
            numBrand = head;
        }
        numDigist++;
    }
    int checksum = (sumWerentMultiply + sumProductsBy2) % 10;
    brand = (checksum != 0) ? "INVALID" : brand;

    // if checksum == 0 verify the leng for each credit card
    // and assign the corresponding brand
    if (checksum == 0)
    {
        if (numBrand >= 40 & numBrand <= 49 && (numDigist == 16 || numDigist == 13))
        {
            brand = "VISA";
        }
        else if (numBrand >= 51 && numBrand <= 55 && numDigist == 16)
        {
            brand = "MASTERCARD";
        }

        else if ((numBrand == 34 | numBrand == 37) && (numDigist == 15))
        {
            brand = "AMEX";
        }
    }
    // print the result
    printf("%s\n", brand);
}