# Jaden Ramirez
## Whispers in the Passageways
## A interactive C++ horror and murder mystery game where players navigate rooms, solve precision tasks, and deduce Human vs. Specter killers.

## Checkpoint-01: Initial project structure / setup

1. What challenges did you encounter?

# Setting up the multi-file C++ compilation workflow in VS Code on macOS required adjusting `.vscode/tasks.json` to compile for the  `*.cpp` instead of only a single active file and switching the output path from a Windows `.exe` executable to a macOS binary (`./main`).

2. What design decisions or changes did you make?

# For this I chanaged how I organized the project root cleanly into a separate header (.h) and used (.cpp) files for the four core classes Room, Player, TaskManager, and GameEngine, alongside dedicated CSV and DAT data files. Those were, rooms_init.csv, tasks_init.csv, and savegame.dat. 

## checkpoint-02: class declaration

1. What challenges did you encounter?

# I faced trying to translate my Phase II UML diagram into a C++ header file while making sure to include guards (`#ifndef`/`#define`/`#endif`), using consistent lowercase `.h` file naming, and avoiding circular header dependencies between `TaskManager`, `Player`, and `GameEngine` which required careful organization.


2. What design decisions or changes did you make?

# I kept all member variables `private` to enforce encapsulation, used inline definitions for simple single-instruction getters / setters, and added a `clueText` attribute to `Room` and a `taskList` vector to `GameEngine` so external CSV data would map cleanly to objects.

## checkpoint-03: class definition

1. What challenges did you encounter?

# I encountered trying to ensure every function definition in the `.cpp` source files matched the exact parameter types and `const` qualifiers which were declared in the `.h` headers, while properly monitoring the player's sanity score between 0 and 100, required when testing.

2. What design decisions or changes did you make?

# I prevented duplicate clue entries inside `Player::addClue()`, through the 0–100 bounds inside `Player::setSanityScore()`, and verified every class constructor and method using a standalone unit test in `main.cpp` before renaming it to `maintest.txt`.

## checkpoint-04: program structure integration and input validation

1. What challenges did you encounter?

# I had trouble with preventing infinite input loops when non-numeric characters (such as letters or symbols) were entered into `std::cin` during menu selection which required clearing the stream error flags like (`cin.clear()`). This then led to flushing the input buffer (`cin.ignore()`).

2. What design decisions or changes did you make?

# I modularized the menu workflow into dedicated `printMenu()`, `validateMenuOption()`, and `getUserMenuOption()` methods inside `GameEngine` so the menu loop remained clean. It also rejects out-of-range or non-integer inputs.

## checkpoint-05: incorporate objects into program flow

1. What challenges did you encounter?

# This was a lot more difficult then I thought it was going to be in coordinating state updates across `Player`, `Room`, and `TaskManager` inside `GameEngine::processAction()`. Specifically in matching directional exits from `Room::getConnectedRooms()` and applying sanity penalties through in the `TaskManager::triggerPenalty(Player&)` because it required careful pointer and reference handling.

2. What design decisions or changes did you make?

# For the design I created `initializeDefaultWorld()` and `runGameLoop()` inside `GameEngine` to populate the initial `vector<Room>` and `vector<TaskManager>` collections in the memory. This allowed full movement, clue gathering, precision tasks, and accusation endings to be tested before thinking ahead to connecting external CSV/DAT File I/O which i will need ot do in the next checkpoint.

## checkpoint-06: file io / data persistence

1. What challenges did you encounter?

# This go arround I had trouble reading comma-separated room data and pipe-separated exit pairs from `rooms_init.csv` and `tasks_init.csv` when using a `std::stringstream`, while making sure missing or empty `savegame.dat` files still returned players safely to the main menu instead of crashing (it liked to do that), I stopped that with stream state checks.

2. What design decisions or changes did you make?

# I implemented `loadRooms()` and `loadTasks()` using `ifstream` and `stringstream` with built-in fallback data where if the CSV files are missing i then added an in-game `[S]` Save command paired with `saveGame()` and `loadGame()` so the investigator's name, current room, sanity score, collected clues, and task states stay the same across separate runs.

---

## checkpoint-07: final testing and program completion, verification, and submission

1. What were the most significant challenges you encountered, and how did you resolve them?

# The biggest challenges were preventing infinite `std::cin` loops when entering non-numeric characters during menu or task input. Figuring out how to coordinate state updates across separate `Player`, `Room`, and `TaskManager` objects inside `GameEngine`. was resolved by adding `cin.clear()` and `cin.ignore()` input validation helpers and combining object interactions inside `GameEngine::processAction()`. Using `std::stringstream` with fallback checks for missing or empty data files. This helped me handle file loading cleanly.

2. What were the most significant design decisions or changes did you make throughout development?

# I separated the program into four different classes such as, GameEngine, Room, Player, and TaskManager. Each class held a single responsibility, such as decoupled menu validation from File I/O during early checkpoints, and designed `savegame.dat` to store the player's name, location, sanity score, collected clues, and active task states in a clean sequential format.

3. What did you learn about developing a C++ program incrementally?

# Through building the project in seven checkpoints starting from essentially nothing it was interesting to create the things like UML class declarations, which you had to design to verifying each class with a standalone unit test (`maintest.txt`), and or layering in menu validation which ran object gameplay. Or the best thing with CSV/DAT File I/O where one stage at a time—made the debugging much faster because every layer was tested before adding something new.

4. Are there any known issues, limitations, or incomplete features?

# The precision tasks currently rely on entering 3-digit calibration codes rather than a real-time countdown timer thread, and the manor map contains four core rooms with a single Specter scenario rather than randomized killer identities across multiple playthroughs. I also found it to be annoying that when playing the results of whatever you typed to be the actions shows up after and above where the UI is located which is due to the runGameLoop() immidietly reprinting it but I will fix that next week. 

5. How does your completed program compare with your original program summary and design?

# The completed program matches my original Phase I UML design and proposal: players navigate interconnected rooms, uncover hidden passageways, gather clues, complete precision tasks to protect their sanity which is what I set out to do. It also saves and loads progress via external files, and make a final Human vs. Specter deduction. I still want to integrate the phase 2 ASCII art and possibly improve on it I just thought for the first process I would get the basics down. 