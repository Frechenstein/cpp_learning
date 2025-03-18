#include <iostream>
#include "BinaryTree.h"

using namespace std;

int main() {

    BinaryTree tree;

    /*
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(1);
    tree.insert(4);
    tree.insert(6);
    tree.insert(8);
    */

    tree.insert(4);
    tree.insert(2);
    tree.insert(6);
    tree.insert(1);
    tree.insert(3);
    tree.insert(5);
    tree.insert(7);

    cout << "Inorder-Traversierung: ";
    tree.inorder();

    cout << "Preorder-Traversierung: ";
    tree.preorder();

    cout << "Postorder-Traversierung: ";
    tree.postorder();

    cout << "Levelorder-Traversierung: ";
    tree.levelorder();

    return 0;
}