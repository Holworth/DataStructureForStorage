#include <cstdio>
#include "BTree.h"

int main()
{
    btree::BTree bt(3);

    bt.insert("1", "good");
    bt.insert("2", "bad");
    bt.insert("3", "tent");
    bt.insert("n", "kasflkkjgal");

    return 0;
}