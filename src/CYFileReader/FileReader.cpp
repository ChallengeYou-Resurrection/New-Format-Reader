#include "FileReader.h"

#include "../Utilities.h"
#include "BinaryFileReader.h"

CYLevel loadLevel(const std::string& file) {
    CYLevel level;
    auto data = readFileIntoVec(file);
    BinaryFileReader reader (std::move(data));

    return level;
}