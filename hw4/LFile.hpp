#ifndef _LFILE_HPP_
#define _LFILE_HPP_

#include "FNode.hpp"
#include "LDisk.hpp"

class LFile
{
    public:
        LFile(int ts, int bs,LDisk * d);
        void append(int numBytes);
        void remove(int numBytes);
        void print();
        int getSize();
        ~LFile();
    private:
        FNode* start;
        int totalSize;
        int blockSize;
        LDisk * disk;

};

#endif
