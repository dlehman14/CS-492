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

struct pageTable {
    
};

int main() {
    //Declare the two inputs from the files, and read the files into the data
    int plist[10];
    ifstream f("plist.txt");
    ifstream a("ptrace.txt");
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
    int memPlace;
    vector<int> list[10];
    while(a >> word){
        if(flag == false) {
            temp = stoi(word);
            flag = true;
        } else {
            memPlace = stoi(word);
            memPlace = memPlace/4;
            if (find(list[temp].begin(), list[temp].end(), memPlace) == list[temp].end()) {
                count++;
                list[temp].insert(list[temp].begin(),memPlace);
                if(list[temp].size() > 12)
                    list[temp].pop_back();
            
            }
         
            flag = false;
        }
    }
    
    a.close();
    cout << "For size 4: " << count << endl;
    a.open("ptrace.txt");
    count = 0;
    vector<int> dist[10];
    while(a >> word){
        if(flag == false) {
            temp = stoi(word);
            flag = true;
        } else {
            memPlace = stoi(word);
            memPlace = memPlace/8;
            if (find(dist[temp].begin(), dist[temp].end(), memPlace) == dist[temp].end()) {
                count++;
                dist[temp].insert(dist[temp].begin(),memPlace);
                if(dist[temp].size() > 6)
                    dist[temp].pop_back();
                
            }
            flag = false;
        }
    }
    
    cout << "For size 8: " << count << endl;
    a.close();
    return 0;
}
