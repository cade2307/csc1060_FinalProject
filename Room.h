/*
 * Name: Jaden Ramirez
 * Class Summary: Represents a physical location in the game world,
 *                which manages room details, threat levels, clues, adjacent room
 *                connections, and hidden passageways.
 */

#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

class Room {
private:
    int roomID;
    string roomName;
    string description;
    string threatLevel;
    vector<string> hiddenPassages;
    map<string, int> connectedRooms;
    bool hasClue;
    string clueText;

public:
    Room();
    Room(int id, string name, string desc, string threat, bool clueFlag, string clue);

    // Getters
    int getRoomID() const { return roomID; }
    string getRoomName() const { return roomName; }
    string getDescription() const { return description; }
    string getThreatLevel() const { return threatLevel; }
    bool getHasClue() const { return hasClue; }
    string getClueText() const { return clueText; }
    map<string, int> getConnectedRooms() const { return connectedRooms; }
    vector<string> getHiddenPassages() const { return hiddenPassages; }

    // Setters
    void setRoomID(int id) { roomID = id; }
    void setRoomName(string name) { roomName = name; }
    void setDescription(string desc) { description = desc; }
    void setThreatLevel(string threat) { threatLevel = threat; }
    void setHasClue(bool clueFlag) { hasClue = clueFlag; }
    void setClueText(string clue) { clueText = clue; }

    // Core Methods
    void displayRoomInfo() const;
    bool hasSecretPassage() const;
    void addHiddenPassage(string passageName);
    void addConnection(string direction, int targetRoomID);
};

#endif