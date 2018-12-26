#include "FileReader.h"

#include <iostream>

#include "../Utilities.h"
#include "BinaryFileReader.h"


namespace {
    template <typename T>
    void print(const char* msg, const T& val) {
        std::cout << msg << ": <" << val << ">\n";
    }
} 



CYLevel loadLevel(const std::string& file) {
    CYLevel level;
    auto data = readFileIntoVec(file);
    BinaryFileReader reader (std::move(data));

    uint8_t fileVersion;
    reader >> fileVersion >> level.levelName >> level.creatorName;

    print("Version", (int)fileVersion);
    print("Game Name", level.levelName);
    print("Game Author", level.creatorName);

    return level;
}