#include <iostream>

#include "CYFileReader/FileReader.h"

#include <filesystem>
#include "Benchmark.h"

int main() {
    benchmark::Benchmark<1>("Reading all levels", []{
    for (auto& path : std::filesystem::directory_iterator("../../out/")) {
        auto lvl = loadLevel(path.path().string());
    }
    }).outputTimes();
}
