#include <stdio.h>
#include <string.h>
#include <stdint.h>

//function to be called normally
int func(void) {
    printf("Function func called successfully.\n");
    return 0;
}


int main(void) {
    //buffer to hold user input
    char buffer[16];

    //pointer to function, memory is allocated on stack contiguously after buffer
    int (*funcptr)();

    //assignment is done before reading input because only then the input can overwrite the value of funcptr
    funcptr = func;

    //reading input without bounds checking
    //if input exceeds 16 bytes, it can overwrite funcptr
    gets(buffer); 

    //calling the function via function pointer
    //an attacker can exploit this to redirect control flow to malicious function
    //in this case, if funcptr is overwritten, it may lead to segmentation fault
    funcptr();

    return 0;
}

/*gcc -g -O0 -fno-stack-protector     -Wno-deprecated-declarations -Wno-implicit-function-declaration   -o pointer-variable pointer-variable.c*/