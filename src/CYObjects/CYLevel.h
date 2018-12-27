#pragma once

#include <array>
#include <vector>

#include "CYObjectId.h"
#include "CYObject.h"

struct CYLevel {
    std::string levelName;
    std::string creatorName;
    uint8_t numFloors;
    uint8_t music;
    uint8_t theme;
    uint8_t weather;

    std::array<std::vector<CYObject>, (size_t)ObjectID::NUM_OBJECTS> objects;
    std::array<std::vector<PropertyType>, (size_t)ObjectID::NUM_OBJECTS> propLayouts;
};