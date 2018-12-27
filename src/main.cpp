#include <iostream>

#include "CYFileReader/FileReader.h"

int main() {
    std::cout << "Reading GlassTower\n";
    {auto level = loadLevel("../../games/GlassTower2[258].cyb");} 
/*
    std::cout << "\nReading The Mouse Returns\n";
    {auto level = loadLevel("../../games/The Mouse Returns[158209].cyb");} 

    std::cout << "\nReading Item Builder\n";
    {auto level = loadLevel("../../games/Items Builder[159673].cyb");}  
*/
}
