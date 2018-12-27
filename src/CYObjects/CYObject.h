#pragma once 

#include <vector>
#include <variant>
#include <cstdint>
#include <string>

class BinaryFileReader;

using PropertyList = std::vector<std::variant<uint8_t, uint32_t, std::string>>;

struct Position {
    int16_t x = 0;
    int16_t z = 0;

    void deserialize(BinaryFileReader& buffer);
};


struct CYObject {
    Position position; 
    uint8_t floor;

    PropertyList properties;
};

struct CYWall {
    Position beginPoint;
    Position endPoint;
    uint8_t floor;

    PropertyList properties;
};

struct CYFloor {
    Position vertexA;
    Position vertexB;
    Position vertexC;
    Position vertexD;
    uint8_t floor;
    PropertyList properties;
};