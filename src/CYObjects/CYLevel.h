#pragma once

#include <array>
#include <vector>

#include "CYObjectId.h"
#include "CYObject.h"

struct CYLevel {
    std::string levelName;
    std::string creatorName;

    std::array<std::vector<CYObject>, (int)ObjectID::NUM_OBJECTS> objects;
};