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

bool SkipList::Empty() const {
    assert(list_[kMaxLevel] != nullptr);
    return (list_[kMaxLevel]->size == 0);
}

size_t SkipList::Size() const {
    assert(list_[kMaxLevel] != nullptr);
    return list_[kMaxLevel] -> size;
}

SkipList::SkipList() {
    for(size_t i = 0; i <= kMaxLevel; ++i){
        list_[i] = new SkipListNode(INT32_MIN, header);
        list_[i]->next = new SkipListNode(INT32_MAX, tail);
    }

    for(size_t i = kMaxLevel; i >= 2; --i) {
        list_[i]->below = list_[i-1];
    }
}

// search one element on a specific level
SkipList::SkipListNode *SkipList::BinarySearchHelper(uint32_t search_level, int32_t data) {
    uint32_t clevel = kMaxLevel;
    SkipListNode *prev = list_[clevel], *cur = list_[clevel];
    while(clevel <= search_level) {
        if (cur->next->type == tail) {
            prev = cur;
            continue;
        }
        if(cur->next->type == node){
            prev = cur;
            cur = cur->next;
        }
        while(cur->data < data) {
            prev = cur;
            prev = prev->next;
        }
        if(clevel == search_level) return prev;
        else {
           cur = prev->below;
           prev = prev->below; 
        }
        ++clevel;
    }
    return prev;
}

bool SkipList::Insert(const int32_t data) {
    uint32_t insert_level = get_random_level();
    
    // insert one element in the chosen level
    SkipListNode* insert_prev = BinarySearchHelper(insert_level, data);
    if(insert_prev->next->type == node && insert_prev->next->data == data) {
        printf("element is already in!\n");
        return false;
    } 
    SkipListNode *new_node = new SkipListNode(data, node);
    new_node->next = insert_prev->next;
    insert_prev->next = new_node;
    // next level;
    uint32_t clevel = insert_level + 1;
    SkipListNode *cur = insert_prev->below, 
                 *prev = insert_prev->below;
    while(clevel <= kMaxLevel) {
        assert(cur != nullptr);
        while(cur->type == node && cur->data < data) {
            prev = cur;
            cur  = cur->next;
        }
        SkipListNode *new_node = new SkipListNode(data, node);
        new_node->next = insert_prev->next;
        insert_prev->next = new_node;

        ++clevel; 
        cur = prev->below;
        prev = prev->below;
    }
}

/*
int main() {
    test_possibility(1000);
    return 0;
*/