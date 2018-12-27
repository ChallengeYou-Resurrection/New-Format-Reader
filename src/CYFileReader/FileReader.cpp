#include "FileReader.h"

#include <iostream>

#include "../Utilities.h"
#include "BinaryFileReader.h"


namespace {
    struct ObjectHeaderInfo {
        ObjectID objectId;
        uint32_t   numObjects;
    };
    template <typename T>
    void print(const char* msg, const T& val) {
        std::cout << msg << ": <" << val << ">\n";
    }

    ObjectHeaderInfo readObjectGroupHeader(BinaryFileReader& reader, CYLevel& level) {
        uint8_t     objectId;
        uint8_t     numProperties;
        uint32_t    numObjects;
        reader >> objectId >> numProperties >> numObjects;


        level.propLayouts[objectId].reserve(numProperties);
        switch ((ObjectID)objectId) {
            case ObjectID::Wall:
                level.walls.reserve((size_t)numObjects);
                break;

            case ObjectID::Floor:
                break;

            default:
                level.objects[objectId].reserve((size_t)numObjects);
                break;
        }
       

        for (int i = 0; i < numProperties; i++) {
            uint8_t propertyId;
            reader >> propertyId;
            level.propLayouts[objectId].push_back((PropertyType)propertyId);
        }

        return {
            (ObjectID)objectId, numObjects
        };
    }

    void readLevelWalls(BinaryFileReader& reader, CYLevel& level, uint32_t numWalls) {
        for (size_t i = 0; i < numWalls; i++) {
            CYWall wall;


            level.walls.push_back(wall);
        }
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

    
    auto headerInfo = readObjectGroupHeader(reader, level);
    switch(headerInfo.objectId) {
        case ObjectID::Wall:
            break;

        case ObjectID::Floor:
            break;

        default:
            break;
    }

    print("Version", (int)fileVersion);
    print("Game Name", level.levelName);
    print("Game Author", level.creatorName);
    print("Floors", (int)level.numFloors);
    print("Music", (int)level.music);
    print("Theme", (int)level.theme);
    print("Weather", (int)level.weather);

    print("Group ID", (int)headerInfo.objectId);
    print("Num Properties", level.propLayouts[(int)headerInfo.objectId].size());
    print("Num Objects",    level.objects[(int)headerInfo.objectId].capacity());
    std::cout << "Properties: \n";
    for (auto p : level.propLayouts[(int)headerInfo.objectId]) {
        print("\tProperty", (int)p);
    }

    return level;
}