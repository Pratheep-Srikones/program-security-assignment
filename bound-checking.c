#include <stdio.h>
#include <stddef.h>

//this function reads input from stdin into buffer with bounds checking
//it truncates large input to fit into the buffer safely
//it prevents buffer overflow vulnerabilities and stack smashing attacks
int read_and_bound_check(char *buffer, size_t buffer_size) {
    if (buffer_size <= 0) return -1;
    size_t i = 0;
    int ch;

    while ((ch = getchar()) != EOF && ch != '\n') {
        if (i < buffer_size -1) {
            buffer[i] = (char)ch;
            i++;
        } else {
            //buffer full, truncate input and add null terminator
            buffer[buffer_size - 1] = '\0'; 
            return 1;
        }
    }
    buffer[i] = '\0';
    return 0;
}

int main() {
    char buffer[16];
    //read input with bounds checking
    //use the result as needed
    int result = read_and_bound_check(buffer, sizeof(buffer));

    //similar bound checking is used in safer fgets() function
    char safe_buffer[16];
    fgets(safe_buffer, sizeof(safe_buffer), stdin);
    
    return 0;
}

/*gcc -g -O0 -fno-stack-protector     -Wno-deprecated-declarations -Wno-implicit-function-declaration   -o bound-checking bound-checking.c */