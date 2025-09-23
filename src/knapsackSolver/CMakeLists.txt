add_library(knapsack_solver "")


target_include_directories(knapsack_solver PUBLIC
"$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
"$<INSTALL_INTERFACE:include>"
)

target_sources(knapsack_solver
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/knapsack_solver.cpp
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/knapsack_solver.h
        ${CMAKE_CURRENT_SOURCE_DIR}/map_key.h
)
target_link_libraries(knapsack_solver INTERFACE
    proj_compiler_flags
)