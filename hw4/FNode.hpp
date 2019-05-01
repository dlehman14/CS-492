#ifndef _FNode_HPP_
#define _FNode_HPP_
#include <cstdio>

struct FNode{
    int blockAddress;
    FNode* next;
    FNode * prev;
    LDisk * disk;

    FNode(LDisk * disk)
    {
        blockAddress = -1;
        next = NULL;
        disk = disk;
    }

    FNode(int m, FNode* n, FNode* p, LDisk * d)
    {
        blockAddress = m;
        next = n;
        disk = d;
        prev = p;
    }
};


#endif
