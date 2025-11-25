// AVLTree.cpp
#include "AVLTree.h"
#include <iostream>

// ===================== Constructor =====================
AVLTree::AVLTree() {
    root = nullptr;
}

// ===================== Height Helper =====================
int AVLTree::height(AVLNode* node) {
    if (node == nullptr) return 0;
    return node->height;
}

// ===================== Balance Factor =====================
int AVLTree::getBalance(AVLNode* node) {
    if (node == nullptr) return 0;
    return height(node->left) - height(node->right);
}

// ===================== Right Rotate =====================
AVLNode* AVLTree::rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    // Rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = std::max(height(y->left), height(y->right)) + 1;
    x->height = std::max(height(x->left), height(x->right)) + 1;

    return x;
}

// ===================== Left Rotate =====================
AVLNode* AVLTree::leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    // Rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = std::max(height(x->left), height(x->right)) + 1;
    y->height = std::max(height(y->left), height(y->right)) + 1;

    return y;
}

// ===================== Insert Node (Recursive) =====================
AVLNode* AVLTree::insertNode(AVLNode* node, const Student& student) {
    // Normal BST insert
    if (node == nullptr)
        return new AVLNode(student);

    if (student.getID() < node->data.getID())
        node->left = insertNode(node->left, student);
    else if (student.getID() > node->data.getID())
        node->right = insertNode(node->right, student);
    else {
        std::cout << "Duplicate ID not allowed.\n";
        return node;
    }

    // Update height
    node->height = 1 + std::max(height(node->left), height(node->right));

    // Get balance factor
    int balance = getBalance(node);

    // ========== Perform Rotations if Needed ==========

    // LL Case
    if (balance > 1 && student.getID() < node->left->data.getID())
        return rightRotate(node);

    // RR Case
    if (balance < -1 && student.getID() > node->right->data.getID())
        return leftRotate(node);

    // LR Case
    if (balance > 1 && student.getID() > node->left->data.getID()) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // RL Case
    if (balance < -1 && student.getID() < node->right->data.getID()) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void AVLTree::insert(const Student& student) {
    root = insertNode(root, student);
}

// ===================== Min Value Node =====================
AVLNode* AVLTree::minValueNode(AVLNode* node) {
    AVLNode* current = node;
    while (current->left != nullptr)
        current = current->left;
    return current;
}

// ===================== Delete Node (Recursive) =====================
AVLNode* AVLTree::deleteNode(AVLNode* node, int studentID) {
    if (node == nullptr)
        return node;

    if (studentID < node->data.getID())
        node->left = deleteNode(node->left, studentID);
    else if (studentID > node->data.getID())
        node->right = deleteNode(node->right, studentID);
    else {
        // node with 1 or 0 children
        if (node->left == nullptr || node->right == nullptr) {
            AVLNode* temp = node->left ? node->left : node->right;

            if (temp == nullptr) {
                temp = node;
                node = nullptr;
            }
            else {
                *node = *temp;
            }
            delete temp;
        }
        else {
            // Node with 2 children
            AVLNode* temp = minValueNode(node->right);
            node->data = temp->data;
            node->right = deleteNode(node->right, temp->data.getID());
        }
    }

    if (node == nullptr)
        return node;

    // Update height
    node->height = 1 + std::max(height(node->left), height(node->right));

    // Balance factor
    int balance = getBalance(node);

    // LL
    if (balance > 1 && getBalance(node->left) >= 0)
        return rightRotate(node);

    // LR
    if (balance > 1 && getBalance(node->left) < 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // RR
    if (balance < -1 && getBalance(node->right) <= 0)
        return leftRotate(node);

    // RL
    if (balance < -1 && getBalance(node->right) > 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void AVLTree::remove(int studentID) {
    root = deleteNode(root, studentID);
}

// ===================== Search =====================
AVLNode* AVLTree::searchNode(AVLNode* node, int studentID) {
    if (node == nullptr)
        return nullptr;

    if (studentID == node->data.getID())
        return node;

    if (studentID < node->data.getID())
        return searchNode(node->left, studentID);

    return searchNode(node->right, studentID);
}

Student* AVLTree::search(int studentID) {
    AVLNode* result = searchNode(root, studentID);
    if (result == nullptr) return nullptr;
    return &result->data;
}

// ===================== Update =====================
AVLNode* AVLTree::updateNode(AVLNode* node, const Student& updated) {
    if (node == nullptr) return nullptr;

    if (updated.getID() < node->data.getID())
        node->left = updateNode(node->left, updated);
    else if (updated.getID() > node->data.getID())
        node->right = updateNode(node->right, updated);
    else
        node->data = updated;

    return node;
}

void AVLTree::update(const Student& student) {
    root = updateNode(root, student);
}

// ===================== Inorder Traversal =====================
void AVLTree::inorderTraversal(AVLNode* node, std::vector<Student>& list) {
    if (node == nullptr) return;
    inorderTraversal(node->left, list);
    list.push_back(node->data);
    inorderTraversal(node->right, list);
}

std::vector<Student> AVLTree::getAllStudentsSorted() {
    std::vector<Student> list;
    inorderTraversal(root, list);
    return list;
}
