add_library(test_suite INTERFACE test_suite.h)

target_include_directories(test_suite INTERFACE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
    "$<INSTALL_INTERFACE:include>"
)

target_link_libraries(test_suite INTERFACE
    proj_compiler_flags
)