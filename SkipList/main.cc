#include "skiplist.h"

int main() {
    SkipList *skiplist = new SkipList();
    for(int i = 0; i <= 10; ++i){
        int32_t t = rand() % 100;
        printf("Insert:%d\n", t);
        skiplist->Insert(t);
    }
    uint32_t size = skiplist->Size();
    printf("size :%d\n", size);
    skiplist->PrintList();
    return 0;
}