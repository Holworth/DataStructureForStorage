#include "skiplist.h"
#include "test.h"

//get true or false both in 0.5 possibility
static inline bool flip_coin() {
    int result = rand() % 2;
    if(result % 2) return true;
    else return false;
}
// generate random level in 2^(-n) possibility
static uint32_t get_random_level() {
    uint32_t result = 1;
    while(flip_coin()) ++result;
    return result;
}
void test_possibility(uint32_t test_times) {
    double poss[11];
    uint32_t total_times = test_times;
    while(test_times--) {
        uint32_t res = get_random_level();
        if(res > 10) {
            total_times--;
            continue;
        }
        ++poss[res];
    }
    for(size_t i = 0;i < 10; ++i) {
        printf("%.6lf\n", (double)poss[i] / total_times);
    }
}

int main() {
    test_possibility(1000);
    return 0;
}
