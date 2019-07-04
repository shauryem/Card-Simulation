//cards.h
//Author: Shaurye Mahajan
//All class declarations 

#ifndef CARDS_H
#define CARDS_H


#include<iostream>
#include<string>

using namespace std;


class card {

public:

    card(string& v);
    card();
    void setValue(string v);
    string getValue() const;
   int orderScore;
friend bool operator==(const card& c1, const card& c2);
friend bool operator >(const card& c1, const card& c2);

friend bool operator <(const card& c1, const card& c2);
private:

    string value;
};

class player {

private:

    class Node {
	    public:
	Node(string& value);	    
	card data;
        Node* left;
	Node* right;
	Node* parent;
    };

    Node* root;
    string name;
    bool dealHelper(string value, Node* n);
    Node* getNodeFor(string value,Node * n) const;
   // void coutHelper(ostream& os, Node* n);
	
public:

    player(string& name);
    bool deal(string value); // append value at end of list
    bool contains(string value) const;
    void clear (Node* n);	    
    string getPredecessor(string value) const;
    string getSuccessor(string value) const;
    Node* getPredecessorNode(string value) const;
    Node* getSuccessorNode(string value) const;
    bool remove(string value);
    Node* min();
    Node* max();


    ~player();  
    
    string getName() const;
	
    friend void pointlessGame(player& p1, player& p2);

    friend ostream& operator<<(ostream& os, const player& p1);

   

};
//bool operator==(const card& c1, const card& c2);
//bool operator >(const card& c1, const card& c2);
//bool operator <(const card& c1, const card& c2);
#endif
