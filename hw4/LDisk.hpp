#ifndef _LDisk_HPP_
#define _LDisk_HPP_

#include <iostream>
#include <list>
#include <time.h>
#include <stdlib.h>
#include "DNode.hpp"
using namespace std;

class LDisk{
    public:
        LDisk(int blocks) : maxBlocks(blocks), head(NULL), totalBlocks(0) {}
        int insert(int s, int e, int u) { // working
          if(head == NULL){ //for empty list
            DNode * temp = new DNode(s,e,u);
            temp -> next = NULL;
            temp -> prev = NULL;
            head = temp;
            tail = temp;
            totalBlocks++;
            return 1;
          } else if(totalBlocks < maxBlocks){ //for a sizeable list
            DNode * temp = new DNode(s,e,u);
            temp -> prev = tail;
            temp -> next = NULL;
            tail -> next = temp;
            tail = temp;
            totalBlocks++;
            return 1;
          } else { //for a too big list
            cout << "could not insert file, bigger than the maxBlocks" << endl;
            exit(EXIT_FAILURE);
          }
        }
        void remove(int blockAddress){ // working
          if(totalBlocks > blockAddress && blockAddress >= 0) {
            if(totalBlocks == 1){ //for a list of size one
              delete head;
              head = NULL;
              tail = NULL;
              totalBlocks--;
              return;
            }
            if(blockAddress == 0){
              DNode * temp = head;
              head = head -> next;
              delete temp;
              totalBlocks--;
              return;
            }
            if(totalBlocks - 1 == blockAddress){ //full list
              DNode * temp = tail;
              tail = temp -> prev;
              delete temp;
              totalBlocks--;
              return;
            } else { //sizeable list
              DNode * trav = head;
              int t = 0;
              while (t < blockAddress){
                trav = trav -> next;
                t++;
              }
              trav -> next -> prev = trav -> prev;
              trav -> prev -> next = trav -> next;
              delete trav;
              totalBlocks--;
              return;
            }
          }
        }
        void update() {
          return;
        } // ask the professor about this tomorrow
        void print(){ // Working
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
        DNode * head;
    private:

        DNode * tail;
};


#endif
