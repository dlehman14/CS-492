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
        Tree(int bs,int b){
          //set up the initial variables
          blockSize = bs;
          numBlocks = b;
          time_t tempTime = time(NULL)
          int toTime = (int)(time(&tempTime));
          root = new GNode(" ",toTime,16,NULL);
          disk = new LDisk()
          currentDir = root;
        }
        //FOR YOUR DIRECTORIES AND FILES
        void addNode(int size,string name);
        //FOR YOUR DEBUGGING
        void prePrint();
        // METHODS FOR THE SHELL
        void cd(string name);
        void cdOut();
        void ls();
        void mkdir(string name);
        void create(string name);
        void append(string name, int bytes);
        void remove(string name,int bytes);
        void deleteNode(string name);
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
        void pFile(GNode * dir);
        int lookUp(string name);
        void step(string name);
        void deleteHelper(GNode * tmp);
        void deleteFile(GNode * f);
        int time;
};

#endif
