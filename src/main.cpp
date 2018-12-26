#include <iostream>
#include <fstream>

#include "CYObjects/CYLevel.h"

int main() {
    std::string fileName = "GlassTower2[258].cyb";
    std::ifstream inFile("../../games/" + fileName, std::ifstream::binary);
    if (!inFile.is_open()) {
        std::cerr << "Unable to open " << fileName << '\n';
        return -1;
    }
}
