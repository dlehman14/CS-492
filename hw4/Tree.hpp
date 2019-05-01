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
          time_t tempTime = time(NULL);
          tim = (int)(time(&tempTime));
          root = new GNode("/",tim,16,NULL);
          disk = new LDisk(b);
          currentDir = root;
        }

        //FOR YOUR DIRECTORIES AND FILES
        void addNode(int size,string name){
          updateTime();
          GNode * newNode = new GNode(name,tim,size,currentDir);
          currentDir -> children.push_back(newNode);
        }
        //FOR YOUR DEBUGGING
    //    void prePrint()
        // METHODS FOR THE SHELL

        void cd(string name){
          bool flag = true;
          list<GNode*>::iterator it = currentDir -> children.begin();
          while(it != currentDir -> children.end() && flag == true){
            if((*it) -> name == name)
              flag = false;
            it++;
          }
          if(*it == NULL){
            cout << "cannot change directory, couldn't find directory" << endl;
            return;
          }
          if((*it) -> file == NULL){
            currentDir = *it;
          } else {
            cout << "cannot change directory to a file" << endl;
          }
        }


        void cdOut() {
          if(currentDir -> parent != NULL){
            currentDir = currentDir -> parent;
          } else {
            cout << "cannot change directory file has no parent" << endl;
          }
        }


        void ls(){
          for(list<GNode*>::iterator it = currentDir -> children.begin(); it != currentDir -> children.end(); ++it){
            cout << (*it) -> name << ' ';
          }
        }


        void mkdir(string name){
          updateTime();
          GNode * temp = new GNode(name,tim,16,currentDir);
          currentDir -> children.push_back(temp);
        }


        void create(string name){
          updateTime();
          //create the file
          LFile * tempFile = new LFile(0,blockSize,disk);
          GNode * tempNode = new GNode(name, tim, 0, currentDir);
          //push it back
          currentDir -> children.push_back(tempNode);
        }


        void append(string name, int bytes){
          bool flag = true;
          updateTime();
          list<GNode*>::iterator it = currentDir -> children.begin();
          while(it != currentDir -> children.end() && flag == true){
            if((*it) -> name == name)
              flag = false;
            it++;
          }
          if((*it) == NULL){
            cout << "cannot append, couldn't find file" << endl;
            return;
          }
          (*it) -> timeStamp = tim;
          (*it) -> file -> append(bytes);
          disk = (*it) -> file -> getDisk();
        }


        void remove(string name,int bytes){
          bool flag = true;
          updateTime();
          list<GNode*>::iterator it = currentDir -> children.begin();
          while(it != currentDir -> children.end() && flag == true){
            if((*it) -> name == name)
              flag = false;
            it++;
          }
          if((*it) == NULL){
            cout << "cannot append, couldn't find file" << endl;
            return;
          }
          (*it) -> timeStamp = tim;
          (*it) -> file -> remove(bytes);
          disk = (*it) -> file -> getDisk();
        }


        void deleteNode(string name){
          int pos = lookUp(name);
          list<GNode*>::iterator it = currentDir -> children.begin();
          if(pos == -1){
            cout << "could not find node" << endl;
            return;
          }
          advance(it,pos);
          if((*it) -> file == NULL){
            deleteHelper(*it);
          } else {
            deleteFile(*it);
          }
        }
        void dir(){
          pFile(currentDir);
        }
        void printDisk(){
          disk -> print();
        }
        void printFiles(){
          for(list<GNode*>::iterator it = currentDir -> children.begin(); it != currentDir -> children.end(); ++it){
            if((*it) -> file != NULL){
              (*it) -> file -> print();
            }
          }
        }

        // CLEANUP
        ~Tree(){
          deleteFullDir(root);
          delete root;
          root = NULL;
          disk = NULL;
          currentDir = NULL;
        }
    private:
        GNode * root;
        LDisk * disk;
        // USE currentDir as a handle
        GNode * currentDir;
        int numBlocks;
        int blockSize;
        int diskSize;
        void pFile(GNode * dir){
          cout << dir -> name << '\t';
          for(list<GNode*>::iterator it = currentDir -> children.begin(); it != currentDir -> children.end(); ++it){
            pFile(*it);
          }
        }
        int lookUp(string name){
          bool flag = true;
          list<GNode*>::iterator it = currentDir -> children.begin();
          while(it != currentDir -> children.end() && flag == true){
            if((*it) -> name == name)
              flag = false;
            it++;
          }
          if((*it) == NULL)
            return -1;
          return distance(currentDir -> children.begin(), it);
        }
        void updateTime(){
          time_t tempTime = time(NULL);
          tim = (int)(time(&tempTime));
        }
        void deleteHelper(GNode * tmp){
          if(tmp -> children.empty()){
            currentDir -> children.remove(tmp);
          }
          else {
            cout << "could not delete directory because it is not empty" << endl;
          }
        }
        void deleteFile(GNode * f){
          currentDir -> children.remove(f);
        }
        int tim;
        void deleteFullDir(GNode * dir){
          for(list<GNode*>::iterator it = currentDir -> children.begin(); it != currentDir -> children.end(); ++it){
            if((*it) -> file != NULL){
              delete *it;
            } else {
              if((*it) -> children.empty()){
                delete *it;
              } else {
                deleteFullDir(*it);
              }
            }
          }
        }
};

#endif
