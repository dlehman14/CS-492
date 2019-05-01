#include <iostream>
#include "LDisk.hpp"
#include "LFile.hpp"
#include "Tree.hpp"
#include <time.h>
using namespace std;

int main() {
/*
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



  LDisk * testDisk = new LDisk(16);
  LFile * testFile = new LFile(2048, 32, testDisk);
  testFile -> print();
  cout << endl;
  testFile -> append(2048);
  testFile -> print();
  testFile -> remove(2048);
  testFile -> print();
*/
  time_t myTime = time(NULL);
  int toTime = (int)(time(&myTime));
  cout << time(&myTime) << endl;
  cout << toTime << endl;
}
