#include "BinaryFileReader.h"

BinaryFileReader::BinaryFileReader(std::vector<unsigned char>&& data) 
:   m_buffer    (data) 
{}