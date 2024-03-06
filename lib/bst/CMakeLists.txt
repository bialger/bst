add_library(bst STATIC
        bst.cpp
        BST.hpp
        BstIterator.hpp
)

target_link_libraries(bst PUBLIC tree)

target_include_directories(bst PUBLIC ${PROJECT_SOURCE_DIR})
