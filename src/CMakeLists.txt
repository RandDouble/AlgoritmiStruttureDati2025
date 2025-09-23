cmake_minimum_required(VERSION 3.14)

project(knapsacksolver VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(gcc_like "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
set(clang_like "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang>")
set(clang_relWithDebug "$<AND:$<CONFIG:RelWithDebInfo>,${clang_like}>")

add_library(proj_compiler_flags INTERFACE)
target_compile_features(proj_compiler_flags INTERFACE cxx_std_23)
target_compile_options(proj_compiler_flags INTERFACE
    "$<${gcc_like}:$<BUILD_INTERFACE:-Wall;-Wextra;-pedantic>>"
    "$<${clang_relWithDebug}:$<BUILD_INTERFACE:-gline-tables-only;-march=native;-fdebug-info-for-profiling;-funique-internal-linkage-names>>"
)



add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_BINARY_DIR}"
)

add_subdirectory(knapsackSolver)

add_subdirectory(testSuite)

target_link_libraries(${PROJECT_NAME} PUBLIC
    knapsack_solver
    test_suite
    proj_compiler_flags
)

