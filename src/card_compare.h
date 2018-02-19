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
    
    Card(int v, int s) : value(v), suit(s) {}
};

// Return a random number generator to shuffle the cards
int randomNum (int i);

// Return true if hand has a flush, false otherwise
bool flush(std::vector<Card>& hand);

// Return true if hand has a straight, false otherwise
bool straight(std::vector<int>& handMap);

// Return true if hand has a five of a kind, false otherwise
bool fiveOfAKind(std::vector<int>& handMap);

// Return true if hand has a straight flush, false otherwise
bool straightFlush(std::vector<Card>& hand, std::vector<int>& handMap);

// Return true if hand has a four of a kind, false otherwise
bool fourOfAKind(std::vector<int>& handMap);

// Return true if hand has a full house, false otherwise
bool fullHouse(std::vector<int>& handMap);

// Return true if hand has a three of a kind, false otherwise
bool threeOfAKind(std::vector<int>& handMap);

// Return true if hand has a two pair, false otherwise
bool twoPair(std::vector<int>& handMap);

// Return true if hand has a one pair, false otherwise
bool onePair(std::vector<int>& handMap);

// Returns the value of the highest card in the hand
int highCard(std::vector<int>& handMap);

// Returns the ranking of the hand
int getHandValue(std::vector<Card>& hand, std::vector<int>& handMap);

// Returns 1 if hand1 is of higher rank than hand2, 0 if they are equal, or -1 if hand2 is of higher rank than hand1
int compareHands(std::vector<Card>& hand1, std::vector<Card>& hand2);

// Creates a 52 card deck, unshuffled
std::vector<Card> createDeck();

// Prints any hand or deck to the command line
void printCards(std::vector<Card> deck);
