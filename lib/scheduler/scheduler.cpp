#include <Arduino.h>
#include "scheduler.h"

bool Scheduler::ScheduleFunc(const char* name, unsigned int period_ms, std::function<void()> func)
{
    // Check if the same name has already been scheduled
    for(int i = 0; i < num_items_; i++){
        ScheduledItem& item = scheduled_items_[i];
        if(item.name == name)
            return false;
    }

    // Schedule Function
    ScheduledItem& item = scheduled_items_[num_items_];

    item = {};
    item.name = name;
    item.period_ms = period_ms;
    item.update_func = func;

    num_items_++;
    return true;
}


bool Scheduler::ScheduleTask(const char* name, unsigned int period_ms, Task& task)
{
    // Check if the same task/name has already been scheduled
    for(int i = 0; i < num_items_; i++){
        ScheduledItem& item = scheduled_items_[i];
        if(item.name == name || item.task == &task)
            return false;
    }

    // Schedule task
    ScheduledItem& item = scheduled_items_[num_items_];

    item = {};
    item.name = name;
    item.period_ms = period_ms;
    item.task = &task;
    task.Init();

    num_items_++;

    return true;
}


void Scheduler::Tick()
{
    // Loop over scheduled items and call their update functions
    for(int i = 0; i < num_items_; i++){
        ScheduledItem& item = scheduled_items_[i];
        
        if(!item.update_func && !item.task)
            continue;

        // TODO handle wrap around of millis (this happens every 50ish days)
        unsigned long now = millis();
        if(item.period_ms != 0 && now-item.last_run_ms < item.period_ms)
            continue;
        
        if(item.update_func)
            item.update_func();
        else if(item.task)
            item.task->Update();

        item.last_run_ms = now;
    }

}