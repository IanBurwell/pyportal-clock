#pragma once

class Task {
public:
    Task(){};
    virtual void Init() = 0;
    virtual void Update() = 0;
};