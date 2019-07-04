#include <iostream>
#include <fstream>
#include <string>
#include "cards.h"

using namespace std;

int main(int argv, char** argc){
	string n1 = "Alice";
	string n2 = "Bob";
  if(argv < 3){
    cout << "Please provide 2 file names" << endl;
    return 1;
  }
  
  ifstream cardFile1 (argc[1]);
  ifstream cardFile2 (argc[2]);
  string line;

  if (cardFile1.fail() || cardFile2.fail() ){
    cout << "Could not open file " << argc[2];
    return 1;
  }
player p1(n1);
player p2(n2);
  //Read each file
  while (getline (cardFile1, line) && (line.length() > 0)){
p1.deal(line);
  }
  cardFile1.close();
  while (getline (cardFile2, line) && (line.length() > 0)){
p2.deal(line);
  }
  cardFile2.close();
  pointlessGame(p1, p2);
  
  cout<<endl<<p1;
  cout<<endl<<p2;
  return 0;
}
