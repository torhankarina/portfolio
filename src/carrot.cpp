#include <string>

#include "carrot.hpp"

std::string Carrot::symbol() {
    if(age == 0) {
        return "v";
    } else if (age >= 1) {
        return "V";
    }
}

void Carrot::end_day() {
    age += 1;
}

bool Carrot::is_mature() {
    return age >= 1;
}