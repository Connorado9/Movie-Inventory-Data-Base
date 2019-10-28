// Connor Humiston
// Godley 310
// Data Structures
// Movies: BSTs & LLs

// This is the class prototype/header file with struct, class, and method definitions

#pragma once //we are including this file in the .cpp files just once
#include <iostream>
using namespace std;

// This is the movie data struct
struct Movie
{
	int rank;
	string title;
	int year;
	int quantity;
};


// This is the singly linked list node struct
struct SingleNode
{
	Movie movie;
	SingleNode *next;
};


// This is the linked list class that the BST nodes will also point to
class LinkedList
{
private:
	SingleNode* head;
public:
	// Constructor
	LinkedList();

	// Prints out the linked list contents -- for testing purposes
	void traverse();
	
	// Searches the linked list for the movie and returns the node it's in
	SingleNode* listSearch(string movieName);

	// Adds movie m into the linked list in its proper place (so the movies are in ascending order)
	void listInsertInOrder(Movie m);

	// Gets the tail for the append function above
	SingleNode* gettail();

	// Returns a pointer to the head for the BST nodes to point to
	SingleNode* gethead();

	// Deleteing the node containting the movie that was passed
	void deleteLLNode(string movieName);
};


// The BST node structure of movies
struct BSTNode
{
	string letter;
	LinkedList* linkedlist;
	//SingleNode* pointer; //pointer to head of linked list
	BSTNode* parent;
	BSTNode* leftChild;
	BSTNode* rightChild;
};


// This is the BST of letters and LL pointers
class MovieSearchTree
{
private:
	BSTNode* root;

	// This recurively prints the tree starting at the node it was passed - primarily for testing purposes
	void printNode(BSTNode* node);

	// Searches for the movie starting at the node it was passed, and returns a BST node pointer
	BSTNode* bstSearch(BSTNode* node, string letter);

	// Returns a pointer to the minimum node element of a given node's tree 
	BSTNode* minElement(BSTNode* node);
	
public:
	MovieSearchTree();
	~MovieSearchTree();

	// Upon program start, the user will pass the name of the text file containing all movie information. 
	// Each line in the file shows the IMDB ranking, title, year released, and quantity in stock. 
	// The insertMovies method opens the file and reads all movie data to build the BST ordered by the first letter in the movie title.
	// For each BST node, there should be a sorted singly linked list of the actual movie data
	// Note: the nodes should be added to the BST and Linked Lists in the order they are read in​.
	void insertMovies(string movieFileName);

	// When the user selects this option from the menu, they should be prompted for the name of the movie.
	// The tree and linked lists are then searched to display info about the desired movie
	// If the movie is not found, the program displays, “Movie not found.”
	void findMovie(string movieName);

	// When the user selects this option from the menu, they should be prompted for the name of the movie. 
	// If the movie is found, the program updates the quantity in stock property of the movie and displays the new info about the movie.
	// If the movie is not found, the program displays, “Movie not found.” 
	// When the quantity reaches 0, the movie should be deleted from the singly linked list. 
	// If that was the only node in the singly linked list, the node should also be deleted from the BST for that letter.
	void rentMovie(string movieName);

	// When the user selects printInventory, all movie titles and quantitis available are displayed in sorted order by title. 
	// Refer to the lecture notes as well as the text book on in-order tree traversal, and linked list traversals
	void printInventory();

	// When the user selects this option, they should be prompted for the title of the movie to delete. 
	// The tree is searched for the first letter of the moive passed, and the singly linked list is searched for the title.
	// If the title is found, delete it from the singly linked list. 
	// If it was the only title for that letter in the BST, the node is deleted in the BST and the parent and child pointers are re-assigned to bypass the deleted node (and the memory is freed) 
	// If the movie is not found in the search process, print “Movie not found” and do not attempt to delete. 
	// A movie node should also be deleted when its quantity goes to 0.
	void deleteMovie(string movieName);

	// This method deletes the bst node with the corresponding letter
	void deleteBSTNode(string letter);

	// Deletes all the nodes and linked lists in the tree up to the node it is was passed
	void deleteAll(BSTNode* node);

	// This method traverses the tree and singly linked lists and returns the total number of movie nodes in the tree.
	int countTreeMovies();

	// Updates the count of a subtree starting at the passed node
	void count_helper(BSTNode* node, int* count);

	// Prints the movies in the linked list from the head it is given
	void LLTraverse(SingleNode* head);
};








