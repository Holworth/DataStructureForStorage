#include <cstdio>
#include "BTree.h"

int main()
{
    btree::BTree bt(3);

    bt.insert("1", "good");
    bt.insert("2", "bad");
    bt.insert("3", "tent");
    bt.insert("n", "kasflkkjgal");
    //bt.insert("19", "a");
    bt.insert("8", "ajkfal");
    bt.insert("7", "auiicjak");
    bt.insert("5", "aks");
    bt.insert("4", "sajksalk");
    bt.insert("6", "askal");
    bt.insert("9", "askalkj");
    bt.insert("a", "akzxiao");

    return 0;
}