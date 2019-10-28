// Connor Humiston
// Godley 310
// Data Structures
// Movies: BSTs & LLs

// This file contains main and the program

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "MovieTree.hpp"
using namespace std;

int main(int argc, char* argv[])
{
	//instantiate the BST and insert all the movies from the filename that was passed in the command line
	MovieSearchTree tree;
	string movieFileName = argv[1];
	tree.insertMovies(movieFileName);
	

	bool isRunning = true;
    while(isRunning)
    {
        //Program start
        //Printing the menu:
        cout << "\n";
        cout << "======Main Menu======" << endl;
        cout << "1. Find a movie" << endl;
        cout << "2. Rent a movie" << endl;
        cout << "3. Print the inventory" << endl;
        cout << "4. Delete a movie" << endl;
        cout << "5. Count the movies" << endl;
        cout << "6. Quit" << endl;

        int numIn;
        cin >> numIn;

        switch(numIn)
        {
            case 1: //Find a movie
            {
                cout << "Find a movie" << endl;
                cout << "\n";

                string movieName = "";
                cin.ignore();
                cout << "Enter a movie name: " << endl;
                getline(cin, movieName);

                cout << "\n";
                tree.findMovie(movieName);
                break;
            }

            case 2: //Rent a movie
            {
                cout << "Rent a movie" << endl;
                cout << "\n";

                string movieName = "";
                cin.ignore();
                cout << "Enter a movie name: " << endl;
                getline(cin, movieName);

                cout << "\n";
                tree.rentMovie(movieName);
                break;
            }

            case 3: //Print the inventory
            {
                cout << "Print the inventory" << endl;
                cout << "\n";

                tree.printInventory();
                break;
            }

            case 4: //Delete a movie
            {
                cout << "Delete a movie" << endl;
                cout << "\n";

                string movieName = "";
                cin.ignore();
                cout << "Enter a movie title to delete: " << endl;
                getline(cin, movieName);

                cout << "\n";
                tree.deleteMovie(movieName);
                break;
            }

            case 5: //Count the movies
            {
                cout << "Count the movies" << endl;
                cout << "\n";

                cout << "Tree contains: " << tree.countTreeMovies() << " movies." << endl;
                break;
            }

            case 6: //Quit
            {
                cout << "Goodbye!\n" << endl;
                isRunning = false;
                tree.~MovieSearchTree();
                exit(0);
                break;
            }

            default:
            {
                cout << "Sorry that wasn't an option. Please reload the program and try again." << endl;
                isRunning = false;
            }
        }
    }
}