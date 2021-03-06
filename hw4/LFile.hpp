

//David Lehman and Thomas Kautzmann
#ifndef _LFILE_HPP_
#define _LFILE_HPP_

#include "FNode.hpp"
#include "LDisk.hpp"
#include <list>
#include <time.h>
#include <unistd.h>
using namespace std;

class LFile
{
    public:
      //constructs a file
        LFile(int ts, int bs,LDisk * d) : totalSize(ts), blockSize(bs), disk(d) { // working
          disk = d;
          diskSize = disk -> maxBlocks;
          disk -> update();
          bool firstPass = true;
          int blocksLeft = ts/bs;
          if(disk -> isFull() == true){
            LDisk * nDisk = new LDisk(diskSize);
            disk = nDisk;
          }

          if(blocksLeft == 0){
            FNode * temp = new FNode(disk -> totalBlocks,NULL, NULL, disk);
            start = temp;
            tail = temp;
            disk -> insert(disk -> totalBlocks, disk -> totalBlocks + 1, 1);
          }

          while(blocksLeft > 0){
            if(blocksLeft > disk -> getBlocksLeft()){
              if (firstPass == true){
                FNode * temp = new FNode(disk -> totalBlocks, NULL, NULL, disk);
                start = temp;
                tail = temp;
              } else {
                FNode * temp = new FNode(disk -> totalBlocks, NULL, tail, disk);
                tail -> next = temp;
                tail = temp;
              }
              blocksLeft = blocksLeft - disk -> getBlocksLeft();
              disk -> insert(disk -> totalBlocks,disk -> maxBlocks - 1,1);
              LDisk * nDisk = new LDisk(diskSize);
              disk = nDisk;
              firstPass = false;
            } else if (blocksLeft == disk -> getBlocksLeft()) {
              if (firstPass == true){
                FNode * temp = new FNode(disk -> totalBlocks, NULL, NULL, disk);
                start = temp;
                tail = temp;
              } else {
                FNode * temp = new FNode(disk -> totalBlocks, NULL, tail, disk);
                tail -> next = temp;
                tail = temp;
              }
              blocksLeft = 0;
              disk -> insert(disk -> totalBlocks,disk -> maxBlocks - 1,1);
              LDisk * nDisk = new LDisk(diskSize);
              disk = nDisk;
              firstPass = false;
            } else {
              if (firstPass == true){
                FNode * temp = new FNode(disk -> totalBlocks, NULL, NULL, disk);
                start = temp;
                tail = temp;
              } else {
                FNode * temp = new FNode(disk -> totalBlocks, NULL, tail, disk);
                tail -> next = temp;
                tail = temp;
              }
              disk -> insert(disk -> totalBlocks,disk -> totalBlocks + blocksLeft, 1);
              blocksLeft = 0;
              firstPass = false;
            }
          }
        }

        //appends bytes to a file
        void append(int numBytes){ // working
          disk -> update();
          totalSize = totalSize + numBytes;
          int blocksLeft = numBytes/blockSize;
          while(blocksLeft > 0){
            if(blocksLeft > disk -> getBlocksLeft()){
              if (start == NULL){
                FNode * temp = new FNode(disk -> totalBlocks, NULL, NULL, disk);
                start = temp;
                tail = temp;
              } else {
                FNode * temp = new FNode(disk -> totalBlocks, NULL, tail, disk);
                tail -> next = temp;
                tail = temp;
              }
              blocksLeft = blocksLeft - disk -> getBlocksLeft();
              disk -> insert(disk -> totalBlocks,disk -> maxBlocks-1,1);
              LDisk * nDisk = new LDisk(diskSize);
              disk = nDisk;
            } else if (blocksLeft == disk -> getBlocksLeft()) {
              if (start == NULL){
                FNode * temp = new FNode(disk -> totalBlocks, NULL, NULL, disk);
                start = temp;
                tail = temp;
              } else {
                FNode * temp = new FNode(disk -> totalBlocks, NULL, tail, disk);
                tail -> next = temp;
                tail = temp;
              }
              blocksLeft = 0;
              disk -> insert(disk -> totalBlocks,disk -> maxBlocks - 1,1);
              LDisk * nDisk = new LDisk(diskSize);
              disk = nDisk;
            } else {
              if (start == NULL){
                FNode * temp = new FNode(disk -> totalBlocks, NULL, NULL, disk);
                start = temp;
                tail = temp;
              } else {
                FNode * temp = new FNode(disk -> totalBlocks, NULL, tail, disk);
                tail -> next = temp;
                tail = temp;
              }
              disk -> insert(disk -> totalBlocks,disk -> totalBlocks + blocksLeft, 1);
              blocksLeft = 0;
            }
          }
        }

        //removes bytes from a file
        void remove(int numBytes){ //testing
          //Setup the disk and check if we need to delete the file
          disk -> update();
          totalSize = totalSize - numBytes;
          if(totalSize <= 0){
            totalSize = 0;
            FNode * trav = tail;
            while(trav != NULL){
              FNode * temp = trav;
              trav = trav -> prev;
              temp -> disk -> deleteDisk();
              delete temp;
            }
            start = NULL;
            tail = NULL;
            return;
          }
          int blocksLeft = numBytes/blockSize;
          //if need to delete end, shave off end
          while(blocksLeft > 0){
            if(blocksLeft > disk -> totalBlocks){
              blocksLeft = blocksLeft - disk -> totalBlocks;
              FNode * temp = tail;
              temp -> disk -> deleteDisk();
              tail = tail -> prev;
              tail -> next = NULL;
              delete temp;
              disk = tail -> disk;
            } else if (blocksLeft == disk -> totalBlocks) {
              FNode * temp = tail;
              temp -> disk -> deleteDisk();
              tail = tail -> prev;
              tail -> next = NULL;
              delete temp;
              disk = tail -> disk;
              blocksLeft = 0;
            } else {
              int leftover = disk -> totalBlocks - blocksLeft - 1;
              disk -> deleteDisk();
              disk -> insert(0,leftover,1);
              tail -> blockAddress = 0;
              blocksLeft = 0;
            }
          }
        }

        //printes a file
        void print(){
          int i = 0;
          FNode * trav;
          if(start == NULL)
            return;
          for(trav = start; trav != NULL; trav = trav -> next){
            if(trav -> blockAddress >= 2147483647){
              cout << "could not print pointer for disk : " << i << ", number to big" << endl;
              i++;
            } else {
            cout << "Disk: " << i << "\tpointer: " << trav -> blockAddress << endl;
            i++;
          }
          }
        }
        //retruns the size of a file
        int getSize(){
          return totalSize;
        }
        //Deconstructor
        ~LFile(){
          FNode * trav = start;
          while(trav != NULL){
            FNode * temp = trav;
            trav = trav -> next;
            delete temp;
          }
          start = NULL;
          tail = NULL;
        }

        LDisk* getDisk(){
          return disk;
        }

    private:
        FNode* start;
        FNode* tail;
        int diskSize;
        int totalSize;
        int blockSize;
        LDisk * disk;

};

#endif
