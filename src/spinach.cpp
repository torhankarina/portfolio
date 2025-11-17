#include "spinach.hpp"

std::string Spinach::symbol() {
    if (age == 0) return "~";     // tilled soil
    else if (age < 2) return "p"; // seedling (avoid 's')
    else return "P";              // adult
}

void Spinach::end_day() {
    if (watered) { age += 2; watered = false; }
    else age += 1;
}

bool Spinach::is_mature() { return age >= 3; }

void Spinach::water() { watered = true; }