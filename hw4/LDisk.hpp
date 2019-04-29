#ifndef _LDisk_HPP_
#define _LDisk_HPP_

#include <iostream>
#include "DNode.hpp"

class LDisk{
    public:
        LDisk(int blocks);
        int insert();
        void remove(int blockAddress);
        void update();
        void print(int blockSize);
        int totalBlocks;
        ~LDisk();
    private:
        DNode * head;
};


#endif
