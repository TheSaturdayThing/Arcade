cmake_minimum_required(VERSION 3.1)

project(LedTest)
aux_source_directory(. SRC_LIST)
include_directories(.)

# C++11, add "-g" if you want to debug
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# add /usr/local/lib to the linker paths (-rpath for GCC)
# so self-compiled SDL2 libraries are found
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
set(CMAKE_INSTALL_RPATH "/usr/local/lib")

# Add myproject executable to project
add_executable(LedTest LedTest.cpp)

# Find against WiringPi
include(FindPkgConfig)
find_library(WIRINGPI_LIBRARIES NAMES wiringPi)
target_link_libraries(LedTest ${WIRINGPI_LIBRARIES})
