#ifndef _Tree_HPP_
#define _Tree_HPP_

#include <list>
#include <time.h>

#include "GNode.hpp"
#include "LDisk.hpp"
using namespace std;

class Tree{
    public:

        //initialize the tree
        Tree(int bs,int b, int ds){
          //set up the initial variables
          blockSize = bs;
          numBlocks = b;
          diskSize = ds;
          time_t tempTime = time(NULL)
          time = (int)(time(&tempTime));
          root = new GNode("/",time,16,NULL);
          disk = new LDisk(b);
          currentDir = root;
        }

        //FOR YOUR DIRECTORIES AND FILES
        void addNode(int size,string name){
          updateTime();
          GNode * newNode = new GNode(name,time,size,currentDir);
          currentDir -> children.push_back(newNode);
        }
        //FOR YOUR DEBUGGING
    //    void prePrint()
        // METHODS FOR THE SHELL

        void cd(string name){
          bool flag = true;
          list<GNode*>::iterator it = currentDir -> children.begin();
          while(it != currentDir -> children.end() && flag == true){
            if(*it -> name == name)
              flag = false;
            it++;
          }
          if(*it == NULL){
            cout << "cannot change directory, couldn't find directory" << endl;
            return;
          }
          if(*it -> file == NULL){
            currentDir = *it;
          } else {
            cout << "cannot change directory to a file" << endl;
          }
        }


        void cdOut() {
          if(currentDir -> parent != NULL){
            currentDir = parent;
          } else {
            cout << "cannot change directory file has no parent" << endl;
          }
        }


        void ls(){
          for(list<GNode*>::iterator it = currentDir -> children.begin(); it != currentDir -> children.end(); ++it){
            cout << *it -> name << ' ';
          }
        }


        void mkdir(string name){
          updateTime();
          GNode * temp = new GNode(name,time,16,currentDir);
          currentDir -> children.push_back(temp);
        }


        void create(string name){
          updateTime();
          //create the file
          LDisk * tempDisk = new LDisk(diskSize/blockSize);
          LFile * tempFile = new LFile(0,blockSize,tempDisk);
          GNode * tempNode = new GNode(name, time, 0, currentDir);
          //push it back
          currentDir -> children.push_back(tempNode);
        }


        void append(string name, int bytes){
          bool flag = true;
          updateTime();
          list<GNode*>::iterator it = currentDir -> children.begin();
          while(it != currentDir -> children.end() && flag == true){
            if(*it -> name == name)
              flag = false;
            it++;
          }
          if(*it == NULL){
            cout << "cannot append, couldn't find file" << endl;
            return;
          }
          *it -> timeStamp = time;
          *it -> file -> append(bytes);
        }


        void remove(string name,int bytes){
          bool flag = true;
          updateTime();
          list<GNode*>::iterator it = currentDir -> children.begin();
          while(it != currentDir -> children.end() && flag == true){
            if(*it -> name == name)
              flag = false;
            it++;
          }
          if(*it == NULL){
            cout << "cannot append, couldn't find file" << endl;
            return;
          }
          *it -> timeStamp = time;
          *it -> file -> remove(bytes);
        }


        void deleteNode(string name){
          int pos = lookUp(name);
          list<GNode*>::iterator it = currentDir -> children.begin();
          if(pos = -1){
            cout << "could not find node" << endl;
            return;
          }
          advance(it,pos);
          if(*it -> file == NULL){
            deleteHelper(*it);
          } else {
            deleteFile(*it);
          }
        }
        void dir();
        void printDisk();
        void printFiles();
        // CLEANUP
        ~Tree();
    private:
        GNode * root;
        LDisk * disk;
        // USE currentDir as a handle
        GNode * currentDir;
        int numBlocks;
        int blockSize;
        int diskSize;
        void pFile(GNode * dir);
        int lookUp(string name){
          bool flag = true;
          list<GNode*>::iterator it = currentDir -> children.begin();
          while(it != currentDir -> children.end() && flag == true){
            if(*it -> name == name)
              flag = false;
            it++;
          }
          if(*it == NULL)
            return -1;
          return distance(currentDir -> children.begin(), it);
        }
        void updateTime(){
          time_t tempTime = time(NULL)
          time = (int)(time(&tempTime));
        }
        void step(string name);
        void deleteHelper(GNode * tmp){
          if(tmp -> children.empty()){
            currentDir -> children -> remove(tmp);
          }
          else {
            cout << "could not delete directory because it is not empty" << endl;
          }
        }
        void deleteFile(GNode * f){

        }
        int time;
};

#endif
