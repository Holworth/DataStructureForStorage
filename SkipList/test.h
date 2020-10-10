#ifndef TEST_H_
#define TEST_H_
#include <sys/time.h>
#include "skiplist.h"
#include "singlelist.h"
//get time
inline uint64_t TimeOfMicros();
void test_possibility(uint32_t test_times);
void skiplist_simple_test();
void singlelist_simple_test();
void SearchTimeCompare(uint32_t search_times=10000);

#endif