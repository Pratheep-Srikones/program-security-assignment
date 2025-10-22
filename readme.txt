File Descriptions:

bound-checking.c
- Shows safe input reading with size limits
- Prevents buffer overflow by checking boundaries

canary-implementation.c
- Uses a secret value (canary) to detect stack corruption
- Demonstrates stack protection technique

no-range-checking.c
- Shows unsafe code without input size checks
- Example of buffer overflow vulnerability

pointer-variable.c
- Shows how overflow can corrupt function pointers
- Demonstrates control flow attacks

prevent-sql-injection.html/py
- Shows safe way to handle user input
- Uses input validation and prepared statements

sql-injection.html/py
- Shows unsafe database queries
- Demonstrates SQL injection vulnerability

stack-smashing.c
- Shows how buffer overflow can corrupt stack
- Example of stack smashing attack

tagging.c
- Implements memory protection with tags
- Checks tags before memory access

variable-overflow.c
- Shows how buffer overflow affects variables
- Demonstrates data corruption through overflow