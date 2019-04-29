#ifndef _LDisk_HPP_
#define _LDisk_HPP_

#include <iostream>
#include <list>
#include <time>
#include "DNode.hpp"
using namespace std;

class LDisk{
    public:
        LDisk(int blocks) : maxBlocks(blocks) {
          head = NULL;
          totalBlocks = 0;
        }
        int insert(int start, int end, int usedBit) {
          if(head == NULL){ //for empty list
            DNode temp(start, end, usedBit);
            head = temp;
            tail = temp;
            totalBlocks++;
          } else if(totalBlocks < maxBlocks){ //for a sizeable list
            DNode temp(start, end, usedBit);
            tail -> next = temp;
            tail -> next = temp.prev;
            tail = temp;
            totalBlocks++;
          } else { //for a too big list
            cout << "could not insert file, bigger than the maxBlocks" << endl;
            exit();
          }
        }
        void remove(int blockAddress){
          if(totalBlocks > blockAddress && blockAddress >= 0) {
            if(totalBlocks == 1){ //for a list of size one
              delete head;
              head = NULL;
              tail = NULL;
              totalBlocks--;
            } else if(totalBlocks - 1 == blockAddress){ //full list
              DNode * temp = tail;
              tail = temp -> prev;
              delete temp;
              totalBlocks--;
            } else { //sizeable list
              DNode * trav = head;
              int t = 0;
              while (t < blockAddress){
                trav = trav.next;
                t++;
              }
              trav -> next -> prev = trav -> prev;
              trav -> prev -> next = trav -> next;
              delete trav;
              totalBlocks--;
            }
          }
        }
        void update(); // ask the professor about this tomorrow
        void print(int blockSize){
          DNode * trav;
          for(trav = head; trav != NULL; trav = trav -> next){
            cout << "Start: " << trav -> start << " \tEnd: " << trav -> end << " \tUsed: " << trav -> usedBit << "\n";
          }
        }
        int totalBlocks;
        int maxBlocks;
        ~LDisk(){
          DNode * t1 = head;
          DNode * t2 = head;
          while(t1 != NULL){
            t2 = t1;
            t1 = t1 -> next;
            delete t2;
          }
        }
    private:
        DNode * head;
        DNode * tail;
};


#endif
