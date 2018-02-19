#include "lib/TestHarness.h"
#include "../src/card_compare.h"

TEST (Cards, Deal) {
    std::vector<Card> deck = createDeck();
    CHECK (deck.size() == 52);
}

TEST (Hand, IsFlush) {
    std::vector<Card> hand;
    for(int i = 0; i < 5; i ++) {
        hand.push_back(Card(i, 0));
    }
    CHECK (flush(hand));
}

TEST (Hand, IsStraight) {
    std::vector<int> handMap(13, 0);
    for(int i = 0; i < 5; i ++) {
        handMap[i] = 1;
    }
    CHECK (straight(handMap));
}

TEST (Hand, IsFiveOfAKind) {
    std::vector<int> handMap(13, 0);
    handMap[4] = 5;
    CHECK (fiveOfAKind(handMap));
}

TEST (Hand, IsStraightFlush) {
    std::vector<Card> hand;
    std::vector<int> handMap(13, 0);
    for(int i = 0; i < 5; i ++) {
        hand.push_back(Card(i, 0));
    }
    for(int i = 0; i < 5; i ++) {
        handMap[hand[i].value] ++;
    }
    CHECK (straightFlush(hand, handMap));
}

TEST (Hand, IsFourOfAKind) {
    std::vector<int> handMap(13, 0);
    handMap[0] = 4;
    handMap[1] = 1;
    CHECK (fourOfAKind(handMap));
}

TEST (Hand, IsFullHouse) {
    std::vector<int> handMap(13, 0);
    handMap[0] = 3;
    handMap[1] = 2;
    CHECK (fullHouse(handMap));
}

TEST (Hand, IsThreeOfAKind) {
    std::vector<int> handMap(13, 0);
    handMap[0] = 3;
    handMap[1] = 1;
    handMap[2] = 1;
    CHECK (threeOfAKind(handMap));
}

TEST (Hand, IsTwoPair) {
    std::vector<int> handMap(13, 0);
    handMap[0] = 2;
    handMap[1] = 2;
    handMap[2] = 1;
    CHECK (twoPair(handMap));
}

TEST (Hand, IsOnePair) {
    std::vector<int> handMap(13, 0);
    handMap[0] = 2;
    handMap[1] = 1;
    handMap[2] = 1;
    handMap[3] = 1;
    CHECK (onePair(handMap));
}

TEST (Hand, FindsHighCard) {
    std::vector<int> handMap(13, 0);
    handMap[12] = 1;
    handMap[11] = 4;
    CHECK (highCard(handMap) == 12);
}

TEST (Hand, GetsCorrectValue) {
    std::vector<Card> hand;
    std::vector<int> handMap(13, 0);
    
    for(int i = 0; i < 5; i ++) {
        hand.push_back(Card(0, 0));
        handMap[0] ++;
    }
    
    CHECK (getHandValue(hand, handMap) == 0);
}

TEST (Hand, ComparesCorrectly) {
    std::vector<Card> hand1;
    std::vector<Card> hand2;
    
    for(int i = 0; i < 5; i ++) {
        hand1.push_back(Card(0, 0));
        hand2.push_back(Card(i, 0));
    }
    
    CHECK (compareHands(hand1, hand2) == 1);
}
