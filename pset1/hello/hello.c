#include<stdio.h>

// used to include the function get_string
#include<cs50.h>

int main(void)
{
    // get thename of the user
    string name = get_string("Whats' your name buddy?\n");

    //Greeting the user by hr/his name
    printf("Hello %s \n", name);
}