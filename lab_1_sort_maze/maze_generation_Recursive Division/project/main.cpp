#include <iostream>
#include <cstdlib>	//rand

const int kMazeSize = 30;

enum Orientation {
	HORIZONTAL,
	VERTICAL
};
struct Cell {
	bool rightEdge = 0;
	bool downEdge = 0;
};

void FieldDivider(Cell** maze_filed, int x0,int y0, int width, int height, Orientation _orientation);
void Mapper(Cell** maze_filed, int wx, int wy, int px, int py, int width, int height, Orientation _orientation);
Orientation ChooseOrientation(int width, int height);
int mrand(int rBorder, int lBorder = 0);
void mazeGraph(Cell** maze_filed);
void LogViever(char const* point, Cell** maze_filed, const size_t size);


int main()
{
	std::srand(1);
	Cell** maze = new Cell*[kMazeSize];
	for (int it = 0; it < kMazeSize; ++it) {
		maze[it] = new Cell[kMazeSize];
	}

	FieldDivider(maze, 0, 0, kMazeSize, kMazeSize, ChooseOrientation(kMazeSize, kMazeSize));
	mazeGraph(maze);

	return 0;
}


Orientation ChooseOrientation(int width, int height) {
	if (width < height) {
		return HORIZONTAL;
	}
	else if(width > height) {
		return VERTICAL;
	}
	else {
		return (mrand(2) ? HORIZONTAL : VERTICAL);
	}
}

void FieldDivider(Cell** maze_filed, int x0, int y0, int width, int height, Orientation _orientation) {
	if (width < 2 || height < 2) {
		return;
	}
	int horisontal = (_orientation == HORIZONTAL);
	int wall_x = ( x0 + (horisontal ? 0 : mrand(width-2)) );		//mrand(width-2,1)
	int wall_y = ( y0 + (horisontal ? mrand(height-2) : 0) );			//mrand(height-2,1)

	int pass_x = (wall_x + (horisontal ? mrand(width) : 0));		//?
	int pass_y = (wall_y + (horisontal ? 0 : mrand(height)));		//?

	Mapper(maze_filed, wall_x, wall_y, pass_x, pass_y, width, height, _orientation);
	//LogViever("AfterMapper: ", maze_filed, kMazeSize);
	//mazeGraph(maze_filed);

	int nx0 = x0;
	int ny0 = y0;
	int nwidth0  = (horisontal ? width : (wall_x - x0 + 1));
	int nheight0 = (horisontal ? (wall_y - y0 + 1) : height);
	
	int nx1 = (horisontal ? x0 : (wall_x + 1));
	int ny1 = (horisontal ? wall_y + 1 : y0);
	int nwidth1  = (horisontal ? width : (x0 + width - wall_x - 1));
	int nheight1 = (horisontal ? (y0+height-wall_y-1) : height);

	FieldDivider(maze_filed, nx0, ny0, nwidth0, nheight0, ChooseOrientation(nwidth0, nheight0));
	FieldDivider(maze_filed, nx1, ny1, nwidth1, nheight1, ChooseOrientation(nwidth1, nheight1));

}

void Mapper(Cell** maze_filed, int wx, int wy, int px, int py, int width, int height, Orientation _orientation) {
	int horisontal = (_orientation == HORIZONTAL);
	int length = horisontal ? width : height;
	int dx     = horisontal ? 1 : 0;
	int dy     = horisontal ? 0 : 1;

	for (int it = 0; it < length; ++it) {
		if (maze_filed[wx][wy].rightEdge == 0) {
			maze_filed[wx][wy].rightEdge = (wx != px || wy != py) ? dx : 0;
		}
		if (maze_filed[wx][wy].downEdge == 0) {
			maze_filed[wx][wy].downEdge = (wx != px || wy != py) ? dy : 0;
		}
		wx += dx;
		wy += dy;
	}
}


int mrand(int rBorder, int lBorder){
	if ((rBorder - lBorder) == 0)
		return 0;
	else
		return (lBorder + rand()%(rBorder - lBorder));
}

void mazeGraph(Cell** maze_filed) {
	for (int it = 0; it < kMazeSize; ++it) {
		std::cout << "._";
	}
	std::cout << "\n";
	for (int row = 0; row < kMazeSize; ++row) {
		std::cout << "|";
		for (int col = 0; col < kMazeSize; ++col) {
			if (row == kMazeSize - 1) {
				std::cout << "_";
			}
			else {
				std::cout << (maze_filed[row][col].downEdge ? "_" : " ");
			}

			if (col == kMazeSize - 1) {
				std::cout << "|";
			}
			else {
				std::cout << (maze_filed[row][col].rightEdge ? "|" : ".");
			}
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}

void LogViever(char const* point, Cell** maze_filed, const size_t size) {
	std::cout << point << "\n";
	for (int row = 0; row < size; ++row) {
		for (int col = 0; col < size; ++col) {
			std::cout << "{" << maze_filed[row][col].rightEdge << ", " << maze_filed[row][col].downEdge << "} ";
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}