#include "beet.hpp"

std::string Beet::symbol() {
    if (age == 0) return "~";     // tilled soil
    else if (age < 2) return "b"; // seedling
    else return "B";              // adult
}

void Beet::end_day() {
    if (watered) { age += 2; watered = false; }
    else age += 1;
}

bool Beet::is_mature() { return age >= 5; }

void Beet::water() { watered = true; }