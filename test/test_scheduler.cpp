#include <Arduino.h>
#include <Scheduler.h>
#include <Task.h>
#include <unity.h>


Scheduler sched;
uint func_calls = 0, task_update_calls = 0, task_init_calls = 0;
class TestTask : public Task {
    void Init() override {task_init_calls++;};
    void Update() override {task_update_calls++;};
} test_task;
void dummy_func(void){func_calls++;}


/// Tests scheduling a function
void test_schedule_func(){
    TEST_ASSERT_TRUE(sched.ScheduleFunc("TestFunction", 100, dummy_func));
    TEST_ASSERT_FALSE(sched.ScheduleFunc("TestFunction", 200, dummy_func));
    TEST_ASSERT_TRUE(sched.ScheduleFunc("ReTestFunction", 250, dummy_func));
    
    TEST_ASSERT_TRUE(sched.GetNumberScheduledItems() == 2);
}


/// Tests scheduling a task
void test_schedule_task(){
    TEST_ASSERT_TRUE(sched.ScheduleTask("TestTask", 100, test_task));
    TEST_ASSERT_FALSE(sched.ScheduleTask("TestTask", 200, test_task));
    TEST_ASSERT_FALSE(sched.ScheduleTask("ReTestTask", 250, test_task));
    
    TEST_ASSERT_TRUE(sched.GetNumberScheduledItems() == 3);
    TEST_ASSERT_TRUE(task_init_calls == 1);
}

/// Tests running the scheduler
void test_scheduler_tick(){
    // Tick the scheduler for 950ms 
    unsigned long start_time = millis();
    while(millis()-start_time < 950)
        sched.Tick();

    // Test number of calls to scheduled function and task
    TEST_ASSERT_TRUE(func_calls == 14);
    TEST_ASSERT_TRUE(task_init_calls == 1);
    TEST_ASSERT_TRUE(task_update_calls == 10);
}

void setup(){
    delay(2000);
    UNITY_BEGIN();

    RUN_TEST(test_schedule_func);
    RUN_TEST(test_schedule_task);

    RUN_TEST(test_scheduler_tick);

    UNITY_END();
}


void setUp(void){}
void tearDown(void){}
void loop(){}