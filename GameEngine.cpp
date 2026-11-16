/*
 * Name: Jaden Ramirez
 * File Summary: Puts in GameEngine class member functions, including main
 *               menu navigation and user input validation.
 */

#include "GameEngine.h"
#include <limits>
#include <cctype>

GameEngine::GameEngine() {
    gameRunning = false;
    killerIsSpecter = true;
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
    cout << "- Move between rooms using N, S, E, or W." << endl;
    cout << "- Press F to search the current room for clues." << endl;
    cout << "- Press T to attempt a 3-digit precision task and stabilize sanity." << endl;
    cout << "- Press C to view your investigator status and collected clues." << endl;
    cout << "- Press A when ready to accuse the killer (Human or Specter)." << endl;
    cout << "- Press Q to return to the main menu." << endl;
}

void GameEngine::runMainMenu() {
    bool inMenu = true;
    while (inMenu) {
        printMenu();
        int option = getUserMenuOption();
        switch (option) {
            case 1:
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

void GameEngine::initializeDefaultWorld() {
    worldMap.clear();
    taskList.clear();

    Room foyer(1, "Grand Foyer", "A cold, marble-floored entrance hall with flickering sconces.", "Low", true,
               "Sub-zero frost patterns spiral outward from the lock without any footprints.");
    foyer.addConnection("N", 2);
    foyer.addConnection("E", 3);

    Room library(2, "Archive Library", "Towering oak bookshelves packed with occult and estate ledgers.", "Medium", true,
                 "A heavy iron candelabra passed straight through the torn wallpaper.");
    library.addConnection("S", 1);
    library.addConnection("E", 4);
    library.addHiddenPassage("Behind the Rotating Atlas");

    Room conservatory(3, "Glass Conservatory", "Overgrown ferns under shattered skylights dripping with rain.", "Medium", true,
                      "The victim's pocket watch stopped at 3:14 AM and is magnetized.");
    conservatory.addConnection("W", 1);
    conservatory.addConnection("N", 4);

    Room cellar(4, "Sub-Basement Cellar", "Damp stone walls echoing with rhythmic whispers.", "High", true,
                "Ectoplasmic residue coats the sealed vault door from the inside.");
    cellar.addConnection("W", 2);
    cellar.addConnection("S", 3);
    cellar.addHiddenPassage("Narrow Maintenance Tunnel");

    worldMap.push_back(foyer);
    worldMap.push_back(library);
    worldMap.push_back(conservatory);
    worldMap.push_back(cellar);

    taskList.push_back(TaskManager(1, "Breaker Box Alignment (Enter code: 427)", 427, 15, 20));
    taskList.push_back(TaskManager(2, "EMF Frequency Lock (Enter code: 739)", 739, 15, 25));
    taskList.push_back(TaskManager(3, "Vault Tumbler Override (Enter code: 814)", 814, 15, 30));

    killerIsSpecter = true;
}

Room* GameEngine::findRoomByID(int id) {
    for (size_t i = 0; i < worldMap.size(); i++) {
        if (worldMap[i].getRoomID() == id) {
            return &worldMap[i];
        }
    }
    return nullptr;
}

void GameEngine::startNewGame() {
    string name;
    cout << "\nEnter your investigator name: ";
    getline(cin, name);
    if (name.empty()) {
        name = "Investigator";
    }

    initializeDefaultWorld();
    currentPlayer = Player(name, 1, 100);
    gameRunning = true;

    cout << "\nWelcome, " << currentPlayer.getPlayerName() << ". The manor doors lock behind you..." << endl;
    runGameLoop();
}

void GameEngine::runGameLoop() {
    while (gameRunning && currentPlayer.isAlive()) {
        Room* activeRoom = findRoomByID(currentPlayer.getCurrentRoomID());
        if (activeRoom != nullptr) {
            activeRoom->displayRoomInfo();
        }

        cout << "\n[Sanity: " << currentPlayer.getSanityScore()
             << "/100 | Clues: " << currentPlayer.getCollectedClues().size()
             << " | Tasks Solved: " << currentPlayer.getTasksCompletedCount() << "]" << endl;
        cout << "Actions: [N/S/E/W] Move | [F] Search Clue | [T] Precision Task | [C] Status | [A] Accuse | [Q] Quit" << endl;
        cout << "Enter command: ";

        char cmd;
        cin >> cmd;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        processAction(toupper(cmd));

        if (!currentPlayer.isAlive()) {
            cout << "\n[GAME OVER] Your sanity has shattered in the dark..." << endl;
            gameRunning = false;
        }
    }
}

void GameEngine::processAction(char command) {
    Room* activeRoom = findRoomByID(currentPlayer.getCurrentRoomID());
    if (activeRoom == nullptr) {
        return;
    }

    if (command == 'N' || command == 'S' || command == 'E' || command == 'W') {
        string dir(1, command);
        map<string, int> exits = activeRoom->getConnectedRooms();
        if (exits.count(dir)) {
            currentPlayer.moveToRoom(exits[dir]);
            cout << "You move " << dir << " into the next chamber..." << endl;
        } else {
            cout << "[Blocked] There is no exit in that direction." << endl;
        }
    } else if (command == 'F') {
        if (activeRoom->getHasClue()) {
            cout << "[Clue Found] " << activeRoom->getClueText() << endl;
            currentPlayer.addClue(activeRoom->getClueText());
        } else {
            cout << "You search carefully, but find no new evidence here." << endl;
        }
    } else if (command == 'T') {
        bool foundActive = false;
        for (size_t i = 0; i < taskList.size(); i++) {
            if (taskList[i].isTaskActive()) {
                foundActive = true;
                cout << "\n[PRECISION TASK] " << taskList[i].getTaskName() << endl;
                cout << "Enter 3-digit calibration code: ";
                int code;
                if (!(cin >> code)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "[Failed] Invalid input! Sanity penalty triggered." << endl;
                    taskList[i].triggerPenalty(currentPlayer);
                    return;
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if (taskList[i].evaluateTaskInput(code)) {
                    cout << "[Success] System stabilized! (+10 Sanity)" << endl;
                    currentPlayer.incrementTasksCompleted();
                    currentPlayer.modifySanity(10);
                } else {
                    cout << "[Failed] Incorrect sequence! (-" << taskList[i].getSanityPenalty() << " Sanity)" << endl;
                    taskList[i].triggerPenalty(currentPlayer);
                }
                break;
            }
        }
        if (!foundActive) {
            cout << "All manor precision tasks are already stabilized!" << endl;
        }
    } else if (command == 'C') {
        cout << "\n=== INVESTIGATOR DOSSIER ===" << endl;
        cout << "Name: " << currentPlayer.getPlayerName() << endl;
        cout << "Sanity: " << currentPlayer.getSanityScore() << "/100" << endl;
        cout << "Tasks Completed: " << currentPlayer.getTasksCompletedCount() << endl;
        vector<string> clues = currentPlayer.getCollectedClues();
        cout << "Collected Clues (" << clues.size() << "):" << endl;
        if (clues.empty()) {
            cout << "  - None yet." << endl;
        } else {
            for (size_t i = 0; i < clues.size(); i++) {
                cout << "  * " << clues[i] << endl;
            }
        }
    } else if (command == 'A') {
        makeFinalAccusation();
    } else if (command == 'Q') {
        cout << "Returning to main menu..." << endl;
        gameRunning = false;
    } else {
        cout << "[Invalid Command] Use N, S, E, W, F, T, C, A, or Q." << endl;
    }
}

void GameEngine::makeFinalAccusation() {
    cout << "\n=== FINAL ACCUSATION ===" << endl;
    cout << "Clues gathered: " << currentPlayer.getCollectedClues().size() << "/4" << endl;
    cout << "Who is responsible for the murders? (1 = Human, 2 = Specter): ";
    int choice;
    if (!(cin >> choice) || (choice != 1 && choice != 2)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "[Cancelled] Invalid selection. Gather your thoughts and try again." << endl;
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    bool accusedSpecter = (choice == 2);
    if (accusedSpecter == killerIsSpecter && currentPlayer.getCollectedClues().size() >= 2) {
        cout << "\n[VICTORY] You proved the killer is a Specter and banished it from the manor!" << endl;
    } else if (accusedSpecter == killerIsSpecter) {
        cout << "\n[PARTIAL ENDING] Your instinct was right, but without at least 2 clues, no one believes you." << endl;
    } else {
        cout << "\n[DEFEAT] Wrong accusation! The true Specter emerges from the passageways..." << endl;
    }
    gameRunning = false;
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