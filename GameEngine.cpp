/*
 * Name: Jaden Ramirez
 * File Summary: Puts in GameEngine class member functions. 
 */

#include "GameEngine.h"

GameEngine::GameEngine() {
    gameRunning = false;
}

void GameEngine::runMainMenu() {
    cout << "Main menu placeholder." << endl;
}

void GameEngine::startNewGame() {
    gameRunning = true;
}

void GameEngine::displayRules() const {
    cout << "Rules placeholder." << endl;
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