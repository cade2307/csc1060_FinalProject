/*
 * Name: Jaden Ramirez
 * Class Summary: Manages precision puzzle tasks, code validation (100-999),
 *                task randomization, and sanity penalties when you fail a task.
 */

#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include <iostream>
#include <string>
#include "Player.h"

using namespace std;

class TaskManager {
private:
    int taskID;
    string taskName;
    int targetSequence;
    int timeLimitSeconds;
    int sanityPenalty;
    bool taskActive;

public:
    TaskManager();
    TaskManager(int id, string name, int target, int timeLimit, int penalty);

    // Getters
    int getTaskID() const { return taskID; }
    string getTaskName() const { return taskName; }
    int getTargetSequence() const { return targetSequence; }
    int getTimeLimitSeconds() const { return timeLimitSeconds; }
    int getSanityPenalty() const { return sanityPenalty; }
    bool isTaskActive() const { return taskActive; }

    // Setters
    void setTaskID(int id) { taskID = id; }
    void setTaskName(string name) { taskName = name; }
    void setTargetSequence(int target) { targetSequence = target; }
    void setTimeLimitSeconds(int seconds) { timeLimitSeconds = seconds; }
    void setSanityPenalty(int penalty) { sanityPenalty = penalty; }
    void setTaskActive(bool active) { taskActive = active; }

    // Core Methods
    bool evaluateTaskInput(int userCode);
    void triggerPenalty(Player &p);
    void generateNewTask();
};

#endif