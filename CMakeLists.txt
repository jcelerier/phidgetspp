project(phidgetspp)

set(CMAKE_CXX_STANDARD 14)
add_library(phidgetspp src/phidgetspp.hpp src/phidgetspp.cpp)
add_executable(test_phidgetspp tests/test_phidgetspp.cpp)

target_link_libraries(test_phidgetspp PRIVATE phidgetspp)

