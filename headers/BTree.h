//
// Created by fuyuki on 19-7-23.
//

#ifndef ST_BTREE_H
#define ST_BTREE_H

static const int M = 3;
static const int KEY_MAX = 2 * M - 1;
static const int KEY_MIN = M - 1;
static const int CHILD_MAX = KEY_MAX + 1;
static const int CHILD_MIN = KEY_MIN + 1;

struct BTreeNode {
    bool isLeaf;
    int keyNums;
    int *keyValues = new int[KEY_MAX];
    BTreeNode* *pChild = new BTreeNode*[CHILD_MAX];

    explicit BTreeNode(bool b = true, int n = 0) : isLeaf(b), keyNums(n) {}
};

class BTree {
private:
    BTreeNode* root;

    void recursiveClear(BTreeNode* &node);
    void deleteNode(BTreeNode* &node);
    bool search(BTreeNode* &node, int key);
    void splitChild(BTreeNode* &parent, int childIndex, BTreeNode* &child);
    void insertNotFull(BTreeNode* &node, int key);
    void displayInConcavo(BTreeNode* &node, int count) const;
    void mergeChild(BTreeNode* &parent, int index);
    void recursiveRemove(BTreeNode* &node, int key);
    int getPredecessor(BTreeNode* &node);
    int getSuccessor(BTreeNode* &node);

public:
    BTree();
    ~BTree();
    bool insert(int key);
    bool remove(int key);
    void display();
    bool contain(int key);
    void clear();
};

#endif //ST_BTREE_H
