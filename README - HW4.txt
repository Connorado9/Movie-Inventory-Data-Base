Movie Inventory
By Connor Humiston
7/7/19
Data Structures

Files: 
"MovieTree.hpp" 	(struct, class, and method definitions)
"MovieTree.cpp" 	(implementations)
"Assignment4.cpp" 	(main method)

Purpose: The purpose of this program is to keep track of a hypothetical movie service's inventory with the capability to display inventory info, rent a movie, and delete a movie. 

Description: This C++ program built in Sublime and run through the command line is passed a file with all the movies that need to be kept track of. The file should contain the IMDB ranking, the movie title, the release year, and the quantity in stock (with semicolons in between data). After running the program, a binary search tree of linked lists is built based on the first letter of the movies provided in the file. Each linked list contains an ordered list of the movies starting with that BST node's letter. After all the movies have been added to the tree, a main menu will be displayed with a list of options for the inventory. Typing a 1 and then pressing enter will provide info about a given movie title. 2 will simulate renting a movie. 3 Prints the entire movie inventory. 4 deletes the desired movie from the stock altogether, and 5 counts up all the movies in stock. 6 will clear all the movies from the linked list and binary tree, and exit the program. 

Running: The program can be compiled by typing g++ -std=c++11 followed by the file with the implementations in it followed by the main method file and then saved with -o
	For example:
		g++ -std=c++11 MovieTree.cpp Assignment4.cpp -o Assignment4
	
Next, the program would be run by typing ./Assignment4 followed by the name of the file with all the movies in it (as specified above).
	For example:
		./Assignment4 Movies.txt

