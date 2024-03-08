add_library(tree INTERFACE
        ITreeNode.hpp
        ITree.hpp
        ITraversal.hpp
        TreeNode.hpp
        BinarySearchTree.hpp
        PreOrder.hpp
        InOrder.hpp
        PostOrder.hpp
)

target_include_directories(tree INTERFACE ${PROJECT_SOURCE_DIR})
