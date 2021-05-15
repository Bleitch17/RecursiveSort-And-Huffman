#include <vector>
#include <iostream>

using namespace std;

struct node{
    node(int, string, node* , node*, node*);
	int count;
	string st;
	node* left;
	node* right;
	node* next;
	
};

node::node(int c, string s, node* l=0, node* r=0, node* n = 0){ //default left and right is null
    count = c;
    st = s;
    left = l;
    right = r;
    next = n;
}

void pushfront(node* &nd, int c, string s, node* comb){ 
	if (comb != 0)
	{
		node* nwn = new node(c, s);
		nwn -> next = nd;
		nd = nwn;
		nd -> left = comb -> left;
		nd -> right = comb -> right;
	}
	
	else
	{
		node* nwn = new node(c, s);
		nwn -> next = nd;
		nd = nwn;
	}
}

void walk(node* nd){
	cout << nd->st << nd->count << " ";
	if (nd -> next  !=0 )
		walk(nd -> next);
}

void insert(node* &nd, int c, string s, node* comb){  // inserts with order
	if (comb != 0)	
	{
		if (nd == 0)
		{
			nd = comb;
			return;
		}
		if (c > nd->count)
		{
			pushfront(nd, c, s, comb);
			return;
		}
		if (c == nd->count)
		{
			if (s < nd->st)
			{
				pushfront(nd, c, s, comb);
				return;
			}
		}
		insert(nd->next, c, s, comb);
	}
	
	else
	{
		if (nd == 0)
		{
			nd = new node(c, s);
			return;
		}
		
		if (c > nd -> count)
		{
			pushfront(nd, c, s, 0);
			return;
		}
		
		if (c == nd -> count)
		{
			if (s < nd -> st)
			{
				pushfront(nd, c, s, 0);
				return;
			}
		}
		
		insert(nd->next, c, s, 0);
	
	}
}

node* Combine(node* &nd) {
	if (nd -> next -> next != 0)
	{
		Combine(nd->next);
	}
	
	else
	{
		node* nwn = new node((nd->count + nd->next->count), (nd->st + nd->next->st));
		nwn->left = nd;
		nwn->right = nd->next;
		nd -> next = 0;
		nd = 0;
		return nwn;
	}	
}

void Huffman(node* &root) {
	node* comb = 0;
	while (root->next != 0)
	{
		comb = Combine(root);
		cout << "comb returned" << endl;
		insert(root, comb->count, comb->st, comb);
		walk(root);
		cout << endl;
	}
}

int main() {

	string phrase = "mississippi river";
	vector <node> Nodes;
	bool First = true;
	bool Insert = true;
	node* root = 0;
	
	for (unsigned int i = 0; i < phrase.size(); i++)
	{
		Insert = true;
		if (First == true)
		{
			Nodes.push_back(node(1, phrase.substr(i, 1)));
			First = false;
		}
		
		else
		{
			for (unsigned int i2 = 0; i2 < Nodes.size(); i2++)
			{
				if (Nodes[i2].st == phrase.substr(i, 1))
				{
					Nodes[i2].count += 1;
					Insert = false;
					break;
				}
			}
			if (Insert == true)
			{
				Nodes.push_back(node(1, phrase.substr(i, 1)));
			}
		}
	}
	
	for (unsigned int i = 0; i < Nodes.size(); i++)
	{
		cout << Nodes[i].st << " " << Nodes[i].count << endl;
	}
	
	for (unsigned int i = 0; i < Nodes.size(); i++)
	{
		insert(root, Nodes[i].count, Nodes[i].st, 0);
	}

	walk(root);
	cout << endl;

	Huffman(root);
	
	return 0;
}
