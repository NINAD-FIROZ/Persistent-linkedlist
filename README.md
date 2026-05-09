# Persistent Linked List (C)

A memory-efficient implementation of a persistent linked list in C, utilizing a path-copying strategy to maintain version history. 

Instead of duplicating the entire data structure upon modification, this implementation uses structural sharing. When an insertion or modification occurs, it recursively copies only the nodes along the direct path to the changed element, reusing the unchanged tail segments from previous versions. 

## Key Technical Features
* **Path Copying:** Achieves persistence with optimal memory usage by minimizing redundant node allocation.
* **Structural Sharing:** Older versions of the list share unchanged sub-trees/tails with newer versions.
* **Version History Tracking:** Maintains an array of head pointers, allowing O(1) access to the starting node of any historical state of the list.
* **Manual Memory Management:** Written purely in C, demonstrating low-level pointer manipulation and dynamic memory allocation (`malloc`/`free`).

## Tech Stack
* Language: C
* Core Concepts: Data Structures, Persistence, Pointer Manipulation, Memory Management
