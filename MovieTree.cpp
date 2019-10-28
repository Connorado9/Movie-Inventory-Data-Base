// Connor Humiston
// Godley 310
// Data Structures
// Movies: BSTs & LLs

// This file implements class methods

#include "MovieTree.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <locale>
using namespace std;


/*=============================Binary Search Tree Class Implementations=============================*/
// tree constructor
MovieSearchTree::MovieSearchTree()
{
	root = NULL;
}
// tree destructor
MovieSearchTree::~MovieSearchTree()
{
	deleteAll(root);
}

// Upon program start, the user will pass the name of the text file containing all movie information. 
// Each line in the file shows the IMDB ranking, title, year released, and quantity in stock. 
// The insertMovies method opens the file and reads all movie data to build the BST ordered by the first letter in the movie title.
// For each BST node, there should be a sorted singly linked list of the actual movie data
// Note: the nodes should be added to the BST and Linked Lists in the order they are read in​.
void MovieSearchTree::insertMovies(string movieFileName)
{
	//reading the file
	ifstream in(movieFileName);
    if (!in)
    {
        cout << "Movie file can't be opened! " << endl;
        exit(1);
    }

    string stringRating;
    while(getline(in, stringRating, ';'))
    {
	  	//Getting the rating, title, year, and quanitity from the file
	  	int rating = stoi(stringRating);

	    string title;
	    getline(in, title, ';');

	    string year;
	    getline(in, year, ';');
	    int releaseYear = stoi(year);

	    string quantity;
	    getline(in, quantity);
	    int quantityAvail = stoi(quantity);

	    if(quantityAvail != 0){

	    //cout << rating << endl;
	    //cout << title << endl;
	    //cout << releaseYear << endl;
	    //cout << quantityAvail << endl;
	    //cout << title.substr(0,1) << endl;

	    //Initializing a new Movie with the data from the file
	    //Movie* mov = new Movie;
	    Movie mov;
	    mov.rank = rating;
	    mov.title = title;
	    mov.year = releaseYear;
	    mov.quantity = quantityAvail;
		
		if(root == NULL) //empty BST
		{
			//initializing a new NST node
			BSTNode* newnode = new BSTNode;
			newnode->letter = title.substr(0,1);
			newnode->linkedlist = new LinkedList; 
			newnode->parent = NULL;
			newnode->leftChild = NULL;
			newnode->rightChild = NULL;

			//updating BST pointers and inserting the movie into the linked list
			root = newnode;
			newnode->linkedlist->listInsertInOrder(mov);
		}
		else //established BST
		{
			BSTNode* curr = root;
			while(curr != NULL)
			{
				if(title.substr(0,1).compare(curr->letter) == 0)
				{
					//if we have reached a BST node with the same letter, there is no need to add a new node
					curr->linkedlist->listInsertInOrder(mov); //so we insert the movie into the current node's linked list
					break;
				}
				else if(title.substr(0,1).compare(curr->letter) > 0)
				{
					if(curr->rightChild == NULL) //if cant go right anymore, insert there
					{
						//initializing a new NST node
						BSTNode* newnode = new BSTNode;
						newnode->letter = title.substr(0,1);
						newnode->linkedlist = new LinkedList; 
						newnode->parent = NULL;
						newnode->leftChild = NULL;
						newnode->rightChild = NULL;

						//inserting the movie into the new linked list
						newnode->linkedlist->listInsertInOrder(mov);

						//updating pointers for the BST
						newnode->parent = curr;
						curr->rightChild = newnode;
						break;
					}
					curr = curr->rightChild; //moving right down the tree if the value is greater than the curr value
				}
				else
				{
					if(curr->leftChild == NULL) //if cant go left anymore, insert there
					{
						//initializing a new NST node
						BSTNode* newnode = new BSTNode;
						newnode->letter = title.substr(0,1);
						newnode->linkedlist = new LinkedList; 
						newnode->parent = NULL;
						newnode->leftChild = NULL;
						newnode->rightChild = NULL;

						//inserting the movie into the new linked list
						newnode->linkedlist->listInsertInOrder(mov);

						//updating pointers for the BST
						newnode->parent = curr;
						curr->leftChild = newnode;
						break;
					}
					curr = curr->leftChild;
				}
			}
		}} //the second bracket is for the quantity available conditional above
    }
}

// When the user selects this option from the menu, they should be prompted for the name of the movie.
// The tree and linked lists are then searched to display info about the desired movie
// If the movie is not found, the program displays, “Movie not found.”
void MovieSearchTree::findMovie(string movieName)
{
	//first the BST node with the corresponding first letter is searched for in the tree
	BSTNode* bstnode = bstSearch(root, movieName.substr(0,1));
	if(bstnode == NULL)
	{
		cout << "Movie not found." << endl;
		return;
	}

	//then, once the BST node is found, the linked list is searched for that movie
	SingleNode* llnode = bstnode->linkedlist->listSearch(movieName);
	if(llnode == NULL)
	{
		cout << "Movie not found." << endl;
		return;
	}
	
	cout << "Movie Info:" << endl;
	cout << "===========" << endl;
	cout << "Title: " << llnode->movie.title << endl;
	cout << "Ranking: " << llnode->movie.rank << endl;
	cout << "Year: " << llnode->movie.year << endl;
	cout << "Quantity: " << llnode->movie.quantity << endl;
}

// When the user selects this option from the menu, they should be prompted for the name of the movie. 
// If the movie is found, the program updates the quantity in stock property of the movie and displays the new info about the movie.
// If the movie is not found, the program displays, “Movie not found.” 
// When the quantity reaches 0, the movie should be deleted from the singly linked list. 
// If that was the only node in the singly linked list, the node should also be deleted from the BST for that letter.
void MovieSearchTree::rentMovie(string movieName)
{
	BSTNode* bstnode = bstSearch(root, movieName.substr(0,1));
	if(bstnode == NULL)
	{
		cout << "Movie not found." << endl;
		return;
	}

	//then, once the BST node is found, the linked list is searched for that movie
	SingleNode* llnode = bstnode->linkedlist->listSearch(movieName);
	if(llnode == NULL)
	{
		cout << "Movie not found." << endl;
		return;
	}

	//If movie is in stock, the quantity is updated, and new info printed
	llnode->movie.quantity--;
	cout << llnode->movie.title << " has been rented." << endl;
	cout << "\n";
	cout << "Movie Info:" << endl;
	cout << "===========" << endl;
	cout << "Title: " << llnode->movie.title << endl;
	cout << "Ranking: " << llnode->movie.rank << endl;
	cout << "Year: " << llnode->movie.year << endl;
	cout << "Quantity left: " << llnode->movie.quantity << endl;
	cout << "\n";

	if(llnode->movie.quantity == 0)
	{
		deleteMovie(movieName);
		cout << "NOTICE: The movie was removed from inventory since there were 0 left in stock." << endl;
	}
}

// When the user selects printInventory, all movie titles and quantitis available are displayed in sorted order by title. 
// Refer to the lecture notes as well as the text book on in-order tree traversal, and linked list traversals
void MovieSearchTree::printInventory()
{
	printNode(root);
}

// When the user selects this option, they should be prompted for the title of the movie to delete. 
// The tree is searched for the first letter of the moive passed, and the linked list is searched for the title.
// If the title is found, delete it from the singly linked list. 
// If it was the only title for that letter in the BST, the node is deleted in the BST and the parent and child pointers are re-assigned to bypass the deleted node (and the memory is freed) 
// If the movie is not found in the search process, print “Movie not found” and do not attempt to delete. 
// A movie node should also be deleted when its quantity goes to 0. (after renting)
void MovieSearchTree::deleteMovie(string movieName)
{
	//first the BST node with the corresponding first letter is searched for in the tree
	BSTNode* bstnode = bstSearch(root, movieName.substr(0,1));
	if(bstnode == NULL)
	{
		cout << "Movie not found." << endl;
		return;
	}

	//then, once the BST node is found, the movie is deleted from the linked list
	bstnode->linkedlist->deleteLLNode(movieName);

	//if the linked list is now empty, the bst node is deleted too
	if(bstnode->linkedlist->gethead() == NULL)
	{
		deleteBSTNode(bstnode->letter);
	}

	cout << movieName << " was deleted." << endl;
}


// This method deletes the bst node with the corresponding letter
void MovieSearchTree::deleteBSTNode(string letter)
{
	//finding the node we want to delete
	BSTNode* toDelete = bstSearch(root, letter);

	if(toDelete == NULL)
	{
		cout << "There was an error deleting the BST node." << endl;
	}

	//Deleting a leaf (no children)
	if(toDelete->leftChild == NULL && toDelete->rightChild == NULL)
	{
		if(toDelete == root) //only the root
		{
			root = NULL;
		}
		else if(toDelete->letter < toDelete->parent->letter) //using keys to determing which side we are on
		{
			toDelete->parent->leftChild = NULL;
		}
		else //seting the parent's right child to NULL
		{
			toDelete->parent->rightChild = NULL;
		}
		delete toDelete;
	}
	//Deleting a node with one child
	else if(toDelete->leftChild == NULL || toDelete->rightChild == NULL) 
	{
		if(toDelete->leftChild != NULL) //we have a left child
		{
			toDelete->leftChild->parent = toDelete->parent;
			if(toDelete->letter < toDelete->parent->letter) //using keys to determing which side we are on
			{
				toDelete->parent->leftChild = toDelete->leftChild;
			}
			else //seting the parent's right child to NULL
			{
				toDelete->parent->rightChild = toDelete->leftChild;
			}
		}
		else //we have a right child
		{
			toDelete->rightChild->parent = toDelete->parent;
			if(toDelete->letter < toDelete->parent->letter) //using keys to determing which side we are on
			{
				toDelete->parent->leftChild = toDelete->rightChild;
			}
			else //seting the parent's right child to NULL
			{
				toDelete->parent->rightChild = toDelete->rightChild;
			}
		}
		delete toDelete;
	}
	//Deleting a node with two children
	else
	{
		BSTNode* rMin = minElement(toDelete->rightChild);
		//cout << "Found rMin: " << rMin->key << endl;
		//handling the hole generated by removing rMin
		if(rMin->rightChild != NULL) 
		{
			rMin->rightChild->parent = rMin->parent;
			if(rMin->letter < rMin->parent->letter) //rMin is left child
			{
				rMin->parent->leftChild = rMin->rightChild;
			}
			else
			{
				rMin->parent->rightChild = rMin->rightChild;
			}	
		} 
		//or simply delete rMin because we know it only has one child so it falls in condition above
		// deleteNode(rMin); //this will also delete memory
		else
		{
			if(rMin->parent == toDelete) //rMin is a rightChild
			{
				rMin->parent->rightChild = NULL;
			}
			else
			{
				rMin->parent->leftChild = NULL;
			}
		}

		//now we can just change the data (lazy but efficient), only works with data of same size
		//cout << "Updating toDelete: " << toDelete->key << " with rMin: " << rMin->key << endl;
		toDelete->letter = rMin->letter;
		delete rMin;
	}
}

// Returns a pointer to the minimum element of a given node's tree 
BSTNode* MovieSearchTree::minElement(BSTNode* node)
{
	// Using the properties of binary tree, the minimum is on the left
	if(node == NULL) return NULL;
	else if(node->leftChild == NULL) return node;
	return minElement(node->leftChild);
}

// Deletes all the nodes and linked lists in the tree up to the node it is was passed
void MovieSearchTree::deleteAll(BSTNode* bstnode)
{
	//if the tree is empty, we exit the method
   	if(root == NULL)
   	{
    	return;
   	}
   	//moving down the left 
   	if(bstnode->leftChild != NULL)
   	{
    	deleteAll(bstnode->leftChild);
   	}
   	//moving down the right
   	if(bstnode->rightChild != NULL)
   	{
    	deleteAll(bstnode->rightChild);
   	}

   	//Now deleting the linked list when we get to a leaf
  	SingleNode* current = bstnode->linkedlist->gethead();
   	//MovieNodeLL* current = node->head;
   	SingleNode* temp;
	//MovieNodeLL* temp;
   	while(current != NULL)
   	{
    	temp = current->next;
    	cout << "Deleting: " << current->movie.title << endl;
    	delete current;
    	current = temp;
   	}
   	current = NULL;
   	delete bstnode;
   	return;
}

// This option traverses the tree and singly linked lists to count and print the total movie nodes in the tree.
int MovieSearchTree::countTreeMovies()
{
	int count = 0;
	int* countptr = &count;

	count_helper(root, countptr);

	return count;	
}

void MovieSearchTree::count_helper(BSTNode* bstnode, int* countptr)
{
	//traversing the left subtree
	if(bstnode->leftChild != NULL)
	{
		count_helper(bstnode->leftChild, countptr); //recurse
	}

	//add up the current bstnode's count by traversing its linked list
	SingleNode* temp = bstnode->linkedlist->gethead();
	while(temp != NULL)
	{
		*countptr = *countptr + temp->movie.quantity;
		temp = temp->next;
	}

	//traversing the right subtree
	if(bstnode->rightChild != NULL)
	{
		count_helper(bstnode->rightChild, countptr); //recurse
	}
}

// This recurively prints the tree starting at the passed node
void MovieSearchTree::printNode(BSTNode* node)
{
	//check valid input
	if(node == NULL) 
	{
		cout << "There are no movies in the inventory." << endl;
		return;
	}

	//print left subtree
	if(node->leftChild != NULL)
	{
		//cout << "Moving left" << endl;
		printNode(node->leftChild); //recurse
	}

	//print current node's key
	LLTraverse(node->linkedlist->gethead());

	//print right subtree
	if(node->rightChild != NULL)
	{
		//cout << "Moving left" << endl;
		printNode(node->rightChild); //recurse
	}
}

// Prints the movies in the linked list from the head it is given
void MovieSearchTree::LLTraverse(SingleNode* head)
{
	SingleNode* temp = head;
	while(temp != NULL)
	{
		cout << "Movie: " << temp->movie.title << " - " << temp->movie.quantity << endl;
		//if(temp->next != NULL) 
		//	cout << ", ";
		temp = temp->next;
	}
}

// Searches for the movie starting at the node it was passed, and returns a BST node pointer
BSTNode* MovieSearchTree::bstSearch(BSTNode* node, string letter)
{
	if(node == NULL)
		return NULL;
	if(letter.compare(node->letter) == 0)
	{
		return node;
	}
	else if(letter.compare(node->letter) > 0) //search right
	{
		return bstSearch(node->rightChild, letter);
	}
	else //search left
	{
		return bstSearch(node->leftChild, letter);
	}
};
/*=============================END of BST Class Implementations=============================*/




/*=============================Linked List Class Implementations=============================*/
// constructor
LinkedList::LinkedList()
{
	head = NULL;
}

// Prints out the linked list contents -- for testing purposes
void LinkedList::traverse()
{
	SingleNode *temp = head;
	cout << "List contents: [";
	while(temp != NULL)
	{
		cout << temp->movie.title;
		if(temp->next != NULL) 
			cout << ", ";
		temp = temp->next;
	}
	cout << "]" << endl;
}

// Searches the linked list for the movie and returns the node it's in
SingleNode* LinkedList::listSearch(string movieName)
{
	SingleNode *temp = head; //temp starts at head (cant go backwards)
	while(temp != NULL)
	{
		if(temp->movie.title.compare(movieName) == 0)
			return temp;
		temp = temp->next; //moving through the linked list if the temp node does not have the desired value
	}
	return NULL;
}

// Adds movie m into the linked list in its proper place (so the movies are in ascending order)
void LinkedList::listInsertInOrder(Movie m)
{
	//initializing new node
	SingleNode* toAdd = new SingleNode; 
	toAdd->movie = m;
	toAdd->next = NULL;

	//we need to traverse the list to find the right spot for our movie (finding left)
	SingleNode* temp = head; //starting at the head
	SingleNode* left = NULL;
	if(temp == NULL)
	{
		left = NULL; //if nothing in the list, left is still null
	}
	else if(temp->movie.title.compare(m.title) == 0) //if the current node has the same title
	{
		left = temp; //if they have the same title, the left node is set to that node
		left->movie.quantity = left->movie.quantity + m.quantity; //left node's quantity is simply added to by the quantity
		return; //leave the method if a duplicate title is encountered
	}
	else
	{
		while(temp->movie.title.compare(m.title) <= 0) //while the title is lower in the alphabet than the temp's movie title
		{
			if(temp->next == NULL) //if we've reached the end of the list
			{
				left = temp;
				break;
			}
			else if(temp->next->movie.title.compare(m.title) == 0) //if the next node has the name title
			{
				left = temp->next; //left is set to next node
				left->movie.quantity = left->movie.quantity + m.quantity; //left node's quantity is simply added to by the quantity
				return; //leave the method if a duplicate title is encountered
				//break;
			}
			else if(temp->next->movie.title.compare(m.title) > 0)
			{
				left = temp;
				break;
			}
			//otherwise if next is still less than
			temp = temp->next;
		}
	}
	
	//inserting the new node at the head
	if(left == NULL)
	{
		toAdd->next = head; //need for next to reference the old head before
		head = toAdd; //before changing the old head
	}
	else //not a new head
	{
		toAdd->next = left->next; //update the next before
		left->next = toAdd; //changing the left node's next pointer (which could have been the head) to be the add node
	}
}

// Gets the tail for the append function above
SingleNode* LinkedList::gettail()
{
	SingleNode* curr;
	SingleNode* beforecurr = NULL;
	curr = head;
	while (curr) 
	{
		beforecurr = curr;
		curr = curr->next;
	}
	return beforecurr;
}

// Returns a pointer to the head for the BST nodes to access the linked lists
SingleNode* LinkedList::gethead()
{
	return head;
}

// Deleteing the node containting the movie that was passed
void LinkedList::deleteLLNode(string movieName) 
{
	SingleNode *toDelete; 
	bool found = false;
	if(head == NULL)
	{
		found = false;
	}
	else if(head->movie.title == movieName) //if we are trying to delete the head
	{
		toDelete = head;
		head = head->next; //head now points to the next node
		found = true;
	}
	else //of not deleting the head then deleting the tail or in the middle
	{
		SingleNode *temp = head; //starts at head
		while(temp->next != NULL)
		{
			if(temp->next->movie.title == movieName) //if the next node has the value we are looking for, temp is leftnode and next is toDelete
			{
				toDelete = temp->next; 
				temp->next = toDelete->next;
				found = true;
				break; //found elements and dont want to keep looking 
			}
			temp = temp->next; //keeps going along the list
		}
	}
	if(found == false)
	{
		cout << "Movie not found." << endl;
		return;
	}
	delete toDelete;
}
/*=============================END of Linked List Class Implementations=============================*/



