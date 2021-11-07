cmake_minimum_required(VERSION 3.20)
project(RePairCompression)

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake/Modules)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif ()

set(CMAKE_C_FLAGS "-Wall -Wextra -std=c99 -pedantic -Wmissing-prototypes -Wstrict-prototypes -Wold-style-definition")
set(CMAKE_CXX_FLAGS "-Wall -Wextra -std=c++17 -pedantic -Werror")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fstandalone-debug -fprofile-instr-generate -fcoverage-mapping")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}  -fprofile-arcs -ftest-coverage -lgcov --coverage")
endif ()
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

include_directories(src)

set(SRC_FILES
        src/Entry.hpp
        src/HashTable.cpp
        src/HashTable.hpp
        src/PriorityQueue.cpp
        src/PriorityQueue.hpp
        src/RePairCompression.cpp
        src/RePairCompression.hpp
        src/RePairDataStructureConcrete.cpp
        src/RePairDataStructureConcrete.hpp
        src/Record.hpp
        src/RepairCoder.cpp
        src/RepairCoder.hpp
        src/TranslateTable.cpp
        src/TranslateTable.hpp
        src/ValuePair.cpp
        src/ValuePair.hpp
        src/CommonDefinitions.hpp
        src/Serialization.cpp
        src/Serialization.hpp
        src/EntryPair.cpp
        src/EntryPair.hpp)

add_library(RePairCompression ${SRC_FILES})

add_executable(CompressFile scripts/CompressFile.cpp)
target_link_libraries(CompressFile RePairCompression)

add_executable(DecompressFile scripts/DecompressFile.cpp)
target_link_libraries(DecompressFile RePairCompression)


find_package(GTest QUIET)
if (GTest_FOUND)
    enable_testing()
    include_directories(${GTEST_INCLUDE_DIRS})

    add_executable(RepairCompressionUsabilityTest test/RepairCompressionUsabilityTest.cpp)
    target_link_libraries(RepairCompressionUsabilityTest RePairCompression ${GTEST_BOTH_LIBRARIES})

    add_test(NAME RepairCompressionUsabilityTest COMMAND ./RepairCompressionUsabilityTest)

endif ()