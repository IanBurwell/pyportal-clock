#pragma once

#include <cstdint>
#include <functional>
#include "task.h"

#define MAX_SCHEDULED_ITEMS 64

class Scheduler {
public:
    Scheduler(){};

    /// @brief Schedules a function to be called every `period_ms` milliseconds
    /// @return True if scheduled, false if name is already in use
    bool ScheduleFunc(const char* name, unsigned int period_ms, std::function<void()> func);

    /// @brief Schedules a task to be updated every `period_ms` milliseconds and calls its Init function
    /// @return True if scheduled, false if the task has already been scheduled
    bool ScheduleTask(const char* name, unsigned int period_ms, Task& task);
    
    /// @brief Calls functions/tasks that are due to be run. Should be called very often
    void Tick();

    size_t GetNumberScheduledItems(){return num_items_;};
    
private:
    struct ScheduledItem {
        Task* task = nullptr;
        const char* name = "";
        unsigned int period_ms = 0;
        unsigned long last_run_ms = 0;
        std::function<void()> update_func = nullptr;
    };

    ScheduledItem scheduled_items_[MAX_SCHEDULED_ITEMS];
    int num_items_ = 0;
};