#include "FileReader.h"

#include <iostream>

#include "../Utilities.h"
#include "BinaryFileReader.h"


namespace {
    template <typename T>
    void print(const char* msg, const T& val) {
        std::cout << msg << ": <" << val << ">\n";
    }

    uint8_t readObjectGroupHeader(BinaryFileReader& reader, CYLevel& level) {
        uint8_t     objectId;
        uint8_t     numProperties;
        uint32_t    numObjects;
        reader >> objectId >> numProperties >> numObjects;


        level.propLayouts[objectId].reserve(numProperties);
        level.objects    [objectId].reserve((size_t)numObjects);

        for (int i = 0; i < numProperties; i++) {
            uint8_t propertyId;
            reader >> propertyId;
            level.propLayouts[objectId].push_back((PropertyType)propertyId);
        }

        return objectId;
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

    auto nextReadGroupId = readObjectGroupHeader(reader, level);

    print("Version", (int)fileVersion);
    print("Game Name", level.levelName);
    print("Game Author", level.creatorName);
    print("Floors", (int)level.numFloors);
    print("Music", (int)level.music);
    print("Theme", (int)level.theme);
    print("Weather", (int)level.weather);

    print("Group ID", (int)nextReadGroupId);
    print("Num Properties", level.propLayouts[nextReadGroupId].size());
    print("Num Objects",    level.objects[nextReadGroupId].capacity());
    std::cout << "Properties: \n";
    for (auto p : level.propLayouts[nextReadGroupId]) {
        print("\tProperty", (int)p);
    }

    return level;
}