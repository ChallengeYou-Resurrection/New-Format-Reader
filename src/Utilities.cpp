#include "Utilities.h"

#include <iterator>
#include <fstream>
#include <iostream>

std::vector<unsigned char> readFileIntoVec(const std::string& filename) {
    std::ifstream inFile(filename, std::ios::binary);
    if (!inFile.is_open()) {
        std::cerr << "Unable to open " << filename << '\n';
        exit(1);
    }
    inFile.unsetf(std::ios::skipws);
    std::streampos fileSize;
    inFile.seekg(0, std::ios::end);
    fileSize = inFile.tellg();
    inFile.seekg(0, std::ios::beg);
    std::vector<unsigned char> vec;
    vec.reserve(fileSize);

    vec.insert(vec.begin(),
               std::istream_iterator<unsigned char>(inFile),
               std::istream_iterator<unsigned char>());

    return vec;
}