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
    bool killerIsSpecter;

public:
    GameEngine();
    // Description: Initializes default game state flags (gameRunning = false, killerIsSpecter = true).

    // Getters
    Player getCurrentPlayer() const { return currentPlayer; }
    // Description: Returns the current player's state and statistics.

    bool isGameRunning() const { return gameRunning; }
    // Description: Checks whether the main gameplay loop is currently running.

    // Menu & Input Validation Helpers (Checkpoint 04)
    void printMenu() const;
    // Description: Displays the formatted main title banner and numbered menu options (1-4).

    int getUserMenuOption() const;
    // Description: Prompts the user for a menu option and clears invalid input until a valid number is entered.

    bool validateMenuOption(int option) const;
    // Description: Validates whether a numeric menu choice is within the accepted range (1-4).

    // Gameplay Helpers (Checkpoint 05)
    void initializeDefaultWorld();
    // Description: Loads rooms and tasks from CSV files with built-in fallback objects if files are missing.

    void runGameLoop();
    // Description: Runs the turn-by-turn investigation loop until the player quits, accuses, or loses all sanity.

    Room* findRoomByID(int id);
    // Description: Searches worldMap for a room matching the given room ID and returns a pointer to it.

    // Core Methods
    void runMainMenu();
    // Description: Controls the top-level menu loop for starting, loading, viewing rules, or exiting.

    void startNewGame();
    // Description: Prompts for the investigator's name, initializes the manor world, and starts gameplay.

    void displayRules() const;
    // Description: Prints gameplay controls, clue mechanics, and accusation rules to the console.

    void processAction(char command);
    // Description: Executes player movement, clue searches, precision tasks, saving, or accusations.

    void makeFinalAccusation();
    // Description: Evaluates the player's Human vs. Specter accusation and collected clues to trigger the ending.

    void loadRooms(string filename);
    // Description: Parses room records, directional exits, and hidden passages from a CSV file into worldMap.

    void loadTasks(string filename);
    // Description: Parses precision task records and sanity penalties from a CSV file into taskList.

    void saveGame(string filename);
    // Description: Writes current player state, collected clues, and task completion flags to disk.

    void loadGame(string filename);
    // Description: Restores saved player state, clues, and task statuses from disk if the file is valid.
};

#endif