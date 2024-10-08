include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
        ${PROJECT_NAME}_tests
        bst_unit_tests.cpp
        bst_traversal_unit_tests.cpp
        tree_unit_tests.cpp
        tree_traversal_unit_tests.cpp
        concepts_tests.cpp
        test_functions.cpp
        test_functions.hpp
        BstUnitTestSuite.cpp
        BstUnitTestSuite.hpp
        TreeUnitTestSuite.cpp
        TreeUnitTestSuite.hpp
        TreeTraversalUnitTestSuite.cpp
        TreeTraversalUnitTestSuite.hpp
        BstTraversalUnitTestSuite.cpp
        BstTraversalUnitTestSuite.hpp
        custom_classes.hpp
)

target_link_libraries(${PROJECT_NAME}_tests PUBLIC
        bst
        tree
        GTest::gtest_main
)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug) # Tests should be built with Debug
endif()

message(STATUS "Tests build type: ${CMAKE_BUILD_TYPE}")

target_include_directories(${PROJECT_NAME}_tests PUBLIC ${PROJECT_SOURCE_DIR})

include(GoogleTest)

gtest_discover_tests(${PROJECT_NAME}_tests)