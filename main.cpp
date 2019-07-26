#include <iostream>
#include "headers/AVL.h"
#include "headers/BTree.h"
#include "headers/RBTree.h"

using std::cin;
using std::cout;
using std::endl;

void useAVL() {
    auto avl = new AVL();
    int x;
    bool over = true;

    cout << "现在运行AVL，依次输入数值，以q结尾" << endl;

    while (over) {
        if (!(cin >> x)) {
            cin.clear();
            over = false;
        } else {
            over = avl->insert(x);
        }
    }

    avl->print();
}

void useBTree() {
    auto btree = new BTree();
    int x;
    bool over = true;

    cout << "现在运行BTree，依次输入数值，以q结尾" << endl;

    while (over) {
        if (!(cin >> x)) {
            cin.clear();
            over = false;
        } else {
            over = btree->insert(x);
        }
    }

    btree->display();
}

void useRBTree() {
    auto rbtree = new RBTree();
    int x;
    bool over = true;

    cout << "现在运行RBTree，依次输入数值，以q结尾" << endl;

    while (over) {
        if (!(cin >> x)) {
            cin.clear();
            over = false;
        } else {
            rbtree->insert(x);
        }
    }

    rbtree->print();
}

void useBPlusTree() {

}

int main() {
    int m;

    cout << "1->AVL\t2->BTree\t3->RBTree\t4->B+Tree" << endl;

    if (!(cin >> m)) {
        cin.clear();
        m = 0;
    }

    switch (m) {
        case 1:
            useAVL();
            break;
        case 2:
            useBTree();
            break;
        case 3:
            useRBTree();
            break;
        case 4:
            useBPlusTree();
            break;
        default:
            break;
    }

    return 0;
}