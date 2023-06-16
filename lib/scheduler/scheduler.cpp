#include <Arduino.h>
#include "scheduler.h"

bool Scheduler::ScheduleFunc(const char* name, uint32_t period_ms, std::function<void()> func)
{
    // Check if the same name has already been scheduled
    for(int i = 0; i < this->num_items_; i++){
        ScheduledItem& item = this->scheduled_items_[i];
        if(item.name == name)
            return false;
    }

    // Schedule Function
    ScheduledItem& item = this->scheduled_items_[this->num_items_];

    item = {};
    item.name = name;
    item.period_ms = period_ms;
    item.update_func = func;

    this->num_items_++;
    return true;
}


bool Scheduler::ScheduleTask(const char* name, uint32_t period_ms, Task& task)
{
    // Check if the same task/name has already been scheduled
    for(int i = 0; i < this->num_items_; i++){
        ScheduledItem& item = this->scheduled_items_[i];
        if(item.name == name || item.task == &task)
            return false;
    }

    // Schedule task
    ScheduledItem& item = this->scheduled_items_[this->num_items_];

    item = {};
    item.name = name;
    item.period_ms = period_ms;
    item.task = &task;
    task.Init();

    this->num_items_++;

    return true;
}


void Scheduler::Tick()
{
    // Loop over scheduled items and call their update functions
    for(int i = 0; i < this->num_items_; i++){
        ScheduledItem& item = this->scheduled_items_[i];
        
        if(!item.update_func && !item.task)
            continue;

        // TODO handle wrap around of millis (this happens every 40ish days)
        if(millis()-item.last_run_ms < item.period_ms)
            continue;
        
        if(item.update_func)
            item.update_func();
        else if(item.task)
            item.task->Update();

        item.last_run_ms = millis();
    }

}