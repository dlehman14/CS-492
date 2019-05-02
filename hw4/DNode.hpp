

//David Lehman and Thomas Kautzmann
#ifndef _DNODE_HPP_
#define _DNODE_HPP_

#include <cstdio>

struct DNode{
    DNode(int s, int l, int u){
        start=s;
        end=l;
        next=NULL;
        prev = NULL;
        usedBit=u;
    }
    int usedBit;
    int start;
    int end;
    DNode* next;
    DNode* prev;
};

#endif
