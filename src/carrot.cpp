#include <string>
#include "carrot.hpp"

std::string Carrot::symbol() {
    if(age == 0) return "~"; //tilled soil
    else if (age < 1) return "c"; //seedling
    else return "C"; //adult
}

void Carrot::end_day() {
    if (watered) { age += 2; watered = false; }
    else age += 1;
}

bool Carrot::is_mature() { return age >= 1; }

void Carrot::water() { watered = true; }