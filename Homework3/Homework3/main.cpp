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

int plist[10];

int Clock(int p){
    string word;
    int temp=0;
    int tvar = 0;
    int pageVar=(512/10)/p;
    int fifoCount=0;
    int memPlace;
    bool flag=false;
    int a1 = 0;
    bool testing = true;
    vector<int> list[10];
    while(a >> word){
        if(flag == false) {
            temp = stoi(word);
            flag = true;
        } else {
            memPlace = stoi(word);
            memPlace = memPlace/p;
            if (find(list[temp].begin(), list[temp].end(),memPlace) == list[temp].end() && find(list[temp].begin(), list[temp].end(),(memPlace + plist[temp]/p)) == list[temp].end()) {
                fifoCount++;
                while (testing == true) {
                    if(list[temp].size() <= pageVar){
                        list[temp].push_back(memPlace + plist[temp]/p);
                        testing = false;
                    } else {
                        if(list[temp].front() > plist[temp]){
                            a1 = list[temp].front();
                            list[temp].erase(list[temp].begin());
                            list[temp].push_back(a1 - (plist[temp]/p));
                            tvar++;
                            if (tvar < 10)
                                cout << a1 << ' ' << tvar << ' ';
                        } else {
                            list[temp].erase(list[temp].begin());
                            list[temp].push_back(memPlace + plist[temp]/p);
                            testing = false;
                        }
                    }
                }
            }
            flag = false;
            testing = true;
        }
    }
    return fifoCount;
}

int LRU(int p){
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
                list[temp].insert(list[temp].begin(),memPlace);
                fifoCount++;
                if(list[temp].size() > pageVar){
                    list[temp].pop_back();
                }
            } else {
                list[temp].erase(find(list[temp].begin(), list[temp].end(), memPlace));
                list[temp].insert(list[temp].begin(),memPlace);
            }
            flag = false;
        }
    }
    return fifoCount;
}


//Not working yet
int FIFOPload(int p){
    string word;
    int temp=0;
    int pageVar=(512/10)/p;
    int fifoCount=0;
    int memPlace;
    bool searching = false;
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
            count++;
        }
    }
    count = 0;
    //Go through the ptrace for the FIFO
    cout << "--------------------------------------------------" << endl;
    cout << "Going throug to find how many page faults for FIFO" << endl;
    int memPlace2;
    count=FIFO(1);
    a.close();
 /*   cout << "For size 1: " << count << endl;
    a.open("ptrace.txt");
    count=FIFO(2);
    cout << "For size 2: " << count << endl;
    a.close();
    a.open("ptrace.txt");
    count=FIFO(4);
    cout << "For size 4: " << count << endl;
    a.close();
    a.open("ptrace.txt");
    count=FIFO(8);
    cout << "For size 8: " << count << endl;
    a.close();
    a.open("ptrace.txt");
    count=FIFO(16);
    cout << "For size 16: " << count << endl;
    a.close();
    cout << "---------------------------------------------------" << endl;
    cout << "Going throug to find how many page faults for LRU" << endl;
    a.open("ptrace.txt");
    count = LRU(1);
    cout << "For size 1: " << count << endl;
    a.close();
    a.open("ptrace.txt");
    count = LRU(2);
    cout << "For size 2: " << count << endl;
    a.close();
    a.open("ptrace.txt");
    count = LRU(4);
    cout << "For size 4: " << count << endl;
    a.close();
    a.open("ptrace.txt");
    count = LRU(8);
    cout << "For size 8: " << count << endl;
    a.close();
    a.open("ptrace.txt");
    count = LRU(16);
    cout << "For size 16: " << count << endl;
    a.close(); */
    cout << "---------------------------------------------------" << endl;
    cout << "Going throug to find how many page faults for Clock" << endl;
    a.open("ptrace.txt");
    count = Clock(1);
    cout << "For size 1: " << count << endl;
    a.close();
    a.open("ptrace.txt");
    count = Clock(2);
    cout << "For size 2: " << count << endl;
    a.close();
    a.open("ptrace.txt");
    count = Clock(4);
    cout << "For size 4: " << count << endl;
    a.close();
    a.open("ptrace.txt");
    count = Clock(8);
    cout << "For size 8: " << count << endl;
    a.close();
    a.open("ptrace.txt");
    count = Clock(16);
    cout << "For size 16: " << count << endl;
    a.close();

    return 0;
}
