/*
 * Name: Jaden Ramirez
 * File Summary: Puts in GameEngine class member functions, including main
 *               menu navigation and user input validation.
 */

#include "GameEngine.h"
#include <limits>

GameEngine::GameEngine() {
    gameRunning = false;
}

void GameEngine::printMenu() const {
    cout << "\n==========================================" << endl;
    cout << "       WHISPERS IN THE PASSAGEWAYS        " << endl;
    cout << "==========================================" << endl;
    cout << "1. Start New Investigation" << endl;
    cout << "2. Load Saved Investigation (Checkpoint 06)" << endl;
    cout << "3. How to Play / Rules" << endl;
    cout << "4. Exit Game" << endl;
    cout << "------------------------------------------" << endl;
}

bool GameEngine::validateMenuOption(int option) const {
    return (option >= 1 && option <= 4);
}

int GameEngine::getUserMenuOption() const {
    int choice = 0;
    while (true) {
        cout << "Select an option (1-4): ";
        if (cin >> choice && validateMenuOption(choice)) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return choice;
        }
        cout << "[Invalid Input] Please enter a number between 1 and 4." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void GameEngine::displayRules() const {
    cout << "\n--- HOW TO PLAY ---" << endl;
    cout << "- Explore rooms (N/S/E/W) and inspect surroundings for clues." << endl;
    cout << "- Complete timed precision tasks (3-digit codes) to protect your sanity." << endl;
    cout << "- If your sanity reaches 0, you lose." << endl;
    cout << "- Gather enough clues to accuse the killer: Human or Specter." << endl;
}

void GameEngine::runMainMenu() {
    bool inMenu = true;
    while (inMenu) {
        printMenu();
        int option = getUserMenuOption();
        switch (option) {
            case 1:
                cout << "\n[System] Starting New Investigation (Object gameplay connects in Checkpoint 05)..." << endl;
                startNewGame();
                break;
            case 2:
                cout << "\n[System] Save/Load File I/O will be connected in Checkpoint 06." << endl;
                break;
            case 3:
                displayRules();
                break;
            case 4:
                cout << "\nExiting Whispers in the Passageways. Stay safe..." << endl;
                inMenu = false;
                gameRunning = false;
                break;
        }
    }
}

void GameEngine::startNewGame() {
    gameRunning = true;
}

void GameEngine::processAction(char command) {
    cout << "Processing command: " << command << endl;
}

void GameEngine::makeFinalAccusation() {
    cout << "Final accusation placeholder." << endl;
}

void GameEngine::loadRooms(string filename) {
    cout << "Loading rooms from " << filename << endl;
}

void GameEngine::loadTasks(string filename) {
    cout << "Loading tasks from " << filename << endl;
}

void GameEngine::saveGame(string filename) {
    cout << "Saving game to " << filename << endl;
}

void GameEngine::loadGame(string filename) {
    cout << "Loading game from " << filename << endl;
}