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