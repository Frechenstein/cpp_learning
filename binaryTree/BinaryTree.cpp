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

void BinaryTree::remove(int value) {
    remove(root, value);
}

Node* BinaryTree::remove(Node* node, int value) {
    if(node == nullptr) {
        return node; 
    }

    if(value < node->data) {
        node->left = remove(node->left, value);
    } else if(value > node->data) {
        node->right = remove(node->left, value);
    } else {

        if(node->left == nullptr) {
            return node->right;
        }

        if(node->right == nullptr) {
            return node->left;
        }

        Node* succ = getSuccessor(node);
        node->data = succ->data;
        node->right = remove(node->right, succ->data);

    }
    return node;
}

Node* BinaryTree::getSuccessor(Node* node) {
    node = node->right;
    while(node != nullptr && node->left != nullptr) {
        node = node->left;
    }
    return node;
}

Node* BinaryTree::search(int value) const {  
    return search(root, value);
}

Node* BinaryTree::search(Node* node, int value) const {
    if(node != NULL) {
        if(node->data == value) {
            return node;
        } else if(value < node->data) {
            return search(node->left, value);
        } else if (value > node->data) {
            return search(node->right, value);
        }
    } else {
        return NULL;
    }
}

bool BinaryTree::isValuePresent(Node* node) const {
    if(node != NULL) {
        return true;
    } else {
        return false;
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

void BinaryTree::printTree() const {
    if(root == nullptr) {
        cout << "Tree is empty!" << endl;
        return;
    }

    cout << "The tree looks like this: " << endl;

    queue<Node*> q;
    q.push(root);
    int defLineCounter = 1;
    int lineCounter = defLineCounter;

    while(!q.empty()) {
        Node* current = q.front();
        q.pop();
        defLineCounter--;
        lineCounter--;

        cout << current->data << " ";

        if(lineCounter == 0) {
            cout << endl;
        }

        if(current->left != nullptr) {
            q.push(current->left);
            defLineCounter++;
        }
        if(current->right != nullptr) {
            q.push(current->right);
            defLineCounter++;
        }

        if(lineCounter == 0) {
            lineCounter = defLineCounter;
        }
    }

    cout << endl;

}