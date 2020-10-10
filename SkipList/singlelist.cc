#include "singlelist.h"

SingleList::SingleList() {
    head = new SingleListNode(INT32_MIN);
}
SingleList::~SingleList() {
    SingleListNode *prev = head, *cur = head->next;
    while(cur) {
        delete prev;
        prev = cur;
        cur = cur->next;
    }
    delete prev;
}

SingleList::InsertRetType SingleList::Insert(const int32_t &data) {
    SingleListNode *prev = head;
    while(prev->next && prev->next->data < data)
        prev = prev->next;
    if(prev->next && prev->next->data == data)
        return DataExists;
    SingleListNode *new_node = new SingleListNode(data);
    new_node->next = prev->next;
    prev->next = new_node;
    return InsertSucc;
}

SingleList::SingleListNode* SingleList::Find(const int32_t &data) {
    auto iter = head->next;
    for(; iter && iter->data != data; iter=iter->next) 
        ;
    if (iter && iter->data == data) return iter;
    else return nullptr;
}

SingleList::DeleteRetType SingleList::Delete(const int32_t &data){
    SingleListNode *prev = head, *cur=head->next;
    while(cur && cur->data != data) {
        prev = cur;
        cur = cur->next;
    }
    if(cur && cur->data == data) {
        prev->next = cur->next;
        delete cur;
        return DeleteSucc;
    } else return DataNotExist;
}
