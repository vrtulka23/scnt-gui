cmake_minimum_required(VERSION 3.22)
cmake_policy(SET CMP0074 NEW)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

project(GUI VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wno-deprecated -O3")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(MODULE_NAME scnt-gui)
#set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install")
set(CMAKE_INSTALL_BINDIR bin)
set(CMAKE_INSTALL_LIBDIR lib)
set(CMAKE_INSTALL_INCLUDEDIR include)

# compile libraries and executables
###################################

message("Code version: ${CODE_VERSION}")

find_package(SCNT-PUQ REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

message("Compiling executable: scnt-gui")
file(GLOB example_files "src/*.cpp" "src/**/*.cpp")
add_executable(scnt-gui ${example_files} )
target_compile_definitions(scnt-gui PRIVATE CODE_VERSION="${CODE_VERSION}")
target_link_libraries(scnt-gui PRIVATE puq-cpp Qt6::Widgets)

# add Google tests
###################

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
enable_testing()

file(GLOB test_files "gtest/*.cpp")
add_executable(TestSolver ${test_files})
target_link_libraries(TestSolver PRIVATE GTest::gtest_main puq-cpp)

include(GoogleTest)
gtest_discover_tests(TestSolver)

# install files
###############

install(TARGETS scnt-gui EXPORT GUITargets
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

