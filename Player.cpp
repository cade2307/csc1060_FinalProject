/*
 * Name: Jaden Ramirez
 * File Summary: Puts in the Players class constructors and member functions
 *               for tracking movement, sanity levels, clues, and task counts.
 */

#include "Player.h"

Player::Player() {
    playerName = "Investigator";
    currentRoomID = 1;
    sanityScore = 100;
    tasksCompletedCount = 0;
}

Player::Player(string name, int startRoomID, int startSanity) {
    playerName = name;
    currentRoomID = startRoomID;
    setSanityScore(startSanity);
    tasksCompletedCount = 0;
}

void Player::setSanityScore(int sanity) {
    if (sanity > 100) {
        sanityScore = 100;
    } else if (sanity < 0) {
        sanityScore = 0;
    } else {
        sanityScore = sanity;
    }
}

void Player::moveToRoom(int newRoomID) {
    currentRoomID = newRoomID;
}

void Player::addClue(string clue) {
    for (const string& existing : collectedClues) {
        if (existing == clue) {
            return;
        }
    }
    collectedClues.push_back(clue);
}

void Player::modifySanity(int amount) {
    setSanityScore(sanityScore + amount);
}

bool Player::isAlive() const {
    return sanityScore > 0;
}