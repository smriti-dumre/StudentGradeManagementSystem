// AVLTree.h
#ifndef AVLTREE_H
#define AVLTREE_H

#include "AVLNode.h"
#include <vector>

class AVLTree {
private:
    AVLNode* root;

    // ========== AVL Utility Functions ==========
    int height(AVLNode* node);
    int getBalance(AVLNode* node);

    AVLNode* rightRotate(AVLNode* y);
    AVLNode* leftRotate(AVLNode* x);

    // ========== Core Recursive Functions ==========
    AVLNode* insertNode(AVLNode* node, const Student& student);
    AVLNode* deleteNode(AVLNode* node, int studentID);
    AVLNode* minValueNode(AVLNode* node);
    AVLNode* searchNode(AVLNode* node, int studentID);
    AVLNode* updateNode(AVLNode* node, const Student& updated);

    void inorderTraversal(AVLNode* node, std::vector<Student>& list);

public:
    AVLTree();

    // Public API (used by the Menu / CLI)
    void insert(const Student& student);
    void remove(int studentID);
    Student* search(int studentID);
    void update(const Student& student);
    std::vector<Student> getAllStudentsSorted();
};

#endif

