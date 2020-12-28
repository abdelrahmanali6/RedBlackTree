//
// Created by abdelrhman on ١٩‏/١٢‏/٢٠٢٠.
//

#ifndef ASSIGNMENT_NODE_H
#define ASSIGNMENT_NODE_H
#include <stdlib.h>
enum Color { red, black};

class Node {
public:
    Color color;
    int data;
    Node* left, *parent, *right;
    Node(int data, Color = red);

    bool isRight();

    bool isLeft();

    Node* uncle();

    Node* sibling();

    void down(Node* newNode);

    bool hasRedChild();
};


#endif //ASSIGNMENT_NODE_H
