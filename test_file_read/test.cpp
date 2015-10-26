#include <iostream>
#include <fstream>
#include <stdio.h>
#include <bitset>
#include <iomanip>
using namespace std;


int main () {
  ifstream fin("single.pcapng", ios::in|ios::binary);
  char ch;
  string str;
  while(!fin.eof()){
  	ch = fin.get();
  	str += ch;
  }
  fin.close();

  for(int i = 0; i < str.length(); i++){
  	cout<<hex<<uppercase<<setfill('0')<<(str.at(i) - '0')<<endl;

  }
  
  return 0;
}
