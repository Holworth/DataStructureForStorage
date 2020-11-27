#include "BTree.h"

namespace btree
{
    /*
        this function returns the first position where
        the key is greater or equal the target key.
        therefore it's the insert potision(if there 
        is not such key), otherwise the positions's key
        equals to the target key
    */
    uint32_t BTree::binary_search(const TreeNode *node, const KeyType &key) const
    {
        uint32_t bound = node->Count;
        int pos = -1;
        for(uint32_t p = bound; p >= 1; p /= 2)
        {
            while(true) {
                auto np = pos+p;
                KeyType tmp = ((node->keys)[np]).first;
                if(np < node->Count &&  tmp < key) pos = np;
                else break;
            }
        }
        return pos+1;
    }

    /*
        This function do a simple shift operation for a tree node
        parameter TreeNode *node specifies which node need to be shifted
        parameter idx specifies the start of the shifted entries
    */
    void BTree::shift_entry(TreeNode *node, size_t idx)
    {
        for(uint32_t i = node->Count; i > idx; --idx)
        {
            node->keys[i] = node->keys[i-1];
            node->branchs[i+1] = node->branchs[i];
        }
    }

    /*
        This function returns the position of a specific key
        int a B Tree.
        It returns a pair consists of a node pointer and an item
        pointer. The item pointer is not nullptr iff the key is 
        found in the tree, otherwise the node pointer shows which
        node should this key insert
    */

    std::pair<TreeNode *, ItemType *> BTree::search_helper(const KeyType &key)
    {
        TreeNode *tmp = tree_root, *par = tree_root;
        while(tmp)
        {
            uint32_t idx = binary_search(tmp, key);
            // which means the item is not in this tree
            if(idx+1 > tmp->Count) {
                return std::make_pair(tmp, nullptr);
            }
            KeyType x = ((tmp->keys)[idx]).first;
            // if find directly
            if(x == key) {
                return std::make_pair(tmp, (tmp->keys)+idx);
            } else {
                par = tmp;
                tmp = (tmp->branchs)[idx];
            }
        }
        return std::make_pair(par, nullptr);
    }


    /*
        This function returns an item pointer of a target
        key. If the key is found in the tree, it will return
        a true pointer, otherwise it will return nullptr
    */
    ItemType * BTree::search(const KeyType &key)
    {
        auto res = search_helper(key);
        return res.second;
    }


    /*
        This function insert a kv pair into a leaf node, which are given
        in the parameter list. The function executes as follows:
        1. First find a proper position for insertion
        2. Then move data from covered position
        3. Last insert the Key-Value pair
    */

    void BTree::insert_leaf_node_without_split(TreeNode *node, const KeyType &key, const ValType &val)
    {
        uint32_t idx = binary_search(node, key);
        shift_entry(node, idx);
        node->keys[idx] = std::make_pair(key, val);
        node->Count += 1;
    }

    /* 
        This function do a true insert. It executes as follows:
        1.  Search the target key in tree
        2.  If the key exists in tree, then return; otherwise do insertion
        3.  See if split is needed
    */

    bool BTree::insert(const KeyType &key, const ValType &val)
    {
        auto find_res = search_helper(key);
        // which means we have already have this kv pair inside
        if(find_res.second != nullptr) {
            return false;
        }
        // otherwise do some insert
        TreeNode *inserted_node = find_res.first;

        insert_leaf_node_without_split(inserted_node, key, val);

        if(NodeKeysExceedLimited(inserted_node))
        {
            return split_node(inserted_node);
        }
        return true;
    }

    /*
        The following series functions do a complete split process.

        TreeNode *split_single_node():
            Split a single node and return its parent node(if there is one)
        
        void split_node():
            Split nodes in the path from root to the target node.
        
        move_item()/move_branch():
            move item and branches between two tree nodes
        
        insert_node_without_split():
            just like what insert_leaf_node_without_split() do.
            But in this function, we will change two parent branch pointers

    */

    TreeNode * BTree::split_single_node(TreeNode *splited_node)
    {
        assert(NodeKeysExceedLimited(splited_node));
        
        uint32_t old_count = splited_node->Count;
        uint32_t mid = (old_count - 1) >> 1;

        // 0 ~ mid-1 keys belong to the current splited node
        // mid+1 ~ old_count-1 keys belong to the new node
        TreeNode *new_splited = new TreeNode, *par = splited_node->parent;

        // first move data
        move_item(splited_node->keys+mid+1, new_splited->keys, old_count-mid-1);
        move_branch(splited_node->branchs+mid+1, new_splited->branchs, old_count-mid);
        // remember to set Count
        splited_node->Count = mid;
        new_splited->Count = old_count-mid-1;


        if(par == nullptr) {
            par = new TreeNode;
            tree_root = par;
        }
        KeyType mid_key = (splited_node->keys[mid]).first;
        ValType mid_val = (splited_node->keys[mid]).second;

        // set their parent node
        insert_node_without_split(par, splited_node, new_splited, mid_key, mid_val);

        // return parent node as return value;
        return par;
    }

    bool BTree::split_node(TreeNode *node)
    {
        TreeNode *tmp = node;
        // when its parent node has more nodes
        while(NodeKeysExceedLimited(tmp)){
            tmp = split_single_node(tmp);
        }
        return tmp == nullptr;
    }

    /*
        This two functions moves data from one position to 
        another. 
    */

    void BTree::move_item(ItemType *dst, ItemType *src, size_t num)
    {
        for(size_t i = 0; i < num; ++i)
        {
            *(dst++) = *(src++);
        }
    }

    void BTree::move_branch(TreeNode **dst, TreeNode **src, size_t num)
    {
        for(size_t i = 0; i < num; ++i)
        {
            *(dst++) = *(src++);
        }
    }

    void BTree::insert_node_without_split(TreeNode *par, TreeNode *left_sibling, TreeNode *right_sibling, 
                                            const KeyType &key, const ValType &val)
    {
        uint32_t inserted_idx = binary_search(par, key);
        shift_entry(par, inserted_idx);

        par->keys[inserted_idx] = std::make_pair(key, val);
        par->branchs[inserted_idx]   = left_sibling;
        par->branchs[inserted_idx+1] = right_sibling;
        par->Count += 1;
    }
}