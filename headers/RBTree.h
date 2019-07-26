//
// Created by Fuyuki on 19/07/25.
//

#ifndef RB_RBTREE_H
#define RB_RBTREE_H

#include <iostream>

struct TreeNode {
    int val;
    bool color;  //红为真
    TreeNode *parent, *lchild, *rchild;

    explicit TreeNode(int x) : val(x), color(true), parent(nullptr), lchild(nullptr), rchild(nullptr) {}
};

class RBTree {
private:
    TreeNode* root;

    void lRotate(TreeNode* node);
    void rRotate(TreeNode* node);
    void reBalance(TreeNode* &node);
    void clear();
    void insertToTree(TreeNode* &node, TreeNode* &nodeT);
    bool findNumFromTree(int x, TreeNode* node);

public:
    RBTree();
    ~RBTree();
    void insert(int x);
    bool findNum(int x);
    void print();
};

#endif //RB_RBTREE_H
