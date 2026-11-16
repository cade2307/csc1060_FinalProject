/*
 * Name: Jaden Ramirez
 * Class Summary: Tracks the player's state throughout the mystery which includes their
 *                name, current room ID, sanity score (0-100), collected clues,
 *                and completed precision task count.
 */

#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Player {
private:
    string playerName;
    int currentRoomID;
    int sanityScore;
    vector<string> collectedClues;
    int tasksCompletedCount;

public:
    Player();
    Player(string name, int startRoomID, int startSanity);

    // Getters
    string getPlayerName() const { return playerName; }
    int getCurrentRoomID() const { return currentRoomID; }
    int getSanityScore() const { return sanityScore; }
    vector<string> getCollectedClues() const { return collectedClues; }
    int getTasksCompletedCount() const { return tasksCompletedCount; }

    // Setters
    void setPlayerName(string name) { playerName = name; }
    void setCurrentRoomID(int id) { currentRoomID = id; }
    void setSanityScore(int sanity);
    void setTasksCompletedCount(int count) { tasksCompletedCount = count; }

    // Core Methods
    void moveToRoom(int newRoomID);
    void addClue(string clue);
    void modifySanity(int amount);
    void incrementTasksCompleted() { tasksCompletedCount++; }
    bool isAlive() const;
};

#endif