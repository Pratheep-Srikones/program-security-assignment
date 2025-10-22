# Program Security Examples

This repository contains examples of common security vulnerabilities and their preventions.

## Files Description

### Buffer Overflow Examples

- `bound-checking.c`: Demonstrates safe input handling with bounds checking to prevent buffer overflow
- `no-range-checking.c`: Shows vulnerable code without range checking, susceptible to buffer overflow
- `stack-smashing.c`: Illustrates a stack smashing vulnerability through buffer overflow
- `variable-overflow.c`: Shows how buffer overflow can affect adjacent variables
- `pointer-variable.c`: Demonstrates how buffer overflow can corrupt function pointers

### Memory Protection

- `canary-implementation.c`: Implements stack canary protection against buffer overflow
- `tagging.c`: Implements memory tagging for protection against unauthorized access

### SQL Injection Examples

- `sql-injection.html` & `sql-injection.py`: Demonstrates vulnerable code susceptible to SQL injection
- `prevent-sql-injection.html` & `prevent-sql-injection.py`: Shows proper input validation and parameterized queries

## Required Commands

### Compile C Programs

All C programs should be compiled with security features disabled to demonstrate vulnerabilities:

```bash
gcc -g -O0 -fno-stack-protector -Wno-deprecated-declarations -Wno-implicit-function-declaration -o program_name program_name.c
```

Example:

```bash
gcc -g -O0 -fno-stack-protector -Wno-deprecated-declarations -Wno-implicit-function-declaration -o bound-checking bound-checking.c
```

### Python Setup

Install required Python packages:

```bash
pip install -r requirements.txt
```

### Database Setup (for SQL examples)

The SQL injection examples use PostgreSQL. Make sure to:

1. Have PostgreSQL installed
2. Create a database named 'testdb'
3. Create a user 'testuser' with password 'test123'
4. Grant necessary permissions
