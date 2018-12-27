#include "CYObject.h"

#include "../CYFileReader/BinaryFileReader.h"

void Position::deserialize(BinaryFileReader& buffer) {
    buffer >> x >> z;
}

/*
void CYWall::deserialize(BinaryFileReader& buffer) {
    buffer  >> beginPoint >> endPoint >> floor;
}
*/