#include "brussels_sprouts.hpp"

std::string BrusselsSprouts::symbol() {
    if (age < 5) return "~"; // tilled soil
    else if (age >= 5 && age < 15) return "r"; // seedling
    else return "R"; // adult
}

void BrusselsSprouts::end_day() {
    if (watered) { age += 2; watered = false; }
    else age += 1;
}

bool BrusselsSprouts::is_mature() { return age >= 15; }

void BrusselsSprouts::water() { watered = true; }