//cards.cpp
//Authors: Shaurye Mahajan
//Implementation of the classes defined in cards.


#include "cards.h"
#include<stack>

player::Node::Node(string& value) {
    data.setValue(value);
    left = NULL;
    right = NULL;
    parent = NULL;
}
card::card() {
    value = "";
    orderScore = 0;
}
card::card(string& v) {
    value = v;

    orderScore =0;

    if(v.at(0) == 'd')
        orderScore+=20;
    if(v.at(0) == 's')
        orderScore+=40;
    if(v.at(0) == 'h')
        orderScore+=60;
    string tmp = v.substr(2);

    if(tmp == "a")
        orderScore++;
    else if(tmp == "j")
        orderScore += 11;
    else if(tmp == "q")
        orderScore += 12;
    else if(tmp == "k")
        orderScore += 13;
    else {
        orderScore += stoi(tmp);
    }
}
void card::setValue(string v) {
    value = v;

    orderScore =0;

    if(v.at(0) == 'd')
        orderScore+=20;
    if(v.at(0) == 's')
        orderScore+=40;
    if(v.at(0) == 'h')
        orderScore+=60;
    string tmp = v.substr(2);

    if(tmp == "a")
        orderScore++;
    else if(tmp == "j")
        orderScore += 11;
    else if(tmp == "q")
        orderScore += 12;
    else if(tmp == "k")
        orderScore += 13;
    else {
        orderScore += stoi(tmp);
    }
}
string card::getValue() const {
    return value;
}
player::player(string& name) : root(NULL) {
    this->name = name;
}

// destructor deletes all nodes
player::~player() {
    clear(root);
}

// recursive helper for destructor
void player::clear(player::Node *n) {
    if (n) {
        clear(n->left);
        clear(n->right);
        delete n;
    }
}
// insert value in tree; return false if duplicate
bool player::deal(string value) {
    // handle special case of empty tree first
    if (!root) {
        root = new player::Node(value);
        return true;
    }
    //otherwise use recursive helper
    return dealHelper(value, root);

}

// recursive helper for insert (assumes n is never 0)
bool player::dealHelper(string value, player::Node *n) {
    card c(value);


    if (value == n->data.getValue())
        return false;
    if (c.orderScore < n->data.orderScore) {
        if (n->left)
            return dealHelper(value, n->left);
        else {
            n->left = new player::Node(value);
            n->left->parent = n;
            return true;
        }
    }
    else {
        if (n->right)
            return dealHelper(value, n->right);
        else {
            n->right = new player::Node(value);
            n->right->parent = n;
            return true;
        }
    }
}

/*
player::Node* player::getNodeFor(string value, player::Node* n) const {
//if (value== "ERROR"|| value == "") return n->parent;
    if(n) {
        if(n->data.getValue()==value) {
            cout<<"HERE";
            return n;
        }
        if(getNodeFor(value, n->left))
            return getNodeFor(value, n->left);
        if(getNodeFor(value, n->right))
            return getNodeFor(value, n->right);
    }
    return NULL;
}
*/

player::Node* player::getNodeFor(string value, player::Node* n) const{
	card c(value);
	
	if (n != NULL){
		if(n->data.orderScore == c.orderScore){
			return n;
		}
		else{
			if(c.orderScore < n->data.orderScore){
				return getNodeFor(value, n->left);
			}
			else{
				return getNodeFor(value, n->right);

			}

		}

	}
	else{
		return NULL;
	}	

}
/*
player::Node* player::getNodeFor(string value) const {
    player::Node* n = root;
    while(n->left) n = n->left;
    while(n) {
        if(n->data.getValue() == value) {
            return n;
        }
        n = getSuccessorNode(n->data.getValue());
    }
    return NULL;
}
*/

// returns true if value is in the tree; false if not
bool player::contains(string value) const {
    player::Node* g = getNodeFor(value,root);
    if(g == 0)
        return false;
    else
        return true;


}
player::Node* player::getPredecessorNode(string value) const {
    Node*n = getNodeFor(value,root);
    card c(value);

    if(n->left) {
        n = n->left;
        while(n->right)
            n = n->right;
        return n;
    }
    else {
        while(n->parent) {
            n = n->parent;
            if (n->data.orderScore < c.orderScore)
                return n;
        }
    }
    return NULL;
}

string player::getPredecessor(string value) const {
    if (getPredecessorNode(value))
        return getPredecessorNode(value)->data.getValue();
    return "ERROR";
}
player::Node* player::getSuccessorNode(string value) const {
    Node*n = getNodeFor(value,root);
    card c(value);

    if(n->right) {
        n = n->right;
        while(n->left)
            n = n->left;
        return n;
    }
    else {
        while(n->parent) {
            n = n->parent;
            if (n->data.orderScore > c.orderScore)
                return n;
        }
    }
    return NULL;
}
string player::getSuccessor(string value) const {
    if (getSuccessorNode(value))
        return getSuccessorNode(value)->data.getValue();
    return "ERROR";
}
// deletes the Node containing the given value from the tree
// returns true if the node exist and was deleted or false if the node does not exist
bool player::remove(string value) {

    player::Node* n = getNodeFor(value,root);
    if(!n) {
        return false;
    }
    if(n->left&&!(n->right)&&!(n->parent)){
    root = n->left;
    root->parent = NULL;
    delete n;
    }
    if(n->right&&!(n->left)&&!(n->parent)){
    root = n->right;
    root->parent = NULL;
    delete n;
    }
    if(n->left && n->right) {
        Node* s =getSuccessorNode(value);
        string temp =n->data.getValue();
        n->data.setValue(s->data.getValue());
        s->data.setValue(temp);
        n=s;
    }
    if(!n->left && !n->right) {
        if(n->parent) {
            if(n== n->parent->left)
                n->parent->left = NULL;
            else
                n->parent->right = NULL;

        }
        else root = NULL;
        delete n;
    }
    else if(!n->right && n->parent) {
        n->left->parent = n->parent;
        if(n==n->parent->left)
            n->parent->left = n->left;
        else
            n->parent->right = n->left;
        delete n;
    }
    else if(!n->left && n->parent) {
        n->right->parent = n->parent;
        if(n==n->parent->right)
            n->parent->right = n->right;
        else
            n->parent->left = n->right;
        delete n;
    }
    return true;
}
string player::getName() const {
    return name;
}


bool operator==(const card& c1, const card& c2) {
    if(c1.orderScore == c2.orderScore)
        return true;
    return false;
}
bool operator >(const card& c1, const card& c2) {
    if(c1.orderScore > c2.orderScore)
        return true;
    return false;
}
bool operator <(const card& c1, const card& c2) {
    if(c1.orderScore < c2.orderScore)
        return true;
    return false;

}
ostream& operator<<(ostream& os, const player& p1) {
    player::Node* curr = p1.root;
    os<<p1.name<<"'s cards:"<<endl;


    stack<player::Node *> s;


    while (curr != NULL || s.empty() == false)
    {

        while (curr !=  NULL)
        {

            s.push(curr);
            curr = curr->left;
        }


        curr = s.top();
        s.pop();
        os<< curr->data.getValue() <<endl;
        curr = curr->right;

    }
    return os;
}
player::Node* player::min() {
    player::Node* p = root;
    while(p->left) p = p->left;
    return p;
}
player::Node* player::max() {
    player::Node* p = root;
    while(p->right) p = p->right;
    return p;
}
void pointlessGame(player& p1, player& p2) {
    string i1Val;
    string i2Val;
    player::Node* i1 = p1.min();
    player::Node* i2 = p2.max();
    while (i1 || i2) {
        i1 = p1.min();
        i2 = p2.max();
        while(i1) {
            i1Val = i1->data.getValue();
            if (p2.contains(i1Val)) {
                p1.remove(i1Val);
                p2.remove(i1Val);
                cout<<p1.name<<" picked matching card "<<i1Val<<endl;
		
                i1 = p1.min();
		
                i2 = p2.max();
		
                break;
            }
	    

            i1 = p1.getSuccessorNode(i1Val);
	    
        }
        while(i2) {
            i2Val = i2->data.getValue();
	    
            if (p1.contains(i2Val)) {
		    
                p1.remove(i2Val);
                p2.remove(i2Val);

                cout<<p2.name<<" picked matching card "<<i2Val<<endl;
                i1 = p1.min();
                i2 = p2.max();
                break;
            }

           i2 = p2.getPredecessorNode(i2Val);
        }
    }
 
}
