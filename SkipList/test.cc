#include "test.h"

void skiplist_simple_test() {
    SkipList *skiplist = new SkipList();
    for(int i = 0; i < 100; ++i){
        int32_t t = rand() % 10000;
        printf("Insert:%d\n", t);
        skiplist->Insert(i);
    }
    uint32_t size = skiplist->Size();
    printf("size :%d\n", size);
    skiplist->PrintList();
    for(int i = 0; i < 100; ++i) {
        skiplist->Delete(i);
    }
    skiplist->PrintList();
    delete skiplist;
}

void singlelist_simple_test() {
    SingleList *singlelist = new SingleList();
    for(int i = 0; i < 100; ++i) {
        int32_t insert_t = rand() % 10000;
        singlelist->Insert(insert_t);
        assert(singlelist->Find(insert_t)->data == insert_t);
    }
    delete singlelist;
}