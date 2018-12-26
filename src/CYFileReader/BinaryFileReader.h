#pragma once

#include <vector>

class BinaryFileReader {
    public:
        BinaryFileReader(std::vector<unsigned char>&& data);

    private:
        std::vector<unsigned char> m_buffer;
};