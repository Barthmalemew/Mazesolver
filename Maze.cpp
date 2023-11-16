// Tries to solve a maze using a recursive solution
// Shows path through the maze if one exists

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cctype>
#include <string>
using namespace std;

const int FILENAMESIZE = 255;
const int MAXROWS = 22;
const int MAXCOLS = 81;

// ASCII characters to use for display
// https://theasciicode.com.ar/extended-ascii-code/block-graphic-character-ascii-code-219.html
const char WALL = (char)219;
const char WALLINFILE = '0';
const char START = 'S';
const char DEST = 'D';
const char EMPTY = ' ';
const char PATH = '*';
const char DEAD = 'X';

/*
* getFile will get a filename from the user. It then attmpts
* to open the file, read its contents, and store the maze
* structure into the maze array, based on the contents of the file. 
* A WALLINFILE character in the file represents a maze wall, while
* an EMPTY character represents a free pathway. The file should also
* contain a single START character and a single DEST character.
* The function stops reading and exits the program if > MAXCOLS-1
* characters are found on one row, or if > MAXROWS rows are
* found in the file.  If the function is successful, then 
* startX and startY will be set to the row and column number of 
* where the START character is located in the maze.
*/
void getMaze(char maze[][MAXCOLS], int& startX, int& startY);

/*
* display is used to draw the maze on the screen.
*/
void display(const char maze[][MAXCOLS]);



// TODO: Declare the remaining functions you need



int main()
{
	char maze[MAXROWS][MAXCOLS];

	// TODO: Write the main function

	return 0;
}


// TODO: Write the code for the remaining functions that you need


void display(const char maze[][MAXCOLS])
{
	// system("cls") clears the screen; only works on Windows machines
	// You will probably need to comment this out if working on
	// a non-Windows machine
	system("cls");

	// TODO: Write the display function
}

void getMaze(char maze[][MAXCOLS], int& startX, int& startY)
{
	// TODO: Write the getMaze function
}