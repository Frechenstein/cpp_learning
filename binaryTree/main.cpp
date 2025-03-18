#include <iostream>
#include "BinaryTree.h"

using namespace std;

int main() {

    BinaryTree tree;

    tree.insert(5);
    tree.insert(3);
    tree.insert(7);

    cout << "Inorder-Traversierung: ";
    tree.inorder();

    return 0;
}