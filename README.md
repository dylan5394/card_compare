# card_compare
C++ program to compare 5 card poker hands


## Set up:
Install necessary command line tools on your OS for compiling C++
git clone git@github.com:dylan5394/card_compare.git
cd card_compare
make (ensure you ran this before trying to test or run random comparison!) 

## To test:
cd tests
./test

## To run random hand comparison:
cd src
./random_compare


## Notes:

The program does not deal wildcards or account for wildcards. Only cards valued 0 (Two) to  12 (Ace) are used. Thus 5 of a kind is not possible to attain through the random comparison program.

The program assumes aces can be high or low so the compare function will analyze the hand twice: one time where the aces in the hand are low, and another time where they are high. The hand version (aces in high or low position) that produces a more desirable ranking is compared.