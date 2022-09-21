#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Node
{
public:
	int key;

	Node **forward;
	Node(int, int);
};

Node::Node(int key, int level)
{
	this->key = key;

	forward = new Node *[level + 1]; //  Assigning memory to forward

	memset(forward, 0, sizeof(Node *) * (level + 1)); // Memset() is a function which copies a single character for a specified number of times to an object.
};

class SkipList
{

	int MAXLVL, level; // The current level of the skiplist
	float P;

	Node *header;

public:
	SkipList(int, float);
	int randomLevel();
	Node *createNode(int, int);
	void insert(int);
	bool deletee(int);
	bool search(int);
	void displayList();
};

SkipList::SkipList(int MAXLVL, float P)
{
	this->MAXLVL = MAXLVL;
	this->P = P;
	level = 0;

	header = new Node(-1, MAXLVL);
};

int SkipList::randomLevel() // creating random level for node
{
	float r = (float)rand() / RAND_MAX;
	int lvl = 0;
	while (r < P && lvl < MAXLVL)
	{
		lvl++;
		r = (float)rand() / RAND_MAX;
	}
	return lvl;
};

Node *SkipList::createNode(int key, int level)
{
	Node *n = new Node(key, level);
	return n;
};

void SkipList::insert(int key)
{
	Node *current = header;

	Node *update[MAXLVL + 1];
	memset(update, 0, sizeof(Node *) * (MAXLVL + 1));

	/* Begin at the top of the skip list and shift the current pointer forward as long as the key is greater than the key of the node next to it.

	Otherwise, current was added in the update and

	Continue your search by going down a level.

	*/
	for (int i = level; i >= 0; i--)
	{
		while (current->forward[i] != NULL &&
			   current->forward[i]->key < key)
			current = current->forward[i];
		update[i] = current;
	}

	/* reached level 0 and moved the forward pointer to the right, which is the desired place to insert the key */
	current = current->forward[0];
	/* If current is NULL, we've reached the end of the level; if current's key differs from the key to insert, we'll have to insert a node between update[0] and the current node*/

	if (current == NULL || current->key != key)
	{

		int rlevel = randomLevel();
		/* we will initialise update value with pointer to header for subsequent usage if random level is bigger than list's current level (node with highest level inserted in list so far) */

		if (rlevel > level)
		{
			for (int i = level + 1; i < rlevel + 1; i++)
				update[i] = header;

			level = rlevel;
		}

		Node *n = createNode(key, rlevel);

		for (int i = 0; i <= rlevel; i++)
		{
			n->forward[i] = update[i]->forward[i];
			update[i]->forward[i] = n;
		}
		cout << "Successfully Inserted key " << key << "\n";
	}
};

bool SkipList::deletee(int key)
{
	Node *current = header;

	Node *update[MAXLVL + 1];
	memset(update, 0, sizeof(Node *) * (MAXLVL + 1));

	/* Begin at the top of the skip list and move the current pointer ahead if the key is bigger than the key of the node next to it; else, insert current in update and go one level down and resume searching */
	for (int i = level; i >= 0; i--)
	{
		while (current->forward[i] != NULL &&
			   current->forward[i]->key < key)
			current = current->forward[i];
		update[i] = current;
	}

	current = current->forward[0];

	if (current != NULL and current->key == key)
	{

		for (int i = 0; i <= level; i++)
		{

			if (update[i]->forward[i] != current)
				break;

			update[i]->forward[i] = current->forward[i];
		}

		// deleting the levels with no values
		while (level > 0 &&
			   header->forward[level] == 0)
			level--;
		return true;
	}
};

bool SkipList::search(int key)
{
	Node *current = header;

	for (int i = level; i >= 0; i--)
	{
		while (current->forward[i] &&
			   current->forward[i]->key < key)
			current = current->forward[i];
	}

	current = current->forward[0];

	if (current and current->key == key)
		return true;
	else
		return false;
};

void SkipList::displayList()
{
	cout << "\n***SkipList***"
		 << "\n";
	for (int i = 0; i <= level; i++)
	{
		Node *node = header->forward[i];
		cout << "Level " << i << ": ";
		while (node != NULL)
		{
			cout << node->key << " ";
			node = node->forward[i];
		}
		cout << "\n";
	}
};

int main()
{

	srand((unsigned)time(0));

	SkipList lst(2.5, 0.5);

	lst.insert(1);
	lst.insert(2);
	lst.insert(3);
	lst.search(0);
	lst.insert(4);
	lst.search(1);
	lst.deletee(0);
	lst.deletee(1);
	lst.search(1);
	lst.displayList();
}