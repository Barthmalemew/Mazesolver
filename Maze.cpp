// Tries to solve a maze using a recursive solution
// Shows path through the maze if one exists
// Kevin Anderson, Aden Yu, Ariadna Soria-Huerta, Thomas Menter, Timothy Huff, Jan Arroyo

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
* Will clean up the dead spaces of the char array so only the solution path remains.
*/
void cleanUp(char maze[][MAXCOLS], int startX, int startY);

/*
* findPath will find the path to the solution of the maze if possible.
* count keeps track of how many recursive functions where called.
*/
bool findPath(char maze[][MAXCOLS], int startX, int startY, int &count);

/*
* initMaze will initialize char array so that all positions are empty spaces.
*/
void initMaze(char maze[][MAXCOLS]);

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
	char c[FILENAMESIZE];

	int x;
	int y;
	int count = 0;

	bool possible = false;

	initMaze(maze);

	getMaze(maze, x, y);

	display(maze);

	printf("Press Enter to Solve the Maze");
	printf("\n");
	cin.getline(c, FILENAMESIZE);

	int i = 0;

	//decides if user wants to solve the maze or 
	//if user input results in an exit. 
	while (c[i] != '\0')
	{
		i++;
		if (i > 9)
		return 0;
	}

	possible = findPath(maze, x, y, count);

	cleanUp(maze, x, y);

	display(maze);

	//explicitly prints to the user if the maze was solvable or not
	if (!possible)
	{
		printf("\n\t\tNo solution to this maze -- %d recursive calls\n", count);
	}
	else
	{
		printf("\n\t\tSolution found! -- %d recursive calls", count);
	}		

	printf("\n\npress Enter again to exit\n");
	cin.get();

	return 0;
}


// TODO: Write the code for the remaining functions that you need

//displays the intended output to be viewed by the user. 
void display(const char maze[][MAXCOLS])
{
	// system("cls") clears the screen; only works on Windows machines
	// You will probably need to comment this out if working on
	// a non-Windows machine
	system("cls");

	for (int i = 0; i < MAXROWS; i++)
	{
		for (int j = 0; j < MAXCOLS; j++)
		{
			{
				printf("%c", maze[i][j]);
			}  
		}
		printf("\n");
	}
}

//function to get maze from user selected file and inserts it into the maze array
void getMaze(char maze[][MAXCOLS], int& startX, int& startY)
{
	int row = 0;

	char input[FILENAMESIZE];
	char line[MAXCOLS];

	printf("Enter the name of a TXT file containing the maze(don't enter 'txt'): ");
	printf("\n");
	cin.getline(input, FILENAMESIZE);
	snprintf(input + strlen(input), FILENAMESIZE, "%s", ".txt");

	ifstream inFile(input);

	if (!inFile.is_open())
	{
		cerr << "ERROR: Input file cannot be opened.";
		exit(1);
	}

	while (row < MAXROWS && !inFile.eof())
	{
		//stops getting characters past the column length of the array
		//and still gets the characters prior to the failbit.
		if (inFile.fail())
		{
			inFile.clear();
			inFile.ignore(numeric_limits<streamsize>::max(), '\n');
		}

		inFile.getline(line, MAXCOLS);

		//copies characters from line array taken from each line of the file
		//and places a \0 at the MAXCOL length of the maze.
		snprintf(maze[row], MAXCOLS, "%-*s", MAXCOLS, line);

		for (int i = 0; i < MAXCOLS; i++)
		{
			if (maze[row][i] == WALLINFILE)
			{
				maze[row][i] = WALL;
			}
			//passes by reference to the main funtion the position of the start character.
			else if (maze[row][i] == START)
			{
				startX = row;
				startY = i;
			}
		}
	row++;
	}
}

//initializes maze to avoid graphical errors when a '\n' is pressed at the start of a line
//or when the line doesnt end at a wall.
void initMaze(char maze[][MAXCOLS])
{
	for (int i = 0; i < MAXROWS; i++)
	{
		for (int j = 0; j < MAXCOLS; j++)
		{
			maze[i][j] = ' ';
		}
	}
}


//recursive function to find if the maze is solvable or not
//and tracks a path from the start to the exit.
bool findPath(char maze[][MAXCOLS], int startX, int startY, int &count)
{
	count++;

	if (startX < 0 || startX >= MAXROWS || startY < 0 || startY >= MAXCOLS)
	{
		return false;
	}

	if (maze[startX][startY] == DEST)
	{
		return true;
	}

	if (maze[startX][startY] == WALL || maze[startX][startY] != EMPTY && maze[startX][startY] != START)
	{
		return false;
	}
	
	else 
	{
		maze[startX][startY] = PATH;
		
		if (findPath(maze, startX - 1, startY, count))
			return true;

		if (findPath(maze, startX, startY + 1, count))
			return true;
		
		if (findPath(maze, startX, startY - 1, count))
			return true;

		if (findPath(maze, startX + 1, startY, count))
			return true;

		maze[startX][startY] = DEAD;
		return false;
	}
}

// Will go through maze array to clean up dead spaces by replacing 
// them with empty spaces so only the solution path remains.
void cleanUp(char maze[][MAXCOLS], int startX, int startY)
{
	maze[startX][startY] = START;

	for (int i = 0; i < MAXROWS; i++)
	{
		for (int j = 0; j < MAXCOLS; j++)
		{
			if (maze[i][j] == DEAD)
			{
				maze[i][j] = EMPTY;
			}
		}
	}
}
