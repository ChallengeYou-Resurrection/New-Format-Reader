#pragma once 

#include <variant>

class BinaryFileReader;

struct Position {
    int16_t x = 0;
    int16_t z = 0;

    void deserialize(BinaryFileReader& buffer);
};


struct CYObject {

};

struct CYWall {
    Position beginPoint;
    Position endPoint;
    std::vector<std::string> properties;
    uint8_t floor;

    void deserialize(BinaryFileReader& buffer);
}