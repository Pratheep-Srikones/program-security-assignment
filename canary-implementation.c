#include <stdio.h>
#include <string.h>

//defining a unique(secret) canary value 
//should be hard to guess, not easily reproducible and random each run
const char *canary = "Ab3#G7kL9pQ2@Z1";

//input buffer which is vulnerable to overflow
char input_buffer[32];

//buffer to hold the canary value
char canary_buffer[16];

//variable which should not be altered by overflow
int isAuthenticated = 0;



int main(void) {

    printf("Value of isAuthenticated before overflow is %d\n", isAuthenticated); //value should be 0/
   
    //storing the canary value before reading input
    //should not store after reading input as it will get overwritten and always match
    strcpy(canary_buffer, canary);

    //vulnerable input read without bounds checking
    gets(input_buffer); 

    //checking if canary value is altered after input read
    //should check after any altering to input_buffer to detect overflow
    if (strcmp(canary_buffer, canary) != 0) {
        //if canary is altered, it indicates buffer overflow and stack smashing attempt
        printf("Stack smashing detected! Exiting program.\n");
        return -1;
    }

    printf("Value of isAuthenticated after overflow is %d\n", isAuthenticated); //value should be 0/

    return 0;
}

/*gcc -g -O0 -fno-stack-protector     -Wno-deprecated-declarations -Wno-implicit-function-declaration   -o canary-implementation canary-implementation.c*/