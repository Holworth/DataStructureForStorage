#ifndef SKIPLIST_H_
#define SKIPLIST_H_

#include <cstdio>
#include <cstdlib>
#include <stdint.h>
#include <iostream>
#include <vector>
#include <assert.h>

class SkipList {

    // max levels a skiplist has;
    static const uint8_t kMaxLevel = 5;
    enum NodeType {header, node} ;
    struct SkipListNode {
        // only support simple data currently
        int32_t data;
        size_t size;
        NodeType type;
        SkipListNode *next, *below;

        SkipListNode(): 
            data(0), type(node),
            next(nullptr), 
            below(nullptr) { }
        SkipListNode(int32_t a, NodeType ntype): 
            data(a), type(ntype), 
            next(nullptr), below(nullptr) { }
    };


    private:

        SkipListNode* list_[kMaxLevel + 1];
        SkipListNode* BinarySearchHelper(uint32_t search_level, int32_t data);


    
    public:
        // default constructor
        SkipList() { }
        // construct list from initialization array
        SkipList(std::vector<int32_t> init) { }
        ~SkipList() {}


    public:

        bool Empty() const;
        size_t Size() const;
        bool Insert(const int32_t data);
        SkipListNode *Find(const int32_t data);
        bool Delete(const int32_t data);
};


#endif




