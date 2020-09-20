#include <iostream>
#include "headers/AVL.h"
#include "headers/BTree.h"
#include "headers/RBTree.h"
#include "headers/SkipList.h"

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

void useBPlusTree() {}

void useSkipList() {
    auto slist = new SkipList();
    char x;
    int n;
    bool over = true;

    cout << "现在运行SkipList, I num 表示插入元素，S num 表示搜索元素，D num 表示删除元素，P 表示列表" << endl;

    while (over) {
        cin >> x;
        if (cin.fail()) {
            cout << "输入错误，重新来过" << endl;
            cin.clear();
            continue;
        }

        if (x == 'I') {
            cin >> n;
            slist->insert(n);
        }
        else if (x == 'S') {
            cin >> n;
            slist->search(n);
        }
        else if (x == 'D') {
            cin >> n;
            slist->deleteNode(n);
        }
        else if (x == 'P') {
            slist->printList();
        } else {
            over = false;
        }
    }
}

int main() {
    int m;

    cout << "1->AVL\t2->BTree\t3->RBTree\t4->B+Tree\t5->SkipList" << endl;

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
        case 5:
            useSkipList();
            break;
        default:
            break;
    }

    return 0;
}