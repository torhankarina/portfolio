#include "spinach.hpp"

std::string Spinach::symbol() {
    if (age < 2) return "~"; // tilled soil
    else if (age >= 2 && age < 5) return "p"; // seedling
    else return "P"; // adult
}

void Spinach::end_day() {
    if (watered) { age += 2; watered = false; }
    else age += 1;
}

bool Spinach::is_mature() { return age >= 5; }

void Spinach::water() { watered = true; }