#include "skiplist.h"

int main() {
    SkipList *skiplist = new SkipList();
    for(int32_t i = 0; i <= 10; ++i) {
        skiplist->Insert(i);
    }
    uint32_t size = skiplist->Size();
    printf("size :%d\n", size);
    return 0;
}