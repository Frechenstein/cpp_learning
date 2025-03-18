#include "BinaryTree.h"
#include <iostream>

using namespace std;

Node::Node(int value) : data(value), left(nullptr), right(nullptr) {}

BinaryTree::BinaryTree() : root(nullptr) {}

void BinaryTree::insert(int value) {
    insert(root, value);
}

void BinaryTree::insert(Node*& node, int value) {
    if (node == nullptr) {
        node = new Node(value);
    } else if (value < node->data) {
        insert(node->left, value);
    } else {
        insert(node->right, value);
    }
}

void BinaryTree::inorder() const {
    inorder(root);
    cout << endl;
}

void BinaryTree::inorder(Node* node) const {
    if (node != nullptr) {
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }
}