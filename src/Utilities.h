#pragma once

#include <vector>
#include <string>
#include <iostream>

#include "CYObjects/CYObjectId.h"

class CYLevel;



std::vector<unsigned char> readFileIntoVec(const std::string& filename);

void printPropertyList(const CYLevel& level, ObjectID id);

template <typename T>
void print(const char* msg, const T& val) {
    std::cout << msg << ": <" << val << ">\n";
}