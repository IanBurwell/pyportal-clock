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
    bool ScheduleFunc(const char* name, uint32_t period_ms, std::function<void()> func);

    /// @brief Schedules a task to be updated every `period_ms` milliseconds and calls its Init function
    /// @return True if scheduled, false if the task has already been scheduled
    bool ScheduleTask(const char* name, uint32_t period_ms, Task& task);
    
    /// @brief Calls functions/tasks that are due to be run. Should be called very often
    void Tick();

    uint8_t GetNumberScheduledItems(){return this->num_items_;};
private:
    struct ScheduledItem {
        const char* name = "";
        uint32_t period_ms = 0;
        std::function<void()> update_func = nullptr;
        uint32_t last_run_ms = 0;
        Task* task = nullptr;
    };
    
    ScheduledItem scheduled_items_[MAX_SCHEDULED_ITEMS];
    uint8_t num_items_ = 0;
};