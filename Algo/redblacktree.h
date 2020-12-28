//
// Created by abdelrhman on ٢٥‏/١٢‏/٢٠٢٠.
//

#ifndef REDBLACKTREE_REDBLACKTREE_H
#define REDBLACKTREE_REDBLACKTREE_H


#include "Node.h"
#include <iostream>
#include <cmath>

using namespace  std;
class RedBlackTree {
public:
    RedBlackTree();
    Node* getRoot();
    void insert(int n);
    void deleteByVal(int target);
    void printInOrder();
    string printTree();
    void printLevel(const Node* temp, int level, string& result, int maxSlot);
    void clear();
private:
    Node* root;
    void leftRotate(Node* target);
    void rightRotate(Node* target);
    void swapColor(Node* first, Node* second);
    void swapData(Node* first, Node* second);
    void redRedConflict(Node* target);
    Node* getSuccessor(Node* target);
    Node* replaceNode(Node* target);
    void deleteNode(Node* target);
    Node* isExist(int n);
    void doubleBlack(Node *target);
    void printInorder(Node *temp);
    Node *search(int target);
    int maxHeight(const Node* temp);
    void clear(Node* root);
};


#endif //REDBLACKTREE_REDBLACKTREE_H
