//
// Created by abdelrhman on ٢٥‏/١٢‏/٢٠٢٠.
//

#include "RedBlackTree.h"
#include <iostream>
#include <string>
using namespace std;

RedBlackTree::RedBlackTree(){
    root = NULL;
}

Node* RedBlackTree::getRoot(){
    return root;
}


string RedBlackTree::printTree()
{
    int height = maxHeight(root);
    string tree = "";
    int maxSlot;
    maxSlot = maxHeight(root) * 2;
    for (int counter = 1; counter <= height ; counter++){
        tree += "Level" + to_string(counter - 1) + "    ";
        printLevel(root, counter, tree, maxSlot);
        tree += "\n";
    }
    return tree;
}

void RedBlackTree::printLevel(const Node* temp, int level, string& result, int maxSlot)
{
    if (temp == NULL) {
        return;
    }
    if (level == 1) {
        /*int x = getLevel(root, temp->data);
            for (int i = 0; i < maxSlot/(pow(2,x)) ;++i) {
                result += " ";
            }*/
        result += to_string(temp->data) + " ";
        /*if(temp->left == NULL || temp->right == NULL){
            for (int i = 0; i < maxSlot/(pow(2,x)) ;++i) {
                result += "l";
            }
        }*/
    }
    else if (level > 1)
    {
        printLevel(temp->left, level - 1, result, maxSlot/2);
        printLevel(temp->right, level - 1, result, maxSlot/2);
    }
}

void RedBlackTree::leftRotate(Node *target) {
    Node* newParent = target->right;
    if(root == target){
        root = newParent;
    }
    target->down(newParent);
    target->right = newParent->left;
    if(newParent->left != NULL){
        newParent->left->parent = target;
    }
    newParent->left = target;
}

void RedBlackTree::rightRotate(Node *target) {
    Node* newParent = target->left;
    if(target == root){
        root = newParent;
    }
    target->down(newParent);
    target->left = newParent->right;
    if(newParent->right != NULL){
        newParent->right->parent = target;
    }
    newParent->right = target;
}

void RedBlackTree::swapColor(Node *first, Node *second) {
    Color temp;
    temp = first->color;
    first->color = second->color;
    second->color = temp;
}

void RedBlackTree::swapData(Node *first, Node *second) {
    {
        int temp;
        temp = first->data;
        first->data = second->data;
        second->data = temp;
    }
}

void RedBlackTree::redRedConflict(Node *target){
    //case 1
    if(target == root){
        target->color = black;
        return;
    }

    Node* targetParent = target->parent;
    Node* targetUncle = target->uncle();
    Node* targetGrandParent = target->parent->parent;
    if(targetParent->color == red){
        if(targetUncle != NULL && targetUncle->color == red){
            targetParent->color = black;
            targetUncle->color = black;
            targetGrandParent->color = red;
            redRedConflict(targetGrandParent);
        }else{
            if(targetParent->isLeft()){
                if(target->isLeft()){
                    swapColor(targetParent,targetGrandParent);
                }else{
                    leftRotate(targetParent);
                    swapColor(target,targetGrandParent);
                }
                rightRotate(targetGrandParent);
            }else{
                if(target->isLeft()){
                    rightRotate(targetParent);
                    swapColor(target, targetGrandParent);
                }else{
                    swapColor(targetParent, targetGrandParent);
                }
                leftRotate(targetGrandParent);
            }
        }
    }
}

Node *RedBlackTree::getSuccessor(Node *target) {
    Node* temp = target;
    while (temp->left != NULL){
        temp = temp->left;
    }
    return temp;
}

Node *RedBlackTree::replaceNode(Node *target) {
    if(target->left != NULL && target->right != NULL){
        return  getSuccessor(target->right);
    }
    if(target->left == NULL && target->right == NULL){
        return  NULL;
    }
    if(target->left != NULL){
        return  target->left;
    }else{
        return  target->right;
    }
}

Node *RedBlackTree::isExist(int n) {
    Node *temp = root;
    while (temp != NULL) {
        if (n < temp->data) {
            if (temp->left == NULL)
                break;
            else
                temp = temp->left;
        } else if (n == temp->data) {
            break;
        } else {
            if (temp->right == NULL)
                break;
            else
                temp = temp->right;
        }
    }

    return temp;
}

void RedBlackTree::insert(int n){
    Node*newNode=new Node(n);
    if(root==NULL){
        newNode->color=black;
        root=newNode;
    }
    else{
        Node*node=isExist(n);
        if(node->data!=n){
            newNode->parent=node;
            if(n>node->data){
                node->right=newNode;
            }
            else{
                node->left=newNode;
            }
        }
    }
}

void RedBlackTree::deleteNode(Node *target) {
    Node* targetSuccessor = replaceNode(target);
    bool targetSuccessorBlack;
    if((targetSuccessor == NULL || targetSuccessor->color == black) &&
       (target->color == black)){
        targetSuccessorBlack = true;
    }else{
        targetSuccessorBlack = false;
    }
    Node* targetParent = target->parent;
    if (targetSuccessor == NULL) {
        if (target == root) {
            root = NULL;
        } else {
            if (targetSuccessorBlack) {
                doubleBlack(target);
            } else {
                if (target->sibling() != NULL)
                    target->sibling()->color = red;
            }
            if (target->isLeft()) {
                targetParent->left = NULL;
            } else {
                targetParent->right = NULL;
            }
        }
        delete target;
        return;
    }
    if (target->left == NULL or target->right == NULL) {
        if (target == root) {
            target->data = targetSuccessor->data;
            target->left = target->right = NULL;
            delete targetSuccessor;
        } else {
            if (target->isLeft()) {
                targetParent->left = targetSuccessor;
            } else {
                targetParent->right = targetSuccessor;
            }
            delete target;
            targetSuccessor->parent = targetParent;
            if (targetSuccessorBlack) {
                doubleBlack(targetSuccessor);
            } else {
                targetSuccessor->color = black;
            }
        }
        return;
    }
    swapData(targetSuccessor, target);
    deleteNode(targetSuccessor);
}

void RedBlackTree::doubleBlack(Node *target){
    if(target != root){
        Node* targetSibling = target->sibling();
        Node* targetParent = target->parent;
        if(targetSibling == NULL){
            doubleBlack(targetParent);
        }else {
            if (targetSibling->hasRedChild()) {
                if (targetSibling->left != NULL && targetSibling->left->color == red) {
                    if (targetSibling->isLeft()) {
                        targetSibling->left->color = targetSibling->color;
                        targetSibling->color = targetParent->color;
                        rightRotate(targetParent);
                    } else {
                        targetSibling->left->color = targetParent->color;
                        rightRotate(targetSibling);
                        leftRotate(targetParent);
                    }
                } else {
                    if (targetSibling->isLeft()) {
                        targetSibling->right->color = targetParent->color;
                        leftRotate(targetSibling);
                        rightRotate(targetParent);
                    } else {
                        targetSibling->right->color = targetSibling->color;
                        targetSibling->color = targetParent->color;
                        leftRotate(targetParent);
                    }
                }
                targetParent->color = black;
            } else {
                targetSibling->color = red;
                if (targetParent->color == black)
                    doubleBlack(targetParent);
                else
                    targetParent->color = black;
            }
        }
    }
}

void RedBlackTree::printInorder(Node *temp) {
    if (temp == NULL) {
        return;
    }
    printInorder(temp->left);
    cout << temp->data << " ";
    printInorder(temp->right);
}

Node* RedBlackTree::search(int target) {
    Node *temp = root;
    while (temp != NULL) {
        if (target < temp->data) {
            if (temp->left == NULL) {
                break;
            }
            else{
                temp = temp->left;
            }
        } else if (target == temp->data) {
            break;
        } else {
            if (temp->right == NULL){
                break;
            }else {
                temp = temp->right;
            }
        }
    }
    return temp;
}

void RedBlackTree::deleteByVal(int target) {
    if (root == NULL) {
        return;
    }
    Node *temp = search(target);
    if (temp->data != target) {
        cout << "Value doesn't exist" << endl;
        return;
    }
    deleteNode(temp);
}

void RedBlackTree::printInOrder() {
    cout << "inorder:__" << endl;
    if (root == NULL){
        cout << "Tree is empty" << endl;
    }else {
        printInorder(root);
    }
    cout << endl;
}


int RedBlackTree::maxHeight(const Node* temp)
{
    if (temp == NULL) {
        return 0;
    }
    else{
        int LeftDepth = maxHeight(temp->left);
        int rightDepth = maxHeight(temp->right);
        if (LeftDepth > rightDepth) {
            return (LeftDepth + 1);
        }else{
            return(rightDepth + 1);
        }
    }
}

void RedBlackTree::clear(Node* root){
    if (root == NULL)
    {
        return;
    }
    clear(root->left);
    clear(root->right);
    delete root;
}

void RedBlackTree::clear(){
    clear(root);
    root = NULL;
}
