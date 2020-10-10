#include "skiplist.h"

int main() {
    SkipList *skiplist = new SkipList();
    for(int i = 0; i < 100; ++i){
        int32_t t = rand() % 10000;
        printf("Insert:%d\n", t);
        skiplist->Insert(i);
    }
    uint32_t size = skiplist->Size();
    printf("size :%d\n", size);
    skiplist->PrintList();
    return 0;
}