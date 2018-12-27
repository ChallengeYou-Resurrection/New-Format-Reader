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

    //Read metadata;
    uint8_t fileVersion;
    reader >> fileVersion;
    reader  >> level.levelName
            >> level.creatorName
            >> level.numFloors
            >> level.music 
            >> level.theme 
            >> level.weather;

    print("Version", (int)fileVersion);
    print("Game Name", level.levelName);
    print("Game Author", level.creatorName);
    print("Floors", (int)level.numFloors);
    print("Music", (int)level.music);
    print("Theme", (int)level.theme);
    print("Weather", (int)level.weather);
    return level;
}