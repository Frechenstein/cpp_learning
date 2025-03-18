#ifndef BINARYTREE_H
#define BINARYTREE_H
#include "Node.h"

class BinaryTree {

    private:
        Node* root;

        void insert(Node*& node, int value);

        void inorder(Node* node) const;
        void preorder(Node* node) const;
        void postorder(Node* node) const;

    public:
        BinaryTree();

        void insert(int value);

        void inorder() const; 
        void preorder() const;
        void postorder() const;
        void levelorder() const;

};

#endif