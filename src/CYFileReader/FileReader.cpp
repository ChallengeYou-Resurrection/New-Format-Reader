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

    void readProperties(BinaryFileReader& reader, const std::vector<PropertyType>& layout, PropertyList& list) {
        for (uint8_t i = 0; i < layout.size(); i++) {
            auto prop = layout[(size_t)i];
            switch(prop) {
                case PropertyType::Texture:{
                    uint32_t texture;
                    reader >> texture;
                    list.push_back(texture);
                    } break;

                case PropertyType::Message:{
                    std::string message;
                    reader >> message;
                    list.push_back(message);
                    } break;

                default:{
                    uint8_t value;
                    reader >> value;
                    list.push_back(value);
                    } break; 
            }
        }
    }

    void readLevelWalls(BinaryFileReader& reader, CYLevel& level, uint32_t numWalls) {
        for (size_t i = 0; i < numWalls; i++) {
            CYWall wall;
            reader >> wall.beginPoint >> wall.endPoint >> wall.floor;
            readProperties(reader, level.propLayouts[(int)ObjectID::Wall], wall.properties);
            level.walls.push_back(wall);
        }
    }

    void readLevelFloor(BinaryFileReader& reader, CYLevel& level, uint32_t floorsCount) {
        for (size_t i = 0; i < floorsCount; i++) {
            CYFloor floor;
            reader >> floor.vertexA >> floor.vertexB >> floor.vertexC >> floor.vertexD >> floor.floor;
            readProperties(reader, level.propLayouts[(int)ObjectID::Floor], floor.properties);
            level.floors.push_back(floor);
        }
    }

    void readLevelObjectGroup(BinaryFileReader& reader, CYLevel& level, const ObjectHeaderInfo& info) {
        for (size_t i = 0; i < info.numObjects; i++) {
            CYObject object;
            reader >> object.position >> object.floor;
            readProperties(reader, level.propLayouts[(int)info.objectId], object.properties);
            level.objects[(int)info.objectId].push_back(object);
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

    while(reader) {
        auto headerInfo = readObjectGroupHeader(reader, level);
        switch(headerInfo.objectId) {
            case ObjectID::Wall:
                readLevelWalls(reader, level, headerInfo.numObjects);
                break;

            case ObjectID::Floor:
                readLevelFloor(reader, level, headerInfo.numObjects);
                break;

            default:
                readLevelObjectGroup(reader, level, headerInfo);
                break;
        }
    }

    return level;
}