#ifndef BTREE_H_
#define BTREE_H_

#include <algorithm>
#include <cstdio>
#include <string>
#include <cstring>
#include <stdint.h>
#include <iostream>
#include <math.h>
#include <assert.h>

namespace btree
{

using KeyType = std::string;
using ValType = std::string;
using ItemType = std::pair<KeyType, ValType>;

const int maxn_order = 10;

struct TreeNode 
{
    uint32_t Count;
    uint32_t idx_in_parent;

    ItemType keys[maxn_order];
    struct TreeNode *branchs[maxn_order+1];
    struct TreeNode *parent;
};

class BTree
{
//using idx_t = uint32_t;
public:

    BTree(uint32_t m):
    order_m_(m)
    {
        if(order_m_ > maxn_order) {
            order_m_ = maxn_order;
        }
        tree_root = new TreeNode;
    }

    ~BTree() { std::cout << "Tree is destroyed" << std::endl;}

    ItemType *search(const KeyType &);
    bool insert(const KeyType &, const ValType &);

private:

    void DestroyTree(TreeNode *);

    // search related
    std::pair<TreeNode *, ItemType *> search_helper(const KeyType &);
    uint32_t binary_search(const TreeNode *, const KeyType &) const;


    // insert related
    void insert_leaf_node_without_split(TreeNode *, const KeyType&, const ValType &);
    bool split_node(TreeNode *);
    TreeNode *split_single_node(TreeNode *);
    inline void move_item(ItemType *, ItemType *, size_t);
    inline void move_branch(TreeNode **, TreeNode **, size_t);
    void insert_node_without_split(TreeNode *, TreeNode *, TreeNode *, const KeyType &, const ValType &);

    // other simple functions

    bool NodeKeysExceedLimited(TreeNode *node) const { 
        return node->Count > max_keys_for_node;
    }

    bool NodeKeysBelowLimited(TreeNode *node) const {
        return node->Count < min_keys_for_node;
    }

    bool IsRoot(TreeNode *node) const {
        return node->parent == nullptr;
    }


private:
    uint32_t order_m_;
    TreeNode *tree_root;

    // here are some limit
    const uint32_t max_keys_for_node = order_m_;
    const uint32_t min_keys_for_node = std::ceil(order_m_ / 2.0);
};

} 

#endif