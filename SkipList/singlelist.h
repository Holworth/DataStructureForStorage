#ifndef SINGLELIST_H_
#define SINGLELIST_H_
#include <stdint.h>
class SingleList {
    enum InsertRetType { InsertSucc, DataExists }; 
    enum DeleteRetType { DeleteSucc, DataNotExist }; 
    struct SingleListNode { 
        int32_t data;
        SingleListNode *next;

        SingleListNode(int32_t data):data(data), next(nullptr) {}
    };

    private:
        SingleListNode *head;

    public:
        SingleList();
        ~SingleList();
    
    public:
        InsertRetType  Insert(const int32_t &data);
        DeleteRetType  Delete(const int32_t &data);
        SingleListNode *Find(const int32_t &data);
        
};

#endif