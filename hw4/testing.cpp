

//David Lehman and Thomas Kautzmann
#include <iostream>
#include "LDisk.hpp"
#include "LFile.hpp"
#include "Tree.hpp"
#include "GNode.hpp"
#include <time.h>
using namespace std;

int main() {
  LDisk testDisk(32);
  cout << testDisk.totalBlocks << endl;
  cout << testDisk.maxBlocks << endl;
  testDisk.insert(0,2,1);
  cout << testDisk.totalBlocks << endl;
  testDisk.insert(3,7,0);
  testDisk.insert(8,9,1);
  cout << testDisk.totalBlocks << endl;
  cout << testDisk.totalNodes << endl;
  testDisk.deleteDisk();
  testDisk.print();
  testDisk.update();
  testDisk.print();


  LDisk * tDisk = new LDisk(16);
  LFile * testFile = new LFile(2048, 32, tDisk);
  GNode * testNode = new GNode("test",512,32,NULL);
  testFile -> print();
  cout << endl;
  testFile -> append(2048);
  testFile -> print();
  testFile -> remove(2048);
  testFile -> print();


int numBlocks=32;
int blockSize=16;
Tree * test = new Tree(blockSize,numBlocks,512);

test -> addNode(16, "testNode");

test -> create("testyboi");

test -> mkdir("testDir");
cout <<"testing ls: expected: testyboi testDir" << endl;
test -> ls();

test -> cd("testDir");
cout << "moved into new dir ls should print nothing"<<endl;
test -> ls();
test -> mkdir("test2");
cout << "ls should print: test2" << endl;
test -> ls();
test -> cdOut();
test -> mkdir("test3");
cout <<"ls should print testyboi testDir" << endl;
test -> ls();
cout << "testing if deletion of a nonempty dir is allowed" << endl;
test -> deleteNode("testDir");
test -> deleteNode("test3");
test -> ls();
cout << "testing the dir function" << endl;
test -> dir();
cout << "testing the printDisk function" << endl;
test -> printDisk();
cout << "testing the printFiles function" << endl;
test -> ls();
test -> printFiles();
test -> printDisk();
cout << "testing the append function. testyboi should have 32 bytes" << endl;
test -> append("testyboi",16);
test -> printFiles();
test -> printDisk();
cout << "testing the remove function. testyboi should have 2 bytes now." << endl;
test -> remove("testyboi",30);
cout << "Hello" << endl;




}
