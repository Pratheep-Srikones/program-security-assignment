#include <stdio.h>
#include <string.h>

//here the function 'func' is vulnerable to stack smashing attack 
void func(char *input) {
    //here only 32 bytes are allocated for buffer 
    char  buffer[32];

    //here no bounds checking is done on input, leading to potential overflow
    //this can exceed the alllocated buffer for argument and overwrite return address
    //an attacker can exploit this to change the control flow of the program to execute malicious code
    strcpy(buffer, input);

    printf("Buffer content: %s\n", buffer);
}


int main(int argc, char *argv[]) {

    //input larger than 32 bytes to demonstrate stack smashing
    char input[64] = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";

    //calling the vulnerable function with large input
    //in this case, the overflow will trigger segmentation fault but in other cases it may lead to arbitrary code execution
    func(input);
    
    return 0;
}