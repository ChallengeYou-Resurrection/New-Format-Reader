cmake_minimum_required(VERSION 3.1)

project(cy-new-format-reader)
#Set up the C++ flags
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_LIBRARIES -lstdc++fs)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(SOURCES
	src/main.cpp
	src/Utilities.cpp
	src/CYFileReader/BinaryFileReader.cpp 
	src/CYFileReader/FileReader.cpp 
	src/CYObjects/CYObject.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

find_package(Threads)
target_link_libraries(${PROJECT_NAME} Threads::Threads)
