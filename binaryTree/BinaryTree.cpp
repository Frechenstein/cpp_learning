#include "BinaryTree.h"
#include <iostream>
#include <queue>

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
    if(node != nullptr) {
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }
}

void BinaryTree::preorder() const {
    preorder(root);
    cout << endl;
}

void BinaryTree::preorder(Node* node) const {
    if(node != nullptr) {
        cout << node->data << " ";
        preorder(node->left);
        preorder(node->right);
    }
}

void BinaryTree::postorder() const {
    postorder(root);
    cout << endl;
}

void BinaryTree::postorder(Node* node) const {
    if(node != nullptr) {
        postorder(node->left);
        postorder(node->right);
        cout << node->data << " ";
    }
}

void BinaryTree::levelorder() const {
    if(root == nullptr) {
        return;
    }

    queue<Node*> q;
    q.push(root);

    while(!q.empty()) {
        Node* current = q.front();
        q.pop();

        cout << current->data << " ";

        if(current->left != nullptr) {
            q.push(current->left);
        }
        if(current->right != nullptr) {
            q.push(current->right);
        }
    }

    cout << endl;
}