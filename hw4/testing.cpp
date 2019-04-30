#include <iostream>
#include "LDisk.hpp"
using namespace std;

int main() {
  LDisk testDisk(32);
  cout << testDisk.totalBlocks << endl;
  cout << testDisk.maxBlocks << endl;
  if(testDisk.head == NULL)
    cout << "Empty List" << endl;
  testDisk.insert(0,45,0);
  cout << testDisk.totalBlocks << endl;
  testDisk.insert(0,46,0);
  testDisk.insert(0,47,0);
  testDisk.print();
  testDisk.remove(0);
  testDisk.remove(1);
  testDisk.print();
  testDisk.remove(0);
}
