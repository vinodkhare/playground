# CMakeList.txt : CMake project for cpp-playground, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# PROJECT
project(playground)

# Find Packages
find_package(Catch2 3 REQUIRED)
find_package(Eigen3 CONFIG REQUIRED)

# TESTS
add_executable(pbr_vs_rbv "source/pbr_vs_rbv.cpp")
target_link_libraries(pbr_vs_rbv PUBLIC Catch2::Catch2WithMain Eigen3::Eigen)