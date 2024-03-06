add_library(tree STATIC
        tree.cpp
        BaseTreeNode.hpp
        ITree.hpp
        ITraversal.hpp
        TreeNode.hpp
        BinarySearchTree.hpp
        PreorderTraversal.hpp
        InorderTraversal.hpp
        PostorderTraversal.hpp
)

target_include_directories(tree PUBLIC ${PROJECT_SOURCE_DIR})
