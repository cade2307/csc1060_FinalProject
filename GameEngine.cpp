/*
 * Name: Jaden Ramirez
 * File Summary: Puts in GameEngine class member functions, including main
 *               menu navigation and user input validation. Also Runs the
 *                main menu, story gameplay loop, CSV world loading,
 *               and savegame.dat persistence for game.
 */

#include "GameEngine.h"
#include <fstream>
#include <sstream>
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
    cout << "2. Load Saved Investigation" << endl;
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
        cout << "Choose an option (1-4): ";
        if (cin >> choice && validateMenuOption(choice)) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return choice;
        }
        cout << "Please enter a valid number from 1 to 4." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void GameEngine::displayRules() const {
    cout << "\n--- INVESTIGATOR HANDBOOK ---" << endl;
    cout << "You are trapped inside Blackwood Manor after a midnight murder." << endl;
    cout << "- Move between rooms with N, S, E, or W." << endl;
    cout << "- Press F to search a room for clues." << endl;
    cout << "- Press T to solve a 3-digit task and steady your nerves." << endl;
    cout << "- Press C to check your sanity and clue notebook." << endl;
    cout << "- Press S to save your progress." << endl;
    cout << "- Press A when you are ready to accuse: Human or Specter." << endl;
    cout << "- Press Q to return to the main menu." << endl;
}

void GameEngine::runMainMenu() {
    bool inMenu = true;
    while (inMenu) {
        printMenu();
        int option = getUserMenuOption();

        if (option == 1) {
            startNewGame();
        } else if (option == 2) {
            loadGame("savegame.dat");
            if (gameRunning) {
                runGameLoop();
            }
        } else if (option == 3) {
            displayRules();
        } else if (option == 4) {
            cout << "\nYou step back into the fog. Until next time..." << endl;
            inMenu = false;
            gameRunning = false;
        }
    }
}

void GameEngine::loadRooms(string filename) {
    worldMap.clear();
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "[Notice] " << filename << " not found. Using backup manor room." << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string idText, name, desc, threat, clueFlag, clue, exits, passage;

        getline(ss, idText, ',');
        getline(ss, name, ',');
        getline(ss, desc, ',');
        getline(ss, threat, ',');
        getline(ss, clueFlag, ',');
        getline(ss, clue, ',');
        getline(ss, exits, ',');
        getline(ss, passage);

        if (idText.empty() || name.empty()) continue;

        Room room(stoi(idText), name, desc, threat, stoi(clueFlag) == 1, clue);

        // Read exits like "N:2|E:3"
        stringstream exitReader(exits);
        string oneExit;
        while (getline(exitReader, oneExit, '|')) {
            size_t split = oneExit.find(':');
            if (split != string::npos) {
                string dir = oneExit.substr(0, split);
                int nextRoom = stoi(oneExit.substr(split + 1));
                room.addConnection(dir, nextRoom);
            }
        }

        if (!passage.empty() && passage != "None") {
            room.addHiddenPassage(passage);
        }

        worldMap.push_back(room);
    }
    file.close();
}

void GameEngine::loadTasks(string filename) {
    taskList.clear();
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "[Notice] " << filename << " not found. Using backup task." << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string idText, name, codeText, timeText, penaltyText;

        getline(ss, idText, ',');
        getline(ss, name, ',');
        getline(ss, codeText, ',');
        getline(ss, timeText, ',');
        getline(ss, penaltyText);

        if (idText.empty() || name.empty()) continue;

        TaskManager task(stoi(idText), name, stoi(codeText), stoi(timeText), stoi(penaltyText));
        taskList.push_back(task);
    }
    file.close();
}

void GameEngine::initializeDefaultWorld() {
    loadRooms("rooms_init.csv");
    if (worldMap.empty()) {
        Room fallback(1, "Grand Foyer", "A quiet, shadowy entrance hall.", "Low", true,
                      "Frost covers the inside of the front door lock.");
        worldMap.push_back(fallback);
    }

    loadTasks("tasks_init.csv");
    if (taskList.empty()) {
        taskList.push_back(TaskManager(1, "Reset the Flickering Breaker Box (Enter code: 427)", 427, 15, 20));
    }

    killerIsSpecter = true;
}

void GameEngine::saveGame(string filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "[Error] Could not save your notebook to " << filename << "." << endl;
        return;
    }

    file << currentPlayer.getPlayerName() << endl;
    file << currentPlayer.getCurrentRoomID() << endl;
    file << currentPlayer.getSanityScore() << endl;
    file << currentPlayer.getTasksCompletedCount() << endl;

    vector<string> clues = currentPlayer.getCollectedClues();
    file << clues.size() << endl;
    for (size_t i = 0; i < clues.size(); i++) {
        file << clues[i] << endl;
    }

    file << taskList.size() << endl;
    for (size_t i = 0; i < taskList.size(); i++) {
        file << (taskList[i].isTaskActive() ? 1 : 0) << endl;
    }

    file.close();
    cout << "\n[Saved] Your investigation notes have been written to " << filename << "." << endl;
}

void GameEngine::loadGame(string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "\n[Notice] No save file found yet. Start a new investigation first!" << endl;
        gameRunning = false;
        return;
    }

    string name;
    if (!getline(file, name) || name.empty()) {
        cout << "\n[Notice] Your save file is empty. Start a new investigation first!" << endl;
        file.close();
        gameRunning = false;
        return;
    }

    int roomID = 1, sanity = 100, tasksDone = 0;
    if (!(file >> roomID >> sanity >> tasksDone)) {
        cout << "\n[Error] Save file could not be read." << endl;
        file.close();
        gameRunning = false;
        return;
    }
    file.ignore(numeric_limits<streamsize>::max(), '\n');

    initializeDefaultWorld();
    currentPlayer = Player(name, roomID, sanity);
    currentPlayer.setTasksCompletedCount(tasksDone);

    size_t clueCount = 0;
    if (file >> clueCount) {
        file.ignore(numeric_limits<streamsize>::max(), '\n');
        for (size_t i = 0; i < clueCount; i++) {
            string clueLine;
            if (getline(file, clueLine) && !clueLine.empty()) {
                currentPlayer.addClue(clueLine);
            }
        }
    }

    size_t savedTasks = 0;
    if (file >> savedTasks) {
        for (size_t i = 0; i < savedTasks && i < taskList.size(); i++) {
            int active = 1;
            if (file >> active) {
                taskList[i].setTaskActive(active == 1);
            }
        }
    }

    file.close();
    gameRunning = true;
    cout << "\n[Loaded] You open your journal and step back into the manor, "
         << currentPlayer.getPlayerName() << "..." << endl;
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
    cout << "\nEnter your detective's name: ";
    getline(cin, name);
    if (name.empty()) {
        name = "Investigator";
    }

    initializeDefaultWorld();
    currentPlayer = Player(name, 1, 100);
    gameRunning = true;

    cout << "\nThunder rolls outside Blackwood Manor as the heavy oak doors slam shut behind you, "
         << currentPlayer.getPlayerName() << "." << endl;
    cout << "Someone—or something—is still inside. Find the truth before your nerve breaks." << endl;

    runGameLoop();
}

void GameEngine::runGameLoop() {
    while (gameRunning && currentPlayer.isAlive()) {
        Room* room = findRoomByID(currentPlayer.getCurrentRoomID());
        if (room != nullptr) {
            room->displayRoomInfo();
        }

        cout << "\n[Sanity: " << currentPlayer.getSanityScore()
             << "/100 | Clues: " << currentPlayer.getCollectedClues().size()
             << " | Tasks Solved: " << currentPlayer.getTasksCompletedCount() << "]" << endl;
        cout << "Commands: [N/S/E/W] Move | [F] Search | [T] Task | [C] Notebook | [S] Save | [A] Accuse | [Q] Quit" << endl;
        cout << "What do you do? ";

        char cmd;
        cin >> cmd;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        processAction(toupper(cmd));

        if (!currentPlayer.isAlive()) {
            cout << "\n[GAME OVER] The whispers overwhelm your mind. You collapse in the dark..." << endl;
            gameRunning = false;
        }
    }
}

void GameEngine::processAction(char command) {
    Room* room = findRoomByID(currentPlayer.getCurrentRoomID());
    if (room == nullptr) return;

    if (command == 'N' || command == 'S' || command == 'E' || command == 'W') {
        string dir(1, command);
        map<string, int> exits = room->getConnectedRooms();

        if (exits.count(dir)) {
            currentPlayer.moveToRoom(exits[dir]);
            cout << "\nYour footsteps echo as you slip through the " << dir << " doorway..." << endl;
        } else {
            cout << "\nA locked wall blocks your path in that direction." << endl;
        }
    } else if (command == 'F') {
        if (room->getHasClue()) {
            cout << "\n[Clue Discovered] " << room->getClueText() << endl;
            cout << "You jot the detail down in your notebook." << endl;
            currentPlayer.addClue(room->getClueText());
        } else {
            cout << "\nYou search the shadows, but find nothing unusual here." << endl;
        }
    } else if (command == 'T') {
        for (size_t i = 0; i < taskList.size(); i++) {
            if (taskList[i].isTaskActive()) {
                cout << "\n[Task] " << taskList[i].getTaskName() << endl;
                cout << "Enter the 3-digit code: ";

                int code;
                if (!(cin >> code)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Your hands shake and the wires spark! (-"
                         << taskList[i].getSanityPenalty() << " Sanity)" << endl;
                    taskList[i].triggerPenalty(currentPlayer);
                    return;
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if (taskList[i].evaluateTaskInput(code)) {
                    cout << "Click! The mechanism hums smoothly. (+10 Sanity)" << endl;
                    currentPlayer.incrementTasksCompleted();
                    currentPlayer.modifySanity(10);
                } else {
                    cout << "Wrong code! A chilling whisper echoes behind you. (-"
                         << taskList[i].getSanityPenalty() << " Sanity)" << endl;
                    taskList[i].triggerPenalty(currentPlayer);
                }
                return;
            }
        }
        cout << "\nEvery device in the manor is already stabilized!" << endl;
    } else if (command == 'C') {
        cout << "\n=== DETECTIVE NOTEBOOK ===" << endl;
        cout << "Investigator: " << currentPlayer.getPlayerName() << endl;
        cout << "Sanity: " << currentPlayer.getSanityScore() << "/100" << endl;
        cout << "Tasks Completed: " << currentPlayer.getTasksCompletedCount() << endl;

        vector<string> clues = currentPlayer.getCollectedClues();
        cout << "Clues Collected (" << clues.size() << "):" << endl;
        if (clues.empty()) {
            cout << "  - None yet. Try searching rooms with [F]." << endl;
        } else {
            for (size_t i = 0; i < clues.size(); i++) {
                cout << "  * " << clues[i] << endl;
            }
        }
    } else if (command == 'S') {
        saveGame("savegame.dat");
    } else if (command == 'A') {
        makeFinalAccusation();
    } else if (command == 'Q') {
        cout << "\nStepping back to the main menu..." << endl;
        gameRunning = false;
    } else {
        cout << "\nUnknown command. Try N, S, E, W, F, T, C, S, A, or Q." << endl;
    }
}

void GameEngine::makeFinalAccusation() {
    cout << "\n=== THE FINAL ACCUSATION ===" << endl;
    cout << "You gather your notes (" << currentPlayer.getCollectedClues().size() << "/4 clues found)." << endl;
    cout << "Who committed the murder at Blackwood Manor? (1 = Human, 2 = Specter): ";

    int choice;
    if (!(cin >> choice) || (choice != 1 && choice != 2)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "You hesitate and lower your lantern. Keep investigating first." << endl;
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    bool accusedSpecter = (choice == 2);
    if (accusedSpecter == killerIsSpecter && currentPlayer.getCollectedClues().size() >= 2) {
        cout << "\n[CASE SOLVED] With solid proof of paranormal frost and magnetism, you banish the Specter!" << endl;
    } else if (accusedSpecter == killerIsSpecter) {
        cout << "\n[UNSOLVED] You guessed Specter correctly, but without at least 2 clues, nobody believes your story." << endl;
    } else {
        cout << "\n[CASE FAILED] It wasn't a human at all. Cold mist pours from the hidden passageways..." << endl;
    }
    gameRunning = false;
}