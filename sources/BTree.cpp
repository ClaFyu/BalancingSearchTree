//
// Created by fuyuki on 19-7-23.
//
#include "../headers/BTree.h"
#include <iostream>

using std::cout;
using std::endl;

BTree::BTree() {
    root = nullptr;
}

BTree::~BTree() {
    clear();
}

void BTree::recursiveClear(BTreeNode *&node) {
    if (node != nullptr) {
        if (!node->isLeaf) {
            for (int i = 0; i <= node->keyNums; i++)
                recursiveClear(node->pChild[i]);
        }
        deleteNode(node);
    }
}

void BTree::deleteNode(BTreeNode *&node) {
    if (node != nullptr) {
        delete node;
        node = nullptr;
    }
}

bool BTree::search(BTreeNode *&node, int key) {
    if (node == nullptr)
        return false;
    else {
        int i = 0;
        for (i = 0; i < node->keyNums && key > node->keyValues[i]; ++i) {}

        if (i < node->keyNums && key == node->keyValues[i])
            return true;
        else {
            if (node->isLeaf)
                return false;
            else
                return search(node->pChild[i], key);
        }
    }
}

void BTree::splitChild(BTreeNode *&parent, int childIndex, BTreeNode *&child) {
    auto* rightNode = new BTreeNode();
    rightNode->isLeaf = child->isLeaf;
    rightNode->keyNums = KEY_MIN;

    for (int i = 0; i < KEY_MIN; i++)
        rightNode->keyValues[i] = child->keyValues[i + CHILD_MIN];

    if (!child->isLeaf) {
        for (int i = 0; i < CHILD_MIN; i++)
            rightNode->pChild[i] = child->pChild[i + CHILD_MIN];
    }

    child->keyNums = KEY_MIN;

    for (int i = parent->keyNums; i > childIndex; i--) {
        parent->pChild[i + 1] = parent->pChild[i];
        parent->keyValues[i] = parent->keyValues[i - 1];
    }

    parent->keyNums++;
    parent->pChild[childIndex + 1] = rightNode;
    parent->keyValues[childIndex] = child->keyValues[KEY_MIN];
}

void BTree::insertNotFull(BTreeNode *&node, int key) {
    int i = node->keyNums;

    if (node->isLeaf) {
        while (i > 0 && key < node->keyValues[i - 1]) {
            node->keyValues[i] = node->keyValues[i - 1];
            --i;
        }
        node->keyValues[i] = key;
        node->keyNums++;
    } else {
        while (i > 0 && key < node->keyValues[i - 1])
            i--;

        auto* child = node->pChild[i];

        if (child->keyNums == KEY_MAX) {
            splitChild(node, i, child);
            if (key > node->keyValues[i])
                child = node->pChild[i + 1];
        }

        insertNotFull(child, key);
    }
}

void BTree::displayInConcavo(BTreeNode *&node, int count) const {
    if (node != nullptr) {
        int i;

        for (i = 0; i < node->keyNums; i++) {
            if (!node->isLeaf)
                displayInConcavo(node->pChild[i], count - 2);
            for (int j = count; j >= 0; j--)
                cout << "*";
            cout << node->keyValues[i] << endl;
        }

        if (!node->isLeaf)
            displayInConcavo(node->pChild[i], count - 2);
    }
}

void BTree::mergeChild(BTreeNode *&parent, int index) {
    auto* child1 = parent->pChild[index];
    auto* child2 = parent->pChild[index + 1];

    child1->keyNums = KEY_MAX;
    child1->keyValues[KEY_MIN] = parent->keyValues[index];

    for (int i = 0; i < KEY_MIN; i++)
        child1->keyValues[i + KEY_MIN + 1] = child2->keyValues[i];

    if (!child1->isLeaf) {
        for (int i = 0; i < CHILD_MIN; i++)
            child1->pChild[i + CHILD_MIN] = child2->pChild[i];
    }

    parent->keyNums--;

    for (int i = index; i < parent->keyNums; i++) {
        parent->keyValues[i] = parent->keyValues[i + 1];
        parent->pChild[i + 1] = parent->pChild[i + 2];
    }

    deleteNode(child2);
}

void BTree::recursiveRemove(BTreeNode *&node, int key) {
    int i = 0;

    while (i < node->keyNums && key > node->keyValues[i])
        i++;

    if (i < node->keyNums && key == node->keyValues[i]) {
        if (node->isLeaf) {
            node->keyNums--;
            for (; i < node->keyNums; i++)
                node->keyValues[i] = node->keyValues[i + 1];
            return;
        } else {
            auto* childPrev = node->pChild[i];
            auto* childNext = node->pChild[i + 1];

            if (childPrev->keyNums >= CHILD_MIN) {
                int prevKey = getPredecessor(childPrev);
                recursiveRemove(childPrev, prevKey);
                node->keyValues[i] = prevKey;
                return;
            } else if (childNext->keyNums >= CHILD_MIN) {
                int nextKey = getSuccessor(childNext);
                recursiveRemove(childNext, nextKey);
                node->keyValues[i] = nextKey;
                return;
            } else {
                mergeChild(node, i);
                recursiveRemove(childPrev, key);
            }
        }
    } else {
        auto* childNode = node->pChild[i];

        if (childNode->keyNums == KEY_MIN) {
            auto* left = i > 0 ? node->pChild[i - 1] : nullptr;
            auto* right = i < node->keyNums ? node->pChild[i + 1] : nullptr;
            int j;

            if (left != nullptr && left->keyNums >= CHILD_MIN) {
                for (j = childNode->keyNums; j > 0; j--)
                    childNode->keyValues[j] = childNode->keyValues[j - 1];
                childNode->keyValues[0] = node->keyValues[i - 1];

                if (!left->isLeaf) {
                    for (j = childNode->keyNums + 1; j > 0; j--)
                        childNode->pChild[j] = childNode->pChild[j - 1];
                    childNode->pChild[0] = left->pChild[left->keyNums];
                }

                childNode->keyNums++;
                node->keyValues[i] = left->keyValues[left->keyNums - 1];
                left->keyNums--;
            } else if (right != nullptr && right->keyNums >= CHILD_MIN) {
                childNode->keyValues[childNode->keyNums] = node->keyValues[i];
                childNode->keyNums++;

                node->keyValues[i] = right->keyValues[0];
                right->keyNums--;

                for (j = 0; j < right->keyNums; j++)
                    right->keyValues[j] = right->keyValues[j + 1];

                if (!right->isLeaf) {
                    childNode->pChild[childNode->keyNums] = right->pChild[0];

                    for (j = 0; j <= right->keyNums; j++)
                        right->pChild[j] = right->pChild[j + 1];
                }
            } else if (left) {
                mergeChild(node, i - 1);
                childNode = left;
            } else if (right)
                mergeChild(node, i);
        }

        recursiveRemove(childNode, key);
    }
}

int BTree::getPredecessor(BTreeNode *&node) {
    while (!node->isLeaf)
        node = node->pChild[node->keyNums];
    return node->keyValues[node->keyNums - 1];
}

int BTree::getSuccessor(BTreeNode *&node) {
    while (!node->isLeaf)
        node = node->pChild[0];
    return node->keyValues[0];
}

bool BTree::insert(int key) {
    if (contain(key))
        return false;
    else {
        if (root == nullptr)
            root = new BTreeNode();

        if (root->keyNums == KEY_MAX) {
            auto* node = new BTreeNode();
            node->isLeaf = false;
            node->pChild[0] = root;
            splitChild(node, 0, root);
            root = node;
        }

        insertNotFull(root, key);
        return true;
    }
}

bool BTree::remove(int key) {
    if (!search(root, key))
        return false;

    if (root->keyNums == 1) {
        if (root->isLeaf) {
            clear();
            return true;
        } else {
            auto* child1 = root->pChild[0];
            auto* child2 = root->pChild[1];

            if (child1->keyNums == KEY_MIN && child2->keyNums == KEY_MIN) {
                mergeChild(root, 0);
                deleteNode(root);
                root = child1;
            }
        }
    }

    recursiveRemove(root, key);
    return true;
}

void BTree::display() {
    displayInConcavo(root, KEY_MAX * 10);
}

bool BTree::contain(int key) {
    return search(root, key);
}

void BTree::clear() {
    recursiveClear(root);
    root = nullptr;
}
