//
// Created by 杨晨 on 2020/9/20.
//

#include "../headers/SkipList.h"

SKNode::SKNode() {
    key = 0;
    for (auto & i : forward) {
        i = nullptr;
    }
}

SKNode & SKNode::operator=(const SKNode *&node) {
    key = node->key;
    for (int i = 0; i < MAXLEVEL; i++) {
        forward[i] = node->forward[i];
    }

    return *this;
}

SkipList::SkipList() {
    hdr = new SKNode;
    listLevel = 0;
    hdr->key = -INT_MAX;
    auto *end = new SKNode;
    auto *first = new SKNode;

    first->key = -INT_MAX;
    end->key = -INT_MAX;

    for (int i = 0; i < MAXLEVEL; i++) {
        hdr->forward[i] = first;
        hdr->forward[i]->forward[i] = end;
    }
    printList();
}

SkipList::~SkipList() {
    delete hdr;
}

SKNode * SkipList::search(int key) const {
    auto *current = new SKNode;
    current = hdr;
    int i = listLevel - 1;

    for (; i >= 0; i--) {
        while ((current->forward[i]->key != INT_MAX) && (key > current->forward[i]->key)) {
            current = current->forward[i];
        }
    }

    current = current->forward[0];
    if (current != nullptr && current->key == key) {
        std::cout << "find" << key << std::endl;
        return current;
    }

    return nullptr;
}

int getInsertLevel() {
    int upCount = 0;
    std::default_random_engine e;

    for (int i = 0; i < MAXLEVEL; i++) {
        int num = (int)e() % 10;
        if (num < 5) {
            upCount++;
        }
    }

    return upCount;
}

int SkipList::insert(int key) {
    int level = getInsertLevel();
    auto *node = new SKNode;
    node->key = key;

    SKNode *s[MAXLEVEL];
    auto *current = new SKNode;
    auto *last = new SKNode;

    for (int i = 0; i < MAXLEVEL; i++) {
        s[i] = hdr->forward[i];
    }

    current = last = hdr;
    std::cout << "hdr " << hdr->key << std::endl;

    int i = listLevel - 1;
    for (; i >= 0; i--) {
        while ((current->forward[i]->key != INT_MAX) && (key > current->forward[i]->key)) {
            current = current->forward[i];
        }

        s[i] = current;
    }

    last = current->forward[0];
    if (last != nullptr && last->key == key) {
        std::cout << "insert key: " << key << " already existed" << std::endl;
        return 0;
    } else {
        std::cout << "insert key: " << key << " successfully" << std::endl;
    }

    if (level > listLevel) {
        listLevel = level;
    }

    for (int k = 0; k < listLevel; k++) {
        node->forward[k] = s[k]->forward[k];
        s[k]->forward[k] = node;
    }
    if (level > listLevel) {
        listLevel = level;
    }

    return 1;
}

int SkipList::deleteNode(int key) const {
    SKNode *s[MAXLEVEL];
    auto *current = new SKNode;
    auto *last = new SKNode;

    for(int i = 0; i < MAXLEVEL; i++)
    {
        s[i] = hdr->forward[i];//initiation
    }
    current = last = hdr;
    for(int i = listLevel - 1; i >= 0; i--) {
        while ((current->forward[i]->key != INT_MAX) && (key > current->forward[i]->key)) {
            current = current->forward[i];
        }
        s[i] = current;//保存每一层位置上的最后指针的前驱
    }
    last = current->forward[0];
    if(last->key != key)
    {
        std::cout << "delete key: " << key << " does not existed" << std::endl;

        return 0;
    }
    for(int i = 0; i < listLevel; i++)
    {
        s[i]->forward[i] = s[i]->forward[i]->forward[i];
    }
    return 1;
}

void SkipList::printList() const {
    auto *current = hdr;

    for (int i = listLevel - 1; i >= 0; i--) {
        current = hdr->forward[i];
        std::cout << "level " << i << "................................" << std::endl;
        while(current->forward[i] != nullptr)  //key大于下一个数据的值。转到本层下一个元素
        {
            std::cout << " " << current->key;
            current = current->forward[i];
        }
        std::cout << " " << current->key << std::endl;
    }
}
