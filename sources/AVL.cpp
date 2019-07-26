//
// Created by fuyuki on 19-7-23.
//
#include <iostream>
#include "../headers/AVL.h"

using std::cout;
using std::endl;

void AVL::rRotate(AVLTreeNode* &p) {
    auto* node = p->left;
    p->left = node->right;
    node->right = p;
    p = node;
}

void AVL::lRotate(AVLTreeNode* &p) {
    auto* node = p->right;
    p->right = node->left;
    node->left = p;
    p = node;
}

void AVL::leftBalance(AVLTreeNode* &p) {
    auto* node = p->left;

    switch (node->bf) {
        case 1:
            p->bf = node->bf = 0;
            rRotate(p);
            break;
        case -1: {
            auto* t = node->right;
            switch (t->bf) {
                case 1:
                    node->bf = 0;
                    p->bf = -1;
                    break;
                case 0:
                    node->bf = 0;
                    p->bf = 0;
                    break;
                case -1:
                    node->bf = 1;
                    p->bf = 0;
                    break;
                default:
                    break;
            }
            t->bf = 0;
            lRotate(p->left);
            rRotate(p);
            break;
        }
        default:
            break;
    }
}

void AVL::rightBalance(AVLTreeNode* &p) {
    auto* node = p->right;

    switch (node->bf) {
        case 1: {
            auto *t = node->left;
            switch (t->bf) {
                case 1:
                    p->bf = 0;
                    node->bf = -1;
                    break;
                case 0:
                    p->bf = 0;
                    node->bf = 0;
                    break;
                case -1:
                    p->bf = 1;
                    node->bf = 0;
                    break;
                default:
                    break;
            }

            t->bf = 0;
            rRotate(p->right);
            lRotate(p);
            break;
        }
        case -1:
            p->bf = node->bf = 0;
            lRotate(p);
            break;
        default:
            break;
    }
}

bool AVL::insertToTree(AVLTreeNode* &p, int val) {
    if (p == nullptr) {
        p = new AVLTreeNode(val);
        taller = true;
    } else {
        if (p->val == val) {
            p->freq++;
        } else if (p->val > val) {
            if (!insertToTree(p->left, val))
                return false;
            if (taller) {
                switch (p->bf) {
                    case 1:
                        leftBalance(p);
                        taller = false;
                        break;
                    case 0:
                        taller = true;
                        p->bf = 1;
                        break;
                    case -1:
                        taller = false;
                        p->bf = 0;
                        break;
                    default:
                        break;
                }
            }
        } else {
            if (!insertToTree(p->right, val))
                return false;
            if (taller) {
                switch (p->bf) {
                    case 1:
                        p->bf = 0;
                        taller = false;
                        break;
                    case 0:
                        p->bf = -1;
                        taller = true;
                        break;
                    case -1:
                        rightBalance(p);
                        taller = false;
                        break;
                    default:
                        break;
                }
            }
        }
    }

    return true;
}

void AVL::preorder(AVLTreeNode* &p) {
    if (p == nullptr)
        return;

    cout << p->val << "\t";
    if (p->left != nullptr)
        inorder(p->left);
    if (p->right != nullptr)
        inorder(p->right);
}

void AVL::inorder(AVLTreeNode* &p) {
    if (p == nullptr)
        return;

    if (p->left != nullptr)
        inorder(p->left);
    cout << p->val << "\t";
    if (p->right != nullptr)
        inorder(p->right);
}

void AVL::postorder(AVLTreeNode* &p) {
    if (p == nullptr)
        return;

    if (p->left != nullptr)
        inorder(p->left);
    if (p->right != nullptr)
        inorder(p->right);
    cout << p->val << "\t";
}

void AVL::levelorder(AVLTreeNode *&p) {
    q.push(p);

    if (q.front() == nullptr) {
        q.pop();
        return;
    }
    else {
        while (!q.empty()) {
            auto* node = q.front();

            if (node->left != nullptr)
                q.push(node->left);
            if (node->right != nullptr)
                q.push(node->right);

            q.pop();
            cout << node->val << "\t";
        }
    }
}

bool AVL::insert(int val) {
    auto a = insertToTree(root, val);
    return a;
}

void AVL::print() {
    cout << "先序： ";
    preorder(root);
    cout << endl;

    cout << "中序： ";
    inorder(root);
    cout << endl;

    cout << "后序： ";
    postorder(root);
    cout << endl;

    cout << "层序： ";
    levelorder(root);
    cout << endl;
}
