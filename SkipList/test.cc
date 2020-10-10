#include "test.h"

inline uint64_t TimeOfMicros() {
    struct timeval tv;
    gettimeofday(&tv, nullptr);
    return static_cast<uint64_t>(tv.tv_sec) * 1000000 + tv.tv_usec;
}

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

void SearchTimeCompare(uint32_t search_times) {
    SkipList *skiplist = new SkipList();
    SingleList *singlelist = new SingleList();

    for(int i = 0; i < 1000; ++i) {
        int32_t insert_t = rand() % 10000;
        skiplist->Insert(insert_t);
        singlelist->Insert(insert_t);
    }

    std::vector<int32_t> test;
    while(search_times--) {
        test.push_back(rand() % 10000);
    }

    uint64_t skiplist_start_time = TimeOfMicros();
    for(auto iter = test.begin(); iter != test.end(); ++iter){
        auto ret = skiplist->Find(*iter);
        if(ret) assert(ret->data == *iter);
    }
    uint64_t skiplist_end_time = TimeOfMicros();

    uint64_t singlelist_start_time = TimeOfMicros();
    for(auto iter = test.begin(); iter != test.end(); ++iter){
        auto ret = singlelist->Find(*iter);
        if(ret) assert(ret->data == *iter);
    }
    uint64_t singlelist_end_time = TimeOfMicros();

    printf("TIMEPASSED:\nSKIPLIST:%.4lf s\nSINGLELIST:%.4lf s\n",
                double(skiplist_end_time-skiplist_start_time) / 1000000,
                double(singlelist_end_time-singlelist_start_time) / 1000000);
    
    delete skiplist;
    delete singlelist; 

}