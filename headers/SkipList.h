//
// Created by 杨晨 on 2020/9/20.
//

#ifndef ST_SKIPLIST_H
#define ST_SKIPLIST_H

#include <iostream>
#include <random>

#define MAXLEVEL 10      // log(n) / log(2)

class SKNode {
public:
    int key = 0;
    SKNode* forward[MAXLEVEL]{};

    SKNode();

    SKNode &operator=(const SKNode *&node);
};

class SkipList {
public:
    SKNode *hdr = nullptr;
    int listLevel = 0;

    int insert(int key);
    SKNode* search(int key) const;
    int deleteNode(int key) const;
    void printList() const;

    SkipList();
    ~SkipList();
};

#endif //ST_SKIPLIST_H
