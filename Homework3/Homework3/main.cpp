//
//  main.cpp
//  Homework3
//
//  Created by David Lehman on 4/17/19.
//  Copyright © 2019 David Lehman. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

ifstream a("ptrace.txt");
struct pageTable {
    
};
int FIFO(int p){
	string word;
	int temp=0;
	int pageVar=(512/10)/p;
	int fifoCount=0;
	int memPlace;
	bool flag=false;
    vector<int> list[10];
    while(a >> word){
        if(flag == false) {
            temp = stoi(word);
            flag = true;
        } else {
            memPlace = stoi(word);
            memPlace = memPlace/p;
            if (find(list[temp].begin(), list[temp].end(), memPlace) == list[temp].end()) {
                fifoCount++;
                list[temp].insert(list[temp].begin(),memPlace);
                if(list[temp].size() > pageVar)
                    list[temp].pop_back();
            
            }
         
            flag = false;
        }
    }
	return fifoCount;

}


int main() {
    //Declare the two inputs from the files, and read the files into the data
    int plist[10];
    ifstream f("plist.txt");

    string word;
    int count = 0;
    int temp = 0;
    bool flag = false;
    //Read the plist
    while(f >> word){
        temp = stoi(word);
        if(temp != count){
            plist[count] = temp;
            cout << plist[count] << endl;
            count++;
        }
    }
    count = 0;
    //Go through the ptrace for the FIFO
    cout << "--------------------------------------------------" << endl;
    cout << "Going throug to find how many page faults for FIFO" << endl;
    int memPlace2;
    count=FIFO(4);
    a.close();
    cout << "For size 4: " << count << endl;
    a.open("ptrace.txt");
    count=FIFO(8);
    cout << "For size 8: " << count << endl;
    a.close();
    a.open("ptrace.txt");
    count=FIFO(16);
    cout << "For size 16: " << count << endl;
    a.close();
    a.open("ptrace.txt");
    count=FIFO(1);
    cout << "For size 1: " << count << endl;
    a.close();
    a.open("ptrace.txt");
    count=FIFO(2);
    cout << "For size 2: " << count << endl;
    a.close();
    return 0;
}
