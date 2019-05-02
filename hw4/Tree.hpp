#ifndef _Tree_HPP_
#define _Tree_HPP_

#include <list>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <time.h>
#include <unistd.h>

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
          disk = new LDisk(ds/bs);
          currentDir = root;
        }

        //FOR YOUR DIRECTORIES AND FILES
        void addNode(int size,string name){
            /*
          updateTime();
          GNode * newNode = new GNode(name,tim,size,currentDir);
          currentDir -> children.push_back(newNode);
          */
            if(size<0){
                mkdir(name);
            }
            else{
                create(name);
                append(name,size);
            }
        }
        //FOR YOUR DEBUGGING
    //    void prePrint()
        // METHODS FOR THE SHELL

        void cd(string name){
          bool flag = false;
          GNode * temp = currentDir;
          for(const auto& GNode : currentDir->children)
          {
          //  usleep(1);
            if(GNode->name.compare(name)==0)
            {
              temp = GNode;
              flag = true;
              break;
            }
          }

          if(flag == false){
            cout << "cannot change directory, couldn't find directory" << endl;
            return;
          }
          if(temp->file==NULL)
            currentDir = temp;
          else
            cout << "cannot change directory to a file"<<endl;
          return;
          /*
          if(*it == NULL){
            cout << "cannot change directory, couldn't find directory" << endl;
            return;
          }
          if((*it) -> file == NULL){
            currentDir = *it;
          } else {
            cout << "cannot change directory to a file" << endl;
          }
          */

        }


        void cdOut() {
          if(currentDir -> parent != NULL){
            currentDir = currentDir -> parent;
          } else {
            cout << "cannot change directory file has no parent" << endl;
          }
        }


        void ls(){
          for(const auto& GNode : currentDir->children)
          {
            cout << GNode->name << '\t';
          }
          cout << endl;
        }


        void mkdir(string name){
            if(!name.empty()){
          updateTime();
          GNode * temp = new GNode(name,tim,16,currentDir);
          currentDir -> children.push_back(temp);
        }
        }


        void create(string name){
          updateTime();
          //create the file
          LFile * tempFile = new LFile(0,blockSize,disk);
          usleep(1);
          GNode * tempNode = new GNode(name, tim, 0, currentDir);
          tempNode -> file = tempFile;
          //push it back
          currentDir -> children.push_back(tempNode);
        }


        void append(string name, int bytes){
          updateTime();
          bool flag = false;
          GNode * temp = currentDir;
          for(const auto& GNode : currentDir->children)
          {
            if(GNode->name.compare(name)==0)
            {
              temp = GNode;
              flag = true;
              break;
            }
          }

          if(flag == false){
            cout << "cannot append, couldn't find file" << endl;
            return;
          }

          temp -> timeStamp = tim;
          temp -> file -> append(bytes);
          disk = temp -> file -> getDisk();
          /*
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
          */
        }


        void remove(string name,int bytes){
          updateTime();
          bool flag = false;
          GNode * temp = currentDir;
          for(const auto& GNode : currentDir->children)
          {
            if(GNode->name.compare(name)==0)
            {
              temp = GNode;
              flag = true;
              break;
            }
          }

          if(flag == false){
            cout << "cannot remove, couldn't find file" << endl;
            return;
          }
          temp -> timeStamp = tim;
          temp -> file -> remove(bytes);
          disk = temp -> file -> getDisk();
          /*
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
          */
        }


        void deleteNode(string name){
          int pos = lookUp(name);
          bool flag = false;
          GNode * temp = currentDir;
          for(const auto& GNode : currentDir->children)
          {
            if(GNode->name.compare(name)==0)
            {
              temp = GNode;
              flag = true;
              break;
            }
          }

          if(flag == false){
            cout << "cannot delete Node, couldn't find Node" << endl;
            return;
          }
          if(temp -> file == NULL){
            deleteHelper(temp);
          } else {
            deleteFile(temp);
          }
        }

        void dir(){
        cout << root -> name << endl;
          pFile(currentDir);
          cout << endl;
        }

        void printDisk(){
          cout << "Printing disk" << endl;
          disk -> print();
        }

        void printFiles(){
          cout << "Printing files for " << currentDir -> name << ": " << endl;

          for(const auto& GNode : currentDir->children)
          {
            if(GNode -> file != NULL){
              cout << "For " << GNode -> name << endl;
              //cout << "Total size: " << GNode -> file -> getSize() << " Bytes" << endl;
              GNode -> file -> print();
            }
          }
          cout << endl;
          /*
          for(list<GNode*>::iterator it = currentDir -> children.begin(); it != currentDir -> children.end(); ++it){
            if((*it) -> file != NULL){
              (*it) -> file -> print();
            }
          }
          */
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
        GNode * temp;
        // USE currentDir as a handle
        GNode * currentDir;
        int numBlocks;
        int blockSize;
        int diskSize;
        void pFile(GNode * dir){
          if(dir -> children.empty())
            return;
        list <GNode*> temp;
          for(const auto& GNode : dir->children)
          {
            cout << GNode -> name << '\t';
            if(GNode->file==NULL)
                temp.push_back(GNode);
          }
          cout << endl;
          for(const auto& GNod : temp){
            pFile(GNod);
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
        //Deconstructor
        void deleteFullDir(GNode * dir){
            if(dir->children.empty()){
                delete dir;
                return;
            }
          for(const auto& GNode : currentDir->children)
          {
            if(GNode -> file != NULL)
              delete GNode;
            else {
              if(GNode -> children.empty())
                delete GNode;
              else {
                //deleteFullDir(GNode);
                delete GNode;
              }
            }
          }
        }
};

#endif
