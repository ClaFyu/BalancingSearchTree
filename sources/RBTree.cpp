//
// Created by Fuyuki on 19/07/25.
//
#include "../headers/RBTree.h"

using std::cout;
using std::endl;

RBTree::RBTree() : root(nullptr) {}

RBTree::~RBTree() {
    clear();
}

void RBTree::lRotate(TreeNode *node) {  // node为旋转点，所有操作rRotate同理
    auto* y = node->rchild;  //令y为旋转点的右子节点
    node->rchild = y->lchild;

    if (y->lchild != nullptr)
        y->lchild->parent = node;  //设定父节点

    y->parent = node->parent;  //y将node的有关父节点的关系全部接受

    if (node == root)
        root = y;
    else if (node == node->parent->lchild)
        node->parent->lchild = y;
    else
        node->parent->rchild = y;

    y->lchild = node;
    node->parent = y;
}

void RBTree::rRotate(TreeNode *node) {
    auto* y = node->lchild;
    node->lchild = y->rchild;

    if (y->rchild != nullptr)
        y->rchild->parent = node;

    y->parent = node->parent;

    if (node == root)
        root = y;
    else if (node == node->parent->rchild)
        node->parent->rchild = y;
    else
        node->parent->lchild = y;

    y->rchild = node;
    node->parent = y;
}

void RBTree::reBalance(TreeNode *&node) {  //重平衡函数，在将新点插入树后使用，保证树维持平衡状态
    node->color = true;  //新节点必是一个红节点

    while (node != root && node->parent->color) {
        if (node->parent == node->parent->parent->lchild) {
            auto* y = node->parent->parent->rchild;  //y为伯父节点
            if (y != nullptr && y->color) {  //伯父节点存在且为红
                node->parent->color = false;  //更改父节点为黑
                y->color = false;             //更改伯父节点为黑
                node->parent->parent->color = true;  //更改祖父节点为红
                node = node->parent->parent;
            } else {  //无伯父节点或其为黑
                if (node == node->parent->rchild) {
                    node = node->parent;
                    lRotate(node);  //node移动到父节点并左旋
                }
                node->parent->color = false;
                node->parent->parent->color = true;
                rRotate(node->parent->parent);
            }
        } else {
            auto* y = node->parent->parent->lchild;
            if (y != nullptr && y->color) {
                node->parent->color = false;
                y->color = false;
                node->parent->parent->color = true;
                node = node->parent->parent;
            } else {
                if (node == node->parent->lchild) {
                    node = node->parent;
                    rRotate(node);
                }
                node->parent->color = false;
                node->parent->parent->color = true;
                lRotate(node->parent->parent);
            }
        }
    }

    root->color = false;  //根节点永远为黑色
}

void deleteNode(TreeNode* &node) {
    if (node->lchild != nullptr)
        deleteNode(node->lchild);
    if (node->rchild != nullptr)
        deleteNode(node->rchild);

    free(node);
    node = nullptr;
}

void RBTree::clear() {
    deleteNode(root);
}

void RBTree::insertToTree(TreeNode *&node, TreeNode *&nodeT) {
    if (root == nullptr) {
        root = node;
        root->color = false;
        return;
    }

    if (node->val < nodeT->val && nodeT->lchild != nullptr)
        insertToTree(node, nodeT->lchild);
    else if (node->val < nodeT->val && nodeT->lchild == nullptr) {
        nodeT->lchild = node;
        node->parent = nodeT;

        reBalance(node);
    } else if (node->val > nodeT->val && nodeT->rchild != nullptr)
        insertToTree(node, nodeT->rchild);
    else if (node->val > nodeT->val && nodeT->rchild == nullptr) {
        nodeT->rchild = node;
        node->parent = nodeT;

        reBalance(node);
    } else
        return;
}

void RBTree::insert(int x) {
    auto* node = new TreeNode(x);
    insertToTree(node, root);
}

bool RBTree::findNumFromTree(int x, TreeNode *node) {
    if (x < node->val) {
        if (node->lchild != nullptr)
            return findNumFromTree(x, node->lchild);
        else
            return false;
    } else if (x > node->val){
        if (node->rchild != nullptr)
            return findNumFromTree(x, node->rchild);
        else
            return false;
    } else
        return true;
}

bool RBTree::findNum(int x) {
    return findNumFromTree(x, root);
}

void findParent(TreeNode* node, int i) {
    if (node->parent != nullptr) {
        findParent(node->parent, i + 1);
        if (i != 0)
            cout << node->val << "-" << (node->color ? "red" : "black") << " -> ";
        else
            cout << node->val << "-" << (node->color ? "red" : "black");
    } else
        cout << node->val << "-" << (node->color ? "red" : "black") << " -> ";
}

void inorder(TreeNode* node) {
    int i = 0;
    bool isLeaf = node->lchild == nullptr && node->rchild == nullptr;

    if (node->lchild != nullptr)
        inorder(node->lchild);
    cout << node->val << "\t" << (isLeaf ? "leaf\t" : "non-leaf") << "\t\t";
    findParent(node, i);
    cout << endl;
    if (node->rchild != nullptr)
        inorder(node->rchild);
}

void RBTree::print() {
    inorder(root);
}
