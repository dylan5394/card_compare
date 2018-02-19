# card_compare
C++ program to compare 5 card poker hands


## Set up:
1. Install necessary command line tools on your OS for compiling C++
2. git clone git@github.com:dylan5394/card_compare.git
3. cd card_compare
4. make (ensure you ran this before trying to test or run random comparison!) 

## To test:
1. cd tests
2. ./test

## To run random hand comparison:
1. cd src
2. ./random_compare


## Notes:

The program does not deal wildcards or account for wildcards. Only cards valued 0 (Two) to  12 (Ace) are used. Thus 5 of a kind is not possible to attain through the random comparison program.

The program assumes aces can be high or low so the compare function will analyze the hand twice: one time where the aces in the hand are low, and another time where they are high. The hand version (aces in high or low position) that produces a more desirable ranking is compared.