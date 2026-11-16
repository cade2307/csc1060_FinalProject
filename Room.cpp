/*
 * Name: Jaden Ramirez
 * File Summary: Puts the Rooms class constructors and member functions
 *               for managing room details, secret passages, and connections.
 */

#include "Room.h"

Room::Room() {
    roomID = 0;
    roomName = "Unknown Room";
    description = "A dark, quiet room.";
    threatLevel = "Low";
    hasClue = false;
    clueText = "";
}

Room::Room(int id, string name, string desc, string threat, bool clueFlag, string clue) {
    roomID = id;
    roomName = name;
    description = desc;
    threatLevel = threat;
    hasClue = clueFlag;
    clueText = clue;
}

void Room::displayRoomInfo() const {
    cout << "\n--- " << roomName << " (ID: " << roomID << ") ---" << endl;
    cout << description << endl;
    cout << "Threat Level: " << threatLevel << endl;
    if (!connectedRooms.empty()) {
        cout << "Exits: ";
        for (const auto& exitPair : connectedRooms) {
            cout << exitPair.first << " (Room " << exitPair.second << ")  ";
        }
        cout << endl;
    }
    if (hasSecretPassage()) {
        cout << "[!] You sense a draft behind the walls..." << endl;
    }
}

bool Room::hasSecretPassage() const {
    return !hiddenPassages.empty();
}

void Room::addHiddenPassage(string passageName) {
    hiddenPassages.push_back(passageName);
}

void Room::addConnection(string direction, int targetRoomID) {
    connectedRooms[direction] = targetRoomID;
}