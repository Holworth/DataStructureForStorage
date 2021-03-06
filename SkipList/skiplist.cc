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
    assert(list_[kBaseLevel] != nullptr);
    return list_[kBaseLevel] -> size;
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

bool SkipList::distroyList() {
    for(size_t idx = kBaseLevel; idx <= kMaxLevel; ++idx) {
        SkipListNode *cur = list_[idx]->next, *last = list_[idx];
        while(cur->type != tail) {
            last = cur; 
            cur = cur->next;
            delete last;
        }
    }
    return true;
}

SkipList::~SkipList() {
    distroyList();
    for(size_t idx = kBaseLevel; idx <= kMaxLevel; ++idx){
        assert(list_[idx]->next && list_[idx]->next->type == tail);
        delete (list_[idx]->next);
        delete (list_[idx]);
    }
}

// search one element on a specific level
SkipList::SkipListNode *SkipList::BinarySearchHelper(uint32_t search_level, const int32_t &data) {
    uint32_t clevel = kMaxLevel;
    SkipListNode *prev = list_[clevel], *cur = list_[clevel];
    while(clevel >= search_level) {
        if (cur->next->type == tail) {
            prev = cur;
            goto update;
        } else if(cur->next->type == node){
            prev = cur;
            cur = cur->next;
        }

        while(cur->data < data) {
            prev = cur;
            cur = cur->next;
        }

        update:
            if(clevel == search_level) return prev;
            else {
            cur = prev->below;
            prev = prev->below; 
            }
            --clevel;
    }
    return prev;
}

SkipList::InsertRetType SkipList::Insert(const int32_t &data) {

    uint32_t insert_level; 
    uint32_t levelExceedTimes = 0;
    // get insert level must less than 5
    while((insert_level = get_random_level()) > kMaxLevel){
        levelExceedTimes++;
        if(levelExceedTimes > levelExceedLimit) 
            return FalseInsertLevel;
    }
                
    // insert one element in the chosen level
    SkipListNode* insert_prev = BinarySearchHelper(insert_level, data);
    if(insert_prev->next->type == node && insert_prev->next->data == data) {
        printf("element is already in!\n");
        return DataExists;
    } 
    SkipListNode *new_node = new SkipListNode(data, node);
    new_node->next = insert_prev->next;
    insert_prev->next = new_node;
    (list_[insert_level]->size)++;
    // next level;
    uint32_t clevel = insert_level - 1;
    SkipListNode *cur = insert_prev->below, 
                 *prev = insert_prev->below;
    SkipListNode *last_level_new = new_node;

    while(clevel >= kBaseLevel) {
        assert(cur != nullptr);
        if(cur->next->type == node) {
            prev = cur;
            cur = cur->next;
        }
        while(cur->type == node && cur->data < data) {
            prev = cur;
            cur  = cur->next;
        }
        new_node = new SkipListNode(data, node);
        //update below pointer;
        last_level_new->below = new_node;
        last_level_new = new_node;
        // insert element
        new_node->next = prev->next;
        prev->next = new_node;
        // update size for each level
        (list_[clevel]->size)++;

        --clevel; 
        cur = prev->below;
        prev = prev->below;
    }
    return InsertSucc;
}

SkipList::SkipListNode *SkipList::Find(const int32_t &data){
    SkipListNode *prev = BinarySearchHelper(kBaseLevel, data);
    assert(prev != nullptr);
    // find one
    if(prev->next->type == node && prev->next->data == data) {
        return prev->next;
    } else {
        // no match data
        return nullptr;
    }
}


void SkipList::PrintList() const {
    for(size_t idx = kMaxLevel; idx >= kBaseLevel; --idx) {
        printf("Level %d:", idx);
        for(SkipListNode *cur = list_[idx]->next; cur->type != tail; 
                                        cur = cur->next){   
                printf("%d->", cur->data);
        }
        printf("\n");
    }
}

SkipList::DeleteRetType SkipList::Delete(const int32_t &data) {

    uint32_t clevel = kMaxLevel;
    uint32_t deltimes = 0;
    SkipListNode *prev = list_[clevel], *cur = list_[clevel]->next;
    while(clevel >= kBaseLevel) {
        while(cur->type == node && cur->data < data) {
            prev = cur;
            cur  = cur->next;
        }
        if (cur->type == node && cur->data == data) {
            prev->next = cur->next;
            delete cur;
            ++deltimes;
        }
        if(clevel > 1) {
            prev = prev->below;
            cur  = prev->next;
        }
        --clevel;
    }
    if(deltimes > 0) return DeleteSucc;
    else return DataNotExist;
}