#include "lettuce.hpp"

std::string Lettuce::symbol() {
    if (age == 0) return "~";     // tilled soil
    else if (age < 2) return "l"; // seedling
    else return "L";              // adult
}

void Lettuce::end_day() {
    if (watered) { age += 2; watered = false; }
    else age += 1;
}

bool Lettuce::is_mature() { return age >= 2; }

void Lettuce::water() { watered = true; }