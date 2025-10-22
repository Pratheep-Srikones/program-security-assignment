#include <stdio.h>
#include <string.h>

//here the memory is allocated contiguously for buffer and isAuthenticated variable
char buffer[32];
int isAuthenticated = 0;

void func(char* input) {
    // No bounds checking is done on input, leading to potential overflow
    // This can exceed the allocated buffer and overwrite the isAuthenticated variable
    strcpy(buffer, input);
}

void checkAuthentication() {
    if (isAuthenticated) {
        printf("Access Granted: You are authenticated!\n");
    } else {
        printf("Access Denied: You are not authenticated.\n");
    }
}

int main(int argc, char* argv[]) {
    checkAuthentication(); //value of isAuthenticated before overflow is 0

    // Input larger than 32 bytes to demonstrate buffer overflow
    char input[33] = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"; // 33 bytes to overflow isAuthenticated
    // Calling the function with large input
    func(input);

    checkAuthentication(); //value of isAuthenticated after overflow may be 1
    return 0;
}