#include <stdio.h>
#include <string.h>

void func(char* input) {
    char buffer[32];

    // no range checking is done on input by the strcpy function
    // this can lead to buffer overflow if input exceeds 32 bytes
    // an attacker can exploit this vulnerability to perform stack smashing attacks
    strcpy(buffer, input);
}

int main(int argc, char* argv[]) {
    // input larger than 32 bytes to demonstrate lack of range checking
    char input[64] = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";

    // calling the function with large input
    func(input);

    return 0;
}