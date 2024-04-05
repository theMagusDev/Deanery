// Copyright (C) 2024 Yuriy Magus

#include <iostream>
#include "../include/Utilities.h"

void printMarksVector(const std::vector<int>& marks) {
    for (int mark : marks) {
        std::cout << mark << " ";
    }
}

bool checkStringContainsOnlyDigits(const std::string& str) {
    for (char charIterator : str) {
        if (!(charIterator >= '0' && charIterator <= '9')) {
            return false;
        }
    }

    return true;
}
