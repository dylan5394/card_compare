#include <vector>
#include <iostream>

#include "card_compare.h"


int randomNum (int i) { return std::rand()%i; }

bool flush(std::vector<Card>& hand) {
    int i = 0;
    while(i < 4 && hand[i].suit == hand[i+1].suit) i ++;
    return i == 4;
}

bool straight(std::vector<int>& handMap) {
    // Try to find 5 sequential cards
    int start = 0;
    while(handMap[start] == 0) start ++;
    int i = start;
    while(start < handMap.size() && handMap[start] == 1) start ++;
    return (start-i) == 5;
}

bool fiveOfAKind(std::vector<int>& handMap) {
    return std::find(handMap.begin(), handMap.end(), 5) != handMap.end();
}

bool straightFlush(std::vector<Card>& hand, std::vector<int>& handMap) {
    return flush(hand) && straight(handMap);
}

bool fourOfAKind(std::vector<int>& handMap) {
    return std::find(handMap.begin(), handMap.end(), 4) != handMap.end();
}

bool fullHouse(std::vector<int>& handMap) {
    return std::find(handMap.begin(), handMap.end(), 2) != handMap.end() && std::find(handMap.begin(), handMap.end(), 3) != handMap.end();
}

bool threeOfAKind(std::vector<int>& handMap) {
    return std::find(handMap.begin(), handMap.end(), 3) != handMap.end();;
}

bool twoPair(std::vector<int>& handMap) {
    return std::count(handMap.begin(), handMap.end(), 2) == 2;
}

bool onePair(std::vector<int>& handMap) {
    return std::find(handMap.begin(), handMap.end(), 2) != handMap.end();;
}

int highCard(std::vector<int>& handMap) {
    int i = handMap.size() - 1;
    while(handMap[i] == 0 && i >= 0) i --;
    return i;
}

int getHandValue(std::vector<Card>& hand, std::vector<int>& handMap) {
    int handValue;
    if(fiveOfAKind(handMap)) handValue = FiveOfAKind;
    else if(straightFlush(hand, handMap)) handValue = StraightFlush;
    else if(fourOfAKind(handMap)) handValue = FourOfAKind;
    else if(fullHouse(handMap)) handValue = FullHouse;
    else if(flush(hand)) handValue = Flush;
    else if(straight(handMap)) handValue = Straight;
    else if(threeOfAKind(handMap)) handValue = ThreeOfAKind;
    else if(twoPair(handMap)) handValue = TwoPair;
    else if(onePair(handMap)) handValue = OnePair;
    else handValue = HighCard + (12 - highCard(handMap));
    return handValue;
}

int compareHands(std::vector<Card>& hand1, std::vector<Card>& hand2) {
    /*
    Compare each hand's main rank (4 of a kind, straight, etc...) then find their kickers and other significant values if the main ranks are the same
     
     Kicker(s) are the cards in each hand which contribute no significance to the hand's main rank
        i.e. the remaining card in a 4 of a kind or one of the three other cards in a one pair
     
     */
    
    // Map each card value so we can easily determine the number of occurences of each card value in each hand
    std::vector<int> hand1Map(13, 0);
    std::vector<int> hand2Map(13, 0);
    
    for(int i = 0; i < hand1.size(); i ++) {
        hand1Map[hand1[i].value] ++;
    }
    
    for(int i = 0; i < hand2.size(); i ++) {
        hand2Map[hand2[i].value] ++;
    }

    // Get hand values when aces are high
    int hand1Val = getHandValue(hand1, hand1Map);
    int hand2Val = getHandValue(hand2, hand2Map);
    
    // Get the aces in each hand and reinsert at the beginning (such that aces are low)
    int hand1Aces = hand1Map[12];
    int hand2Aces = hand2Map[12];
    
    hand1Map.pop_back();
    hand2Map.pop_back();
    
    hand1Map.insert(hand1Map.begin(), hand1Aces);
    hand2Map.insert(hand2Map.begin(), hand2Aces);
    
    // Get hand values when aces are low
    int hand1ValAcesLow = getHandValue(hand1, hand1Map);
    int hand2ValAcesLow = getHandValue(hand2, hand2Map);
    
    // Take the aces configuration that provides the best value. If equal, aces high is always better
    if(hand1Val <= hand1ValAcesLow) {
        hand1Map.erase(hand1Map.begin());
        hand1Map.push_back(hand1Aces);
    } else hand1Val = hand1ValAcesLow;
    
    if(hand2Val <= hand2ValAcesLow) {
        hand2Map.erase(hand2Map.begin());
        hand2Map.push_back(hand2Aces);
    } else hand2Val = hand2ValAcesLow;
    
    std::cout << "Hand 1 value: " << hand1Val << std::endl;
    std::cout << "Hand 2 value: " << hand2Val << std::endl;
    
    // If hand 1 and hand 2 have different rankings, return 1 if hand 1 ranks better otherwise -1
    if(hand1Val != hand2Val) return hand1Val < hand2Val ? 1 : -1;
    
    // Hand 1 and hand 2 are of equal rank, so we have to find potential tie breaker conditions
    if(hand1Val == FourOfAKind) {
        // Find which card value each 4 of a kind is comprised of, and compare
        int hand1HighCard = std::find(hand1Map.begin(), hand1Map.end(), 4) - hand1Map.begin();
        int hand2HighCard = std::find(hand2Map.begin(), hand2Map.end(), 4) - hand2Map.begin();
        if(hand1HighCard != hand2HighCard) return hand1HighCard > hand2HighCard ? 1 : -1;
    } else if(hand1Val == FullHouse) {
        // Find which card value each 3 of a kind is comprised of, and compare
        int hand1Triple = std::find(hand1Map.begin(), hand1Map.end(), 3) - hand1Map.begin();
        int hand2Triple = std::find(hand2Map.begin(), hand2Map.end(), 3) - hand2Map.begin();
        
        if(hand1Triple != hand2Triple) return hand1Triple > hand2Triple ? 1 : -1;
        else {
            // Find which card value each pair is comprised of, and compare
            int hand1Pair = std::find(hand1Map.begin(), hand1Map.end(), 2) - hand1Map.begin();
            int hand2Pair = std::find(hand2Map.begin(), hand2Map.end(), 2) - hand2Map.begin();
            
            if(hand1Pair != hand2Pair) return hand1Pair > hand2Pair ? 1 : -1;
            return 0;
        }
    } else if(hand1Val == ThreeOfAKind) {
        // Find which card value each 3 of a kind is comprised of, and compare
        int hand1Triple = std::find(hand1Map.begin(), hand1Map.end(), 3) - hand1Map.begin();
        int hand2Triple = std::find(hand2Map.begin(), hand2Map.end(), 3) - hand2Map.begin();
        if(hand1Triple != hand2Triple) return hand1Triple > hand2Triple ? 1 : -1;
    } else if(hand1Val == TwoPair) {
        // Find which card value each pair is comprised of, and compare
        for(int i = 12; i >= 0; i --) {
            if((hand1Map[i] == 2 || hand2Map[i] == 2) && hand1Map[i] != hand2Map[i]) {
                return hand1Map[i] > hand2Map[i] ? 1 : -1;
            }
        }
    } else if(hand1Val == OnePair) {
        // Find which card value pair is comprised of, and compare
        int hand1PairVal = std::find(hand1Map.begin(), hand1Map.end(), 2) - hand1Map.begin();
        int hand2PairVal = std::find(hand2Map.begin(), hand2Map.end(), 2) - hand2Map.begin();
        if(hand1PairVal != hand2PairVal) return hand1PairVal > hand2PairVal ? 1 : -1;
    }
    
    // Outside of certain cases in the above conditions, all hands of equal rank can be reduced to determining which hand has higher kicker values. Find hand (if exists) with higher kicker value, else return 0
    for(int i = 12; i >= 0; i --) {
        if(hand1Map[i] != hand2Map[i]) return hand1Map[i] > hand2Map[i] ? 1 : -1;
    }
    return 0;
   
}

std::vector<Card> createDeck() {
    std::vector<Card> deck;
    for(int i = 0; i < 52; i ++) {
        int suit = i/13;
        int value = i % 13;
        
        Card newCard(value, suit);
        deck.push_back(newCard);
    }
    return deck;
}

void printCards(std::vector<Card> deck) {
    for(int i = 0; i < deck.size(); i ++) {
        std::cout<<deck[i].value << ", " << deck[i].suit << std::endl;
    }
}

