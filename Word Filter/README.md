# Assignment 6: The Great Firewall of Santa Cruz: Bloom Filters, Linked Lists, and Hash Tables

## Files Included and Explanations

- DESIGN.pdf - Design file that offers general idea of the purpose of the program and provides pseudocode to give readers a basic idea as to how they would go about coding the program if they wanted to recreate it.
- WRITEUP.pdf - Covers what was learned from doing the assignment and answers questions regarding to functionality to analyze various topics related to the program itself such as its shortcomings.
- banhammer.c - C file that is used to read in newspeak, oldspeak, and badspeak, and compare them to user input to see if they are guilty of thoughtcrime. Also prints out stats that is related to how the program came to its verdict.
- city.c - C file that contains the hash functions that were used to calculate the index of certain data structures such as bloom filters and hash tables.
- bv.c - C file that contains the struct as well as the functions needed to use a bitvector. These functions are called in bf.c as that file creates a bit vector that is used to determine if oldspeak values are already set.
- bf.c - C file that contains the struct as well as the functions needed to use a bloom filter. Uses functions defined in bv.c to maintain a bit vectors within a bloom filter.
- node.c - C file that contains the struct as well as the functions needed to use a node. Nodes are created as to be a part of a linked list. ll.c will refer to functions in this file to create and use a linked list.
- ll.c - C file that contains the struct as well as the functions needed to use a linked list. Uses node.c to create nodes that will be inserted into the linked list. Linked list nodes can point to both previous and next nodes.
- ht.c - C file that contians the stuct as well as the functions needed to use a hash table. Uses node.c and ll.c to maintain multiple linked lists within a hash table.
- parser.c - C file that contains the struct as well as the functions needed to use a parser. Mainly uses a function called next word that finds the next valid word of a file passed into the parser.
- city.h - Contains the function declarations for city.h that are used by multiple other source code files.
- bf.h - Contains the struct and function definitions for the bloom filter C file.
- bv.h - Contains the struct and function definitions for the bit vector C file.
- node.h - Contains the struct and function definitions for the node C file.
- ll.h - Contains the struct and function definitiions for the linked list C file.
- ht.h - Contains the struct and function definitions for the hash table C file.
- parser.h - Contains the struct and function definitions for the parser C file.
- messages.h - Contains the messages that are to be printed depending on the words the user inputs.
- Makefile - File that compiles all the source code files together. Use command make to do so. Can run make all, make clean, and make spotless.
- README.md -This file. Contains information about all of the files included. To run program use command make. Then either type ./banhammer with any of the options and type in words manually, or you can use premade words by piping it with ./banhammer followed by any options.

## Outside Sources Used
- Scaler Topics for string comparison with pointers www.scaler.com/topics/c/string-comparison-in-c/
- Stack Overflow used for string copy 

