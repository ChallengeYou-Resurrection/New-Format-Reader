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
            return reader;
        }

        friend BinaryFileReader& operator >>(BinaryFileReader& reader, u32& n) {
            reader.readNumber(n);
            return reader;
        }

        friend BinaryFileReader& operator >>(BinaryFileReader& reader, std::string& str) {
            uint32_t length = 0;
            reader >> length;
            str.assign(
                reader.m_buffer.data() + reader.readIndex, 
                reader.m_buffer.data() + reader.readIndex + length);
            reader.incrementReader(length);
            return reader;
        }

        friend BinaryFileReader& operator >>(BinaryFileReader& reader, i16& n) {
            reader.readNumber(n);
            return reader;
        }

        template <typename T>
        friend BinaryFileReader& operator >>(BinaryFileReader& reader, T& val) {
            val.deserialize(reader);
            return reader;
        }

        explicit operator bool() {
            return readIndex < m_buffer.size();
        }


    private:
        void incrementReader(size_t amount);

        template<typename T>
        void readNumber(T& n) {
            std::memcpy(reinterpret_cast<char*>(&n), m_buffer.data() + readIndex, sizeof(T));
            incrementReader(sizeof(T));
        }

        std::vector<unsigned char> m_buffer;
        size_t readIndex = 0;
};

BinaryFileReader& operator >>(BinaryFileReader& reader, u8& n);