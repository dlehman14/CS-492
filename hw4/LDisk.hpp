

//David Lehman and Thomas Kautzmann
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
        LDisk(int blocks) {
          maxBlocks = blocks;
          head = NULL;
          totalBlocks = 0;
        }
        // inserts a file into the disk
        int insert(int s, int e, int u) { // working
          if(e < s){
            cout << "invalid input parameters for insert" << endl;
            exit(EXIT_FAILURE);
          }
          if(head == NULL){ //for empty list
            DNode * temp = new DNode(s,e,u);
            totalNodes++;
            temp -> next = NULL;
            temp -> prev = NULL;
            head = temp;
            tail = temp;
            totalBlocks = totalBlocks + (e-s) + 1;
            return e;
          } else if(totalBlocks < maxBlocks){ //for a sizeable list
            DNode * temp = new DNode(s,e,u);
            totalNodes++;
            temp -> prev = tail;
            temp -> next = NULL;
            tail -> next = temp;
            tail = temp;
            totalBlocks = totalBlocks + (e-s) + 1;
            return e;
          } else { //for a too big list
            cout << "could not insert disk, bigger than the maxBlocks" << endl;
            exit(EXIT_FAILURE);
          }
        }

        //returns the blocks remaining
        int getBlocksLeft(){
          return maxBlocks - totalBlocks;
        }

        //checks if the disk is full
        bool isFull(){
          if(totalBlocks >= maxBlocks)
            return true;
          return false;
        }

        //removes something from the disk
        void remove(int blockAddress){
          if(blockAddress > tail -> end || blockAddress < 0){
            cout << "could not delete disk, out of bounds" << endl;
            exit(EXIT_FAILURE);
          }
          if(totalNodes <= 0){
            cout << "could not delete, empty disk" << endl;
            exit(EXIT_FAILURE);
          }
          if(totalNodes == 1){
            head = NULL;
            tail = NULL;
            delete head;
            totalBlocks = 0;
            totalNodes = 0;
            return;
          }
          totalNodes--;
          DNode * temp = head;
          bool flag = false;
          while(temp != NULL && flag == false){
            if(temp -> start <= blockAddress && temp -> end >= blockAddress){
              flag = true;
            } else {
              temp = temp -> next;
            }
          }
          if(temp == head){
            head = temp -> next;
            head -> prev = NULL;
            delete temp;
            return;
          }
          if(temp == tail){
            tail = temp -> prev;
            tail -> next = NULL;
            delete temp;
            return;
          }
          temp -> prev -> next = temp -> next;
          temp -> next -> prev = temp -> prev;
          delete temp;
        }

        //wipes the disk clean
        void deleteDisk(){
          if(head == NULL)
            return;
          update();
          DNode * temp = head;
          head = NULL;
          tail = NULL;
          delete temp;
          totalBlocks = 0;
          totalNodes = 0;
          return;
        }
        //updates the disk
        void update() { //working
          if(head == NULL)
            return;
          int min = 0;
          int max = 0;
          DNode * trav = head;
          totalNodes = 1;
          while(trav != NULL){
            if(trav -> end > max && trav -> usedBit == 1)
              max = trav -> end;
            DNode * temp = trav;
            trav = trav -> next;
            delete temp;
          }
          DNode * newHead = new DNode(min,max,1);
          head = tail = newHead;
          postUpdateEnd = max;
          totalBlocks = max;
          return;
        }
        //prints the disk
        void print(){ // Working
          DNode * trav;
          for(trav = head; trav != NULL; trav = trav -> next){
            cout << "Start: " << trav -> start << " \tEnd: " << trav -> end << " \tUsed: " << trav -> usedBit << "\n";
          }
        }
        int totalBlocks;
        int maxBlocks;
        int postUpdateEnd;
        int totalNodes;
        //deconstructor
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
