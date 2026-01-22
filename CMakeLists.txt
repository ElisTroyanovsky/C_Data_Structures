cmake_minimum_required(VERSION 4.1)
project(C_data_structure C)

set(CMAKE_C_STANDARD 11)

add_executable(C_data_structure main.c
        Tree/Tree.c
        Tree/Tree.h
        Stack/stack.c
        Stack/stack.h
        AVL_Tree/AVL_tree.c
        AVL_Tree/AVL_tree.h
        Heap/Heap.c
        Heap/Heap.h
        Queue/queue.c
        Queue/queue.h
        Graph/graph.c
        Graph/graph.h
        HashTable/hashTable.c
        HashTable/hashTable.h)
