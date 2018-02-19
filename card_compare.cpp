#include <iostream>
#include <vector>
#include <ctime>

enum Rank { Ace, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King };

enum Suit { Hearts, Diamonds, Spades, Clubs };

enum HandRank { FiveOfAKind, StraightFlush, FourOfAKind, FullHouse, Flush, Straight, ThreeOfAKind, TwoPair, OnePair, HighCard };

struct Card {
    int value;
    int suit;
    
    bool operator < (const Card& card) const {
        return (value < card.value);
    }
    
    bool operator > (const Card& card) const {
        return (value > card.value);
    }
    
    bool operator == (const Card& card) const {
        return (value == card.value);
    }
    
    bool operator != (const Card& card) const {
        return (value != card.value);
    }
};

int myrandom (int i) { return std::rand()%i; }

bool flush(std::vector<Card>& hand) {
    int i = 0;
    while(i < 4 && hand[i].suit == hand[i+1].suit) i ++;
    return i == 4;
}

bool straight(std::vector<Card>& hand) {
    int i = 0;
    while(i < 4 && hand[i].value + 1 == hand[i+1].value) i ++;
    return i == 4;
}

bool fiveOfAKind(std::vector<Card>& hand) {
    return hand[0] == hand[4];
}

bool straightFlush(std::vector<Card>& hand) {
    return flush(hand) && straight(hand);
}

bool fourOfAKind(std::vector<Card>& hand) {
    return hand[0] == hand[3] || hand[1] == hand[4];
}

bool fullHouse(std::vector<Card>& hand) {
    return (hand[0] == hand[1] && hand[2] == hand[4]) || (hand[0] == hand[2] && hand[3] == hand[4]);
}

bool threeOfAKind(std::vector<Card>& hand) {
    return hand[0] == hand[2] || hand[1] == hand[3] || hand[2] == hand[4];
}

bool twoPair(std::vector<Card>& hand) {
    return (hand[0] == hand[1] && hand[2] == hand[3]) || (hand[1] == hand[2] && hand[3] == hand[4]) || (hand[0] == hand[1] && hand[3] == hand[4]);
}

bool onePair(std::vector<Card>& hand) {
    return hand[0] == hand[1] || hand[1] == hand[2] || hand[2] == hand[3] || hand[3] == hand[4];
}

int highCard(std::vector<Card>& hand) {
    return hand[hand.size()-1].value;
}

int getHandValue(std::vector<Card>& hand) {
    int handValue;
    if(fiveOfAKind(hand)) handValue = FiveOfAKind;
    else if(straightFlush(hand)) handValue = StraightFlush;
    else if(fourOfAKind(hand)) handValue = FourOfAKind;
    else if(fullHouse(hand)) handValue = FullHouse;
    else if(flush(hand)) handValue = Flush;
    else if(straight(hand)) handValue = Straight;
    else if(threeOfAKind(hand)) handValue = ThreeOfAKind;
    else if(twoPair(hand)) handValue = TwoPair;
    else if(onePair(hand)) handValue = OnePair;
    else handValue = HighCard + (12 - highCard(hand));
    return handValue;
}

int compareHands(std::vector<Card>& hand1, std::vector<Card>& hand2) {
    /*
     
    Return 1 if hand1 is of better rank than hand2, 0 if they are equal, or -1 if hand1 is of worse rank than hand2
     
    Compare each hand's main rank (4 of a kind, straight, etc...) then find their kickers and other significant values if the main ranks are the same
     
     Kicker(s) are the cards in each hand which contribute no significance to the hand's main rank
        i.e. the remaining card in a 4 of a kind or one of the three other cards in a one pair
     
     */
    
    std::vector<int> hand1Vec(13, 0);
    std::vector<int> hand2Vec(13, 0);
    
    for(Card card : hand1) {
        hand1Vec[card.value] ++;
    }
    
    for(Card card : hand2) {
        hand2Vec[card.value] ++;
    }

    int hand1Val = getHandValue(hand1);
    std::cout << "Hand 1 value: " << hand1Val << std::endl;
    int hand2Val = getHandValue(hand2);
    std::cout << "Hand 2 value: " << hand2Val << std::endl;
    
    // If hand 1 and hand 2 have different rankings, return 1 if hand 1 ranks better otherwise -1
    if(hand1Val != hand2Val) return hand1Val < hand2Val ? 1 : -1;
    
    // Hand 1 and hand 2 rank the same, so we have to find potential tie breaker conditions
    if(hand1Val == FiveOfAKind) {
        // Find which card value each 5 of a kind is composed of
        if(hand1[0] > hand2[0]) return 1;
        else if(hand1[0] == hand2[0]) return 0;
        return -1;
    } else if(hand1Val == StraightFlush) {
        // Find which straight, if any, has higher values
        if(hand1[0] > hand2[0]) return 1;
        else if(hand1[0] == hand2[0]) return 0;
        return -1;
    } else if(hand1Val == FourOfAKind) {
        // Find the 4 of a kind composition, then the kicker if they are composed of the same card value
        Card hand1HighCard = hand1[1];
        Card hand2HighCard = hand2[1];
        
        if(hand1HighCard > hand2HighCard) return 1;
        else if(hand1HighCard == hand2HighCard) {
            Card hand1Kicker;
            Card hand2Kicker;
            
            if(hand1[0] == hand1[1]) hand1Kicker = hand1[4];
            else hand1Kicker = hand1[0];
            
            if(hand2[0] == hand2[1]) hand2Kicker = hand2[4];
            else hand2Kicker = hand2[0];
            
            if(hand1Kicker != hand2Kicker) return hand1Kicker > hand2Kicker ? 1 : -1;
            else if(hand1Kicker == hand2Kicker) return 0;
            return -1;
        }
        return -1;
        
    } else if(hand1Val == FullHouse) {
        // Find what card values compose each hands pair and three of a kind
        Card hand1Triple;
        Card hand2Triple;
        
        hand1Triple = hand1[2];
        hand2Triple = hand2[2];
        
        if(hand1Triple > hand2Triple) return 1;
        else if(hand1Triple == hand2Triple) {
            Card hand1Pair;
            Card hand2Pair;
            
            if(hand1[0] == hand1[2]) hand1Pair = hand1[3];
            else hand1Pair = hand1[0];
            
            if(hand2[0] == hand2[2]) hand2Pair = hand2[3];
            else hand2Pair = hand2[0];
            
            if(hand1Pair > hand2Pair) return 1;
            else if(hand1Pair == hand2Pair) return 0;
            return -1;
        }
        return -1;
    } else if(hand1Val == Flush) {
        // Compare kicker values in each flush
        for(int i = 4; i <= 0; i ++) {
            if(hand1[i] > hand2[i]) return 1;
            else if(hand1[i] < hand2[i]) return -1;
        }
        return 0;
    } else if(hand1Val == Straight) {
        // Find which straight, if any, has higher values
        if(hand1[0] > hand2[0]) return 1;
        else if(hand1[0] == hand2[0]) return 0;
        return -1;
    } else if(hand1Val == ThreeOfAKind) {
        // Compare three of a kind composition card
        // If equal, compare kickers
        if(hand1[2] > hand2[2]) return 1;
        else if(hand1[2] == hand2[0]) {
            std::pair<int, int> hand1KickerIndices;
            std::pair<int, int> hand2KickerIndices;
            
            if(hand1[2] == hand1[0]) hand1KickerIndices = std::make_pair(3, 4);
            else if(hand1[2] == hand1[1] && hand1[2] == hand1[3]) hand1KickerIndices = std::make_pair(0, 4);
            else hand1KickerIndices = std::make_pair(0, 1);
            
            if(hand2[2] == hand2[0]) hand2KickerIndices = std::make_pair(3, 4);
            else if(hand2[2] == hand2[1] && hand2[2] == hand2[3]) hand2KickerIndices = std::make_pair(0, 4);
            else hand2KickerIndices = std::make_pair(0, 1);
            
            if(hand1[hand1KickerIndices.second] > hand2[hand2KickerIndices.second]) return 1;
            else if(hand1[hand1KickerIndices.second] == hand2[hand2KickerIndices.second]) {
                if(hand1[hand1KickerIndices.first] > hand2[hand2KickerIndices.first]) return 1;
                else if(hand1[hand1KickerIndices.first] == hand2[hand2KickerIndices.first]) return 0;
                return -1;
            }
            return -1;
        }
        return -1;
    } else if(hand1Val == TwoPair) {
        // Compare each pair composition card
        // If both are equal, compare kickers
        Card hand1HighPair;
        Card hand2HighPair;
        
        Card hand1LowPair;
        Card hand2LowPair;
        
        Card hand1Kicker;
        Card hand2Kicker;
        if(hand1[0] == hand1[1]) {
            hand1LowPair = hand1[0];
            if(hand1[2] == hand1[3]) {
                hand1HighPair = hand1[2];
                hand1Kicker = hand1[4];
            } else {
                hand1HighPair = hand1[4];
                hand1Kicker = hand1[2];
            }
        } else {
            hand1LowPair = hand1[1];
            hand1HighPair = hand1[3];
            hand1Kicker = hand1[0];
        }
           
        if(hand2[0] == hand2[1]) {
            hand2LowPair = hand2[0];
            if(hand2[2] == hand2[3]) {
                hand2HighPair = hand2[2];
                hand2Kicker = hand2[4];
            } else {
                hand2HighPair = hand2[4];
                hand2Kicker = hand2[2];
            }
        } else {
            hand2LowPair = hand2[1];
            hand2HighPair = hand2[3];
            hand2Kicker = hand2[0];
        }
           
        if(hand1HighPair > hand2HighPair) return 1;
        else if(hand1HighPair == hand2HighPair) {
            if(hand1LowPair > hand2LowPair) return 1;
            else if(hand1LowPair == hand2LowPair) {
                if(hand1Kicker > hand2Kicker) return 1;
                else if(hand1Kicker == hand2Kicker) return 0;
                return -1;
            }
            return -1;
        }
        return -1;
    } else if(hand1Val == OnePair) {
        Card hand1Pair;
        Card hand2Pair;
        
        if(hand1[0] == hand1[1]) hand1Pair = hand1[0];
        else if(hand1[1] == hand1[2]) hand1Pair = hand1[1];
        else hand1Pair = hand1[3];
        
        if(hand2[0] == hand2[1]) hand2Pair = hand2[0];
        else if(hand2[1] == hand2[2]) hand2Pair = hand2[1];
        else hand2Pair = hand2[3];
        
        if(hand1Pair > hand2Pair) return 1;
        else if(hand1Pair == hand2Pair) {
            for(int i = 4; i >= 0; i --) {
                if(hand1[i] > hand2[i]) return 1;
                if(hand1[i] < hand2[i]) return -1;
            }
            return 0;
        }
        return -1;
    } else {
        for(int i = 4; i <= 0; i ++) {
            if(hand1[i] > hand2[i]) return 1;
            else if(hand1[i] < hand2[i]) return -1;
        }
        return 0;
    }
    return 0;
}

std::vector<Card> createDeck() {
    std::vector<Card> deck;
    for(int i = 0; i < 52; i ++) {
        int suit = i/13;
        int value = i % 13;
        
        Card newCard;
        newCard.value = value;
        newCard. suit = suit;
        
        deck.push_back(newCard);
    }
    return deck;
}

void printCards(std::vector<Card> deck) {
    for(int i = 0; i < deck.size(); i ++) {
        std::cout<<deck[i].value << ", " << deck[i].suit << std::endl;
    }
}

int main(int argc, const char * argv[]) {
    
    // Generate hands
    
    // Validate hands
    
    // Compare hands
    
    // Repeat?
    
    std::vector<Card> deck = createDeck();
    
    std::cout << "<============== PRINTING DECK ==============>" << std::endl;
    printCards(deck);
    
    std::srand(unsigned(std::time(0)));
    std::random_shuffle(deck.begin(), deck.end(), myrandom);
    
    std::cout << "<============== PRINTING SHUFFLED DECK ==============>" << std::endl;
    printCards(deck);
    
    // Deal the hands
    std::vector<Card> hand1(deck.begin(), deck.begin()+5);
    std::vector<Card> hand2(deck.begin()+5, deck.begin()+10);
    
    std::sort(hand1.begin(), hand1.end());
    std::sort(hand2.begin(), hand2.end());
    
    std::cout << "<============== PRINTING HAND 1 ==============>" << std::endl;
    printCards(hand1);
    std::cout << "<============== PRINTING HAND 2 ==============>" << std::endl;
    printCards(hand2);
    
    int result = compareHands(hand1, hand2);
    
    std::cout << result << std::endl;
    
    return 1;
}
