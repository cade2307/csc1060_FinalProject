/*
 * Name: Jaden Ramirez
 * File Summary: Uses the TaskManager class constructors and member
 *               functions for precision task evaluation and uses sanity penalties.
 */

#include "TaskManager.h"
#include <cstdlib>

TaskManager::TaskManager() {
    taskID = 0;
    taskName = "Circuit Calibration";
    targetSequence = 427;
    timeLimitSeconds = 15;
    sanityPenalty = 15;
    taskActive = true;
}

TaskManager::TaskManager(int id, string name, int target, int timeLimit, int penalty) {
    taskID = id;
    taskName = name;
    targetSequence = target;
    timeLimitSeconds = timeLimit;
    sanityPenalty = penalty;
    taskActive = true;
}

bool TaskManager::evaluateTaskInput(int userCode) {
    if (userCode == targetSequence) {
        taskActive = false;
        return true;
    }
    return false;
}

void TaskManager::triggerPenalty(Player &p) {
    p.modifySanity(-sanityPenalty);
}

void TaskManager::generateNewTask() {
    targetSequence = 100 + (rand() % 900);
    taskActive = true;
}