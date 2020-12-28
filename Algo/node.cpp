//
// Created by abdelrhman on ١٩‏/١٢‏/٢٠٢٠.
//

#include "Node.h"

Node::Node(int data, Color){
    this->data = data;
    parent = right = left = NULL;
    this->color = color;
}

bool Node::isRight(){
    return this == parent->right;
}

bool Node::isLeft(){
    return this == parent->left;
}

Node* Node::uncle(){
    if(parent == NULL || parent->parent == NULL){
        return NULL;
    }else{
        if(parent->isLeft()){
            return parent->parent->right;
        }else{
            return parent->parent->left;
        }
    }
}

Node* Node::sibling(){
    if(parent == NULL){
        return NULL;
    }else{
        if(isLeft()){
            return parent->right;
        }else{
            return parent->left;
        }
    }
}

void Node::down(Node* newNode){
    if(parent != NULL){
        if(isLeft()){
            parent->left = newNode;
        }else{
            parent->right = newNode;
        }
    }
    newNode->parent = parent;
    parent = newNode;
}

bool Node::hasRedChild() {
    return (left != NULL && left->color == red) || (right != NULL and right->color == red);
}
