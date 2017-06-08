
cmake_minimum_required(VERSION 3.8)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/CMake)
project(phidgetspp)

cmake_policy(SET CMP0003 NEW)
set(CMAKE_CXX_STANDARD 14)
add_library(phidgetspp src/phidgetspp.hpp src/phidgetspp.cpp)
target_include_directories(phidgetspp PUBLIC 3rdparty/libphidget-2.1.8.20151217)
target_link_libraries(phidgetspp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/libphidget-2.1.8.20151217/.libs/libphidget21.a)
add_executable(test_phidgetspp tests/test_phidgetspp.cpp)
find_package(Threads REQUIRED)
find_package(USB REQUIRED)
target_link_libraries(test_phidgetspp PRIVATE phidgetspp Threads::Threads  ${LIBUSB_LIBRARIES} dl)
