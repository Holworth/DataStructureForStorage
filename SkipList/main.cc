#include "skiplist.h"
#include "singlelist.h"
#include "test.h"
#define SKIPLIST_SIMPLE_TEST   1
#define SINGLELIST_SIMPLE_TEST 1

int main() {

    #ifdef SKIPLIST_SIMPLE_TEST
    skiplist_simple_test();
    #endif

    #ifdef SINGLELIST_SIMPLE_TEST
    singlelist_simple_test();
    #endif

    return 0;
}