//
// Created by fuyuki on 19-7-23.
//

#ifndef ST_AVL_H
#define ST_AVL_H

#include <queue>

struct AVLTreeNode {
    int val;
    int bf;
    int freq;
    AVLTreeNode* left, * right;

    explicit AVLTreeNode(int x) : val(x), bf(0), freq(1), left(nullptr), right(nullptr) {}
};

class AVL {
private:
    AVLTreeNode* root;
    std::queue<AVLTreeNode*> q;
    bool taller;

    void rRotate(AVLTreeNode* &p);
    void lRotate(AVLTreeNode* &p);
    void leftBalance(AVLTreeNode* &p);
    void rightBalance(AVLTreeNode* &p);
    bool insertToTree(AVLTreeNode* &p, int val);
    void preorder(AVLTreeNode* &p);
    void inorder(AVLTreeNode* &p);
    void postorder(AVLTreeNode* &p);
    void levelorder(AVLTreeNode* &p);

public:
    AVL() = default;
    ~AVL() = delete;
    bool insert(int val);
    void print();
};

#endif //ST_AVL_H
