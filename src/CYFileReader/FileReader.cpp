#include "FileReader.h"

#include <iostream>

#include "../Utilities.h"
#include "BinaryFileReader.h"


namespace {
    struct ObjectHeaderInfo {
        ObjectID objectId;
        uint32_t numObjects;
        uint8_t numProperties;
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
            (ObjectID)objectId, numObjects, numProperties
        };
    }

    void readLevelWalls(BinaryFileReader& reader, CYLevel& level, uint32_t numWalls, uint8_t numProperties) {
        for (size_t i = 0; i < numWalls; i++) {
            CYWall wall;
            reader >> wall.beginPoint >> wall.endPoint >> wall.floor;

            for (uint8_t i = 0; i < numProperties; i++) {
                auto prop = level.propLayouts[(int)ObjectID::Wall][(size_t)i];
                switch(prop) {
                    case PropertyType::Texture:{
                        uint32_t texture;
                        reader >> texture;
                        wall.properties.push_back(texture);
                        } break;

                    case PropertyType::Message:{
                        std::string message;
                        reader >> message;
                        wall.properties.push_back(message);
                        } break;

                    default:{
                        uint8_t value;
                        reader >> value;
                        print("After insert: ", (int)std::get<uint8_t>(wall.properties.back()));
                        } break; 
                }
            }

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
            readLevelWalls(reader, level, headerInfo.numObjects, headerInfo.numProperties);
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
    print("Num Properties", (int)headerInfo.numProperties);
    print("Num Objects",    headerInfo.numObjects);
    std::cout << "Properties: \n";
    for (auto p : level.propLayouts[(int)headerInfo.objectId]) {
        print("\tProperty", (int)p);
    }

    for (const auto& wall : level.walls) {
        std::cout << "Wall: \n";
        print("\tStart X", wall.beginPoint.x);
        print("\tStart Z", wall.beginPoint.z);
        print("\tEnd   X", wall.endPoint.x);
        print("\tStart Z", wall.endPoint.z);
        print("\tFloor", (int)wall.floor);
        for (int i = 0; i < (int)wall.properties.size(); i++) {
            auto prop = level.propLayouts[(int)ObjectID::Wall][(size_t)i];
            switch(prop) {
                case PropertyType::Texture:{
                    auto texture = std::get<uint32_t>(wall.properties[i]);
                    print("\tTexture", texture);
                    } break;

                case PropertyType::Message:{
                    auto message = std::get<std::string>(wall.properties[i]);
                    print("\tMessage", message);
                    } break;

                default:{
                    auto prop = std::get<uint8_t>(wall.properties[i]);
                    print("\tMisc Prop", (int)prop);
                    } break; 
            }
        }
    }

    return level;
}