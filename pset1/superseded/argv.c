#include <cs50.h>
#include <stdio.h>

int main(int argc, string argv[])
{
    printf("arg 0:  %s\n", argv[0]);
    printf("arg 1:  %s\n", argv[1]);


    if(argc >= 2)
    {
        printf("Hello, ");
        for(int i = 1; argv[i] != '\0'; i++)
        {
            printf("%s ", argv[i]);
        }
        printf("\n");
    }
    else
    {
        printf("Hello world\n");
    }

}