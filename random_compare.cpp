#include <iostream>
#include <ctime>
#include <vector>

#import "card_compare.h"

int main() {
    std::vector<Card> deck = createDeck();
    
    // Seed random number generator and shuffle the card deck
    std::srand(unsigned(std::time(0)));
    std::random_shuffle(deck.begin(), deck.end(), randomNum);
    
    // Deal each hand (aces high, or aces = 12)
    std::vector<Card> hand1(deck.begin(), deck.begin()+5);
    std::vector<Card> hand2(deck.begin()+5, deck.begin()+10);
    
    std::cout << "<============== PRINTING HAND 1 ==============>" << std::endl;
    printCards(hand1);
    std::cout << "<============== PRINTING HAND 2 ==============>" << std::endl;
    printCards(hand2);
    
    int result = compareHands(hand1, hand2);
    
    std::cout << "compareHands result: " << result << std::endl;
    
    return 1;
}
