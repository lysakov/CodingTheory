cmake_minimum_required(VERSION 3.5)

#Target name
project(zipMeHuffman)

#C++ standart
set(CMAKE_CXX_STANDART 17)
set(CMAKE_CXX_STANDART_REQUIRED True)

#Compiler options
set(CMAKE_CXX_FLAGS 
"-std=c++17 -Wall -Werror -pedantic-errors -Wextra -ftrapv -O2 -g")

#Setting up include directory
set(INCLUDE_DIR
inc)

#Setting up source directory
set(SOURCE_DIR
src)

set(SOURCE_FILES
${SOURCE_DIR}/CodeGenerator.cpp
${SOURCE_DIR}/main.cpp
${SOURCE_DIR}/Coder.cpp
${SOURCE_DIR}/Decoder.cpp
${SOURCE_DIR}/DecodingTable.cpp
${SOURCE_DIR}/Archiever.cpp
${SOURCE_DIR}/Controller.cpp)


include_directories(${INCLUDE_DIR})
add_executable(zipMeHuffman ${SOURCE_FILES})