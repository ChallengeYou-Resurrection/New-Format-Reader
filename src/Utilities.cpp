#include "Utilities.h"

#include <iterator>
#include <fstream>
#include <iostream>

#include "CYObjects/CYLevel.h"

//Credit: https://stackoverflow.com/a/21802936
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

void printPropertyList(const CYLevel& level, ObjectID id) {
    for (const auto& f : level.objects[(int)id]) {
        std::cout << "Props:\n";
        for (int i = 0; i < (int)f.properties.size(); i++) {
            auto prop = level.propLayouts[(int)id][(size_t)i];
            switch(prop) {
                case PropertyType::Texture:
                    print("\tTexture", std::get<uint32_t>(f.properties[i]));
                    break;
    
                case PropertyType::Message:
                    print("\tMessage", std::get<std::string>(f.properties[i]));
                    break;
    
                default:
                    print("\tMisc Prop", (int)std::get<uint8_t>(f.properties[i]));
                    break; 
            }
        }
    }
}