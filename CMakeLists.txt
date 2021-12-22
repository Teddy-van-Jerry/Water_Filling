CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

PROJECT(Water_Filling VERSION 0.0.1)

# SET(CMAKE_OSX_ARCHITECTURES arm64;x86_64)

FIND_PACKAGE(Boost 1.70 REQUIRED
             COMPONENTS iostreams program_options)

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/include
                    ${CMAKE_SOURCE_DIR}/gnuplot-iostream
                    ${Boost_INCLUDE_DIR})

SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED True)
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

ADD_EXECUTABLE(waterfilling
               src/main.cpp
               src/wf_global.cpp
               src/waterfilling.cpp
               src/params.cpp
               src/generator.cpp)

TARGET_LINK_LIBRARIES(waterfilling LINK_PUBLIC ${Boost_LIBRARIES})

install(TARGETS waterfilling)

enable_testing()
add_test(NAME waterfilling COMMAND waterfilling)
