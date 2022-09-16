# CMakeList.txt : CMake project for cpp-playground, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# PROJECT
project(playground)

# Find Packages
find_package(spdlog CONFIG REQUIRED)
find_package(Catch2 3 REQUIRED)
find_package(Eigen3 CONFIG REQUIRED)

# TESTS
add_executable(constructor_destructor_order "source/constructor_destructor_order.cpp")
target_compile_definitions(constructor_destructor_order PUBLIC SPDLOG_ACTIVE_LEVEL=TRACE)
target_link_libraries(constructor_destructor_order PUBLIC spdlog::spdlog Catch2::Catch2WithMain)


add_executable(pbr_vs_rbv "source/pbr_vs_rbv.cpp")
target_link_libraries(pbr_vs_rbv PUBLIC Catch2::Catch2WithMain Eigen3::Eigen)
