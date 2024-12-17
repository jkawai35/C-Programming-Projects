# Assignment 3: I Have a Little Dreidel

## Files Included and Explanations

- DESIGN.pdf - Design files that offers general idea of the purpose of the program and provides pseudocode to give readers a basic idea as to how they would go about coding the program if they wanted to recreate it.
- dreidel.c - Main c file that spins the dreidel and simulates a single game given the amount of players playing and the amount of coins that each player starts with.
- play-dreidel.c - File that takes in arguments via getopt() that allow the user to set player count, starting coins, and the seed that determines how the game will play out. Calls functions in dreidel.c that will run the game. Returns results of the game.
- dreidel.h - Header file that defines functions that are to be referenced by both dreidel.c and play-dreidel.c. Also defines variables for rounds and display that are to be used by both files.
- Makefile - File that is used to compile mathlib-test file.
- mtrand.h - Header file for mtrand.c file that defines functions that set the seed and generate a random number according to the seed.
- mtrand.c - Main c file for mtrand program that sets the seed and generates a random number based on the value of the seed.
- README.md - This file. Describes all files included. To compile and run, use command make to compile, then run ./play-dreidel and use tags -p # for player count, -c # for starting coins, -s # for seed, and (optionally) -v to display who gets eliminated and when. Example command ./play-dreidel -p 4 -s 3 -s 613 -v. This will start a game with 4 players, 3 coins each, seed 613, and display feed on. Calling ./play-dreidel will play a game with default settings.
- WRITEUP.pdf - Written breakdown of each function, and expalins why certain functions, variables, loops, etc. were created. Also offers analysis on certain aspects of the data that the dreidel program returns such as average game length given certain settings, if being a certain position in relation to other players matters, and if there are more or fewer players, the outcome of the game in terms of length is affected.
