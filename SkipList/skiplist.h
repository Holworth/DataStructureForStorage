#ifndef SKIPLIST_H_
#define SKIPLIST_H_

#include <cstdio>
#include <cstdlib>
#include <stdint.h>

class SkipList {

    static const uint8_t kMaxLevel = 5;

    struct SkipListNode {
        int32_t data;
        SkipListNode *next, *below;

        SkipListNode(): data(0), next(nullptr), below(nullptr) {}
    };

    private:

        SkipListNode list_[kMaxLevel + 1];

    public:

        bool Empty() const;
        bool Insert(const int32_t data);
        SkipListNode *Find(const int32_t data);
        bool Delete(const int32_t data);
};


#endif




