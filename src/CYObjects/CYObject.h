#pragma once 

#include <any>

class BinaryFileReader;

using PropertyList = std::vector<std::any>;

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
    uint8_t floor;

    PropertyList m_properties;

    void deserialize(BinaryFileReader& buffer);
}