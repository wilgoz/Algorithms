#include "MaxHeap.hh"

#include <iostream>
#include <vector>

int main()
{
    std::vector<int> arr = { 4, 1, 3, 2, 16, 9, 10, 14, 8, 7 };
    MaxHeap<int> root(arr);

    std::cout << "Current highest priority := " << root.peek()
              << std::endl << std::endl;

    std::cout << "Inserting 64 to the heap..."
              << std::endl << std::endl;
    root.insert(64);

    std::cout << "Current highest priority := " << root.peek()
              << std::endl << std::endl;

    root.debug_priority_queue();
}