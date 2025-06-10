# Assignment 5: Public Key Cryptography

## Files Included and Explanations

- DESIGN.pdf - Design files that offers general idea of the purpose of the program and provides pseudocode to give readers a basic idea as to how they would go about coding the program if they wanted to recreate it.
- WRITEUP.pdf - Gives basic outline on how code was tested for functionality and what was learned from completing this assignment.
- decrypt.c - C file that is used to decrypt data given some sort of encrypted data.
- keygen.c - C file that created a public and private key pair that is used to both encrypt and decrypt data.
- numtheory.c - C file that is used to calculate various math operations such as gcd, mod inverse, power mod. Also determines if numbers are prime.
- randstate.c - C file that contains functions needed to initialize a random state that was used to generate random numbers.
- randstate.h - Header file that defines functions in randstate.c.
- rsa.c - C file that is used to create key pairs, encrypt and decrypt files, write to files, and confirm signatures.
- rsa.h - Header file that declares all functions that were needed in rsa.c.
- Makefile - File that is used to compile program.
- encrypt.c - C file that is used to encrypt data given some sort of input data that is to be encrypted.
- README.md - This file. To compile program, use command make. Once compiled, commands such as ./keygen -b 50 -v can be used to set certain parameters for certain files and functions. Some parameters include amount of bits for p and q, number of iterations for is prime test, verbose output, and help screen.

