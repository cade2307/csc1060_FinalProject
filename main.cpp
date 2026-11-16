/*
 * Name: Jaden Ramirez
 * Program Title: Whispers in the Passageways
 * Program Summary: An interactive C++ horror and murder mystery game where
 *                  where players navigate interconnected rooms, uncover hidden
 *                  passageways, and solve timed precision tasks to preserve
 *                  sanity, and deduce whether the killer is Human or Specter.
 */

#include <iostream>
#include "GameEngine.h"

using namespace std;

int main() {
    GameEngine engine;
    engine.runMainMenu();
    return 0;
}