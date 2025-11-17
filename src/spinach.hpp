#pragma once
#include "plot.hpp"
#include <string>

class Spinach : public Plot {
private:
    int age = 0;
    bool watered = false;
public:
    std::string symbol() override;
    void end_day() override;
    bool is_mature() override;
    void water();
};