/*
 * Name: Jaden Ramirez
 * Class Summary: A controller class that manages the main menu, gameplay
 *                loop, user action processing, CSV/DAT file I/O, and ending
 *                evaluations.
 */

#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <iostream>
#include <string>
#include <vector>
#include "Room.h"
#include "Player.h"
#include "TaskManager.h"

using namespace std;

class GameEngine {
private:
    vector<Room> worldMap;
    vector<TaskManager> taskList;
    Player currentPlayer;
    bool gameRunning;

public:
    GameEngine();

    // Getters
    Player getCurrentPlayer() const { return currentPlayer; }
    bool isGameRunning() const { return gameRunning; }

    // Menu & Input Validation Helpers (Checkpoint 04)
    void printMenu() const;
    int getUserMenuOption() const;
    bool validateMenuOption(int option) const;

    // Core Methods
    void runMainMenu();
    void startNewGame();
    void displayRules() const;
    void processAction(char command);
    void makeFinalAccusation();
    void loadRooms(string filename);
    void loadTasks(string filename);
    void saveGame(string filename);
    void loadGame(string filename);
};

#endif