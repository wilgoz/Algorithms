#include "BST.hh"
#include <iostream>

int main()
{
    int del  =  8;
    int find = 13;
    int succ =  4;

    BST<int> root(8);

    root.insert(3);
    root.insert(15);
    root.insert(4);
    root.insert(11);
    root.insert(16);
    root.insert(13);
    root.insert(10);
    root.insert(14);
    root.insert(20);

    std::cout << std::endl << "POSTORDER TRAVERSAL\t: ";
    root.show_postorder();
    std::cout << std::endl;

    std::cout << std::endl << "SUCCESSOR OF " << succ << "\t\t: "
              << root.get_successor(succ) << std::endl;

    root.delete_node(del);
    std::cout << std::endl << "AFTER DELETING " << del << "\t: ";
    root.show_postorder();
    std::cout << std::endl;

    std::cout << std::endl << "SEARCHING FOR KEY " << find << "..."
              << std::endl;
    if (root.search(find))
        std::cout << "KEY FOUND" << std::endl;
}
