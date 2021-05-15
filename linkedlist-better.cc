
#include <iostream>
using namespace std;

struct node{
	node(string s, node*);
	string st;
	node* next;
};

node::node(string s, node* np=0){ //:: scope resolution operator
	st = s;
	next = np;
}


void walk(node* nd){
	cout << nd->st << " ";
	if (nd->next  !=0 )
		walk(nd->next);
}

int length(node* nd){
	if (nd == 0) return 0;
    else if (nd->next == 0) return 1;

    else
    {   
        return length(nd->next) +1;
    }

}

//Must pass nd by ref or seg fault. We must change root node address in main.
void pushfront(node* &nd, string s){ 
	node* nwn = new node(s);
	nwn->next = nd;
	nd = nwn;
}


void popfront(node* &nd){
	if (nd != 0) //can't popfront if nothing to pop
	{
		node* temp = nd->next;
		delete nd;
		nd = temp;
	}
}


/*can't pushback on root=0 since no node exists yet. So must check for it.
copy ctor called for nd pointer so root in main not changed. This is 
okay if one node already exists since we just add to the end of it.
But if no node exists yet (root=0) then we must change root addr so we
have to pass by ref also.*/

void pushback(node* &nd, string s){ 
	if (nd == 0){ // or !nd
		nd = new node(s); //call new directly for defined struct ctor
		return;
	}
	pushback(nd->next, s);
}


void popback(node* &nd){
	if (nd == 0) return; //can't delete nothing
	
	if (nd->next == 0)
	{
		delete nd;
		nd = 0;
	}
	else
	{
		popback(nd->next);
	}
}


/* must pass nd by ref since we may need to insert at the
root node and hence change the root addr */
void insert(node* &nd, string s){ 
    //inserts in the correct sorted location
	if (nd == 0)
	{
		nd = new node(s);
		return;
	}
	if (s < nd->st)
	{
		pushfront(nd, s);
		return;
	}
	else
	{
		insert(nd->next, s);
		return;
	}
}

	
void lfree(node* nd){
	if (nd->next != 0)
		lfree(nd->next);
	delete nd;
}
	


int main(){
	
	const char* sarray[6] = {"b","d","a","e","f","c"};
	node* root=0;
	
	int x;
	for (x=0; x<6 ; x++)
	{
		//pushback(root, sarray[x]);
		//pushfront(root, sarray[x]);
		insert(root, sarray[x]);
		walk(root);
		cout<<endl;
	}
	cout << length(root) << endl;
	
	insert(root, "g");
	walk(root);
	cout << endl;
/*	
	for (x=0; x<3 ; x++)
	{
		cout<<"popfront"<<endl;
		popfront(root);
		walk(root);
		cout<<endl;
	}
	insert(root, "zoo");
	walk(root);
	cout<<endl;	
	
	for (x=0; x<3 ; x++)
	{
		cout<<"popback"<<endl;
		popback(root);
		walk(root);
		cout<<endl;
	}
	pushback(root, "zzz");
	walk(root);
	cout<<endl;
*/	
	lfree(root);
	return 0;
}

	
