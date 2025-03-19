#include <iostream>
#include <vector>
#include "BinaryTree.h"

using namespace std;

int main() {

    BinaryTree tree;

    // Tree with h = 3
    /*
    tree.insert(4);
    tree.insert(2);
    tree.insert(6);
    tree.insert(1);
    tree.insert(3);
    tree.insert(5);
    tree.insert(7);
    */

    // Tree with h = 4;
    ///*
    tree.insert(8);
    tree.insert(4);
    tree.insert(12);
    tree.insert(2);
    tree.insert(6);
    tree.insert(10);
    tree.insert(14);
    tree.insert(1);
    tree.insert(3);
    tree.insert(5);
    tree.insert(7);
    tree.insert(9);
    tree.insert(11);
    tree.insert(13);
    tree.insert(15);
    //*/

    cout << endl;
    cout << "Inorder-Traversierung: ";
    tree.inorder();
    cout << "Preorder-Traversierung: ";
    tree.preorder();
    cout << "Postorder-Traversierung: ";
    tree.postorder();
    cout << "Levelorder-Traversierung: ";
    tree.levelorder();
    cout << endl;

    tree.printTree();

    vector<int> searchingFor = {5, 8, 69, 3, -1};
    for(int num : searchingFor) {
        cout << "Value " << num << " is present: " << tree.isValuePresent(tree.search(num)) << endl;
    }
    cout << endl;

    return 0;
}