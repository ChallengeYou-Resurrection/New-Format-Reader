#pragma once

#include <vector>
#include <iostream>
#include <string>
#include <cstring>
#include <cstdint>
#include <byteswap.h>

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;

using i16 = int16_t;

class BinaryFileReader {
    public:
        BinaryFileReader(std::vector<unsigned char>&& data);

        friend BinaryFileReader& operator >>(BinaryFileReader& reader, u8& n) {
            reader.readNumber(n);
            return reader;
        }

        friend BinaryFileReader& operator >>(BinaryFileReader& reader, u16& n) {
            reader.readNumber(n);
            n = bswap_16(n);
            return reader;
        }

        friend BinaryFileReader& operator >>(BinaryFileReader& reader, u32& n) {
            reader.readNumber(n);
            return reader;
        }

        friend BinaryFileReader& operator >>(BinaryFileReader& reader, std::string& str) {
            uint32_t length = 0;
            reader >> length;
            str.assign(reader.m_readPtr, reader.m_readPtr + length);
            incrementReader(length);
            return reader;
        }

    private:
        void incrementReader(size_t amount);

        template<typename T>
        void readNumber(T& n) {
            std::memcpy(reinterpret_cast<char*>(&n), m_readPtr, sizeof(T));
            incrementReader(sizeof(T));
        }

        std::vector<unsigned char> m_buffer;
        unsigned char* m_readPtr;
};

BinaryFileReader& operator >>(BinaryFileReader& reader, u8& n);