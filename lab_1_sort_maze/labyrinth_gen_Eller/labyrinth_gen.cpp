#include "pch.h"
#include <iostream>
#include <cstdlib> //  rand() и srand()


struct Cell {
	int val = 0;
	int rEdge = 0;
	int dEdge = 0;
};

void rowGenerate(Cell** m_cell, int rowNum);
void rightEdgeGenerate(Cell** m_cell, int rowNum);
void downEdgeGenerate(Cell** m_cell, int rowNum);
void nextRowGenerate(Cell** m_cell, int rowNum);
void endMaze(Cell** m_cell, int rowNum);
void mazeGenerate(Cell** m_cell);
void mazeGraph(Cell** m_cell);
void LogViever(char const* point, Cell* logCell);

const size_t kMazeSize = 15;

int main()
{
	std::srand(1);

	Cell** mtx_cell = new Cell*[kMazeSize];

	for (int it = 0; it < kMazeSize; ++it) {
		mtx_cell[it] = new Cell[kMazeSize];
	}

	mazeGenerate(mtx_cell);
	mazeGraph(mtx_cell);

	return 0;
}

void rowGenerate(Cell** m_cell, int rowNum) {
	static int initVal = 0;
	for (int it = 0; it < kMazeSize; ++it) {
		if (m_cell[rowNum][it].val == 0) {
			m_cell[rowNum][it].val = ++initVal;
		}
		/*else {
			initVal = m_cell[rowNum][it].val;
		}*/
		LogViever("rowGenerate: ", (*(m_cell + rowNum) + it));

	}
	//std::cout << "\n";

	rightEdgeGenerate(m_cell, rowNum);
	downEdgeGenerate(m_cell, rowNum);
}


void rightEdgeGenerate(Cell** m_cell, int rowNum) {
	int randEdge;
	for (int it = 0; it < kMazeSize; ++it) {
		if (m_cell[rowNum][it].val == m_cell[rowNum][it + 1].val) {
			m_cell[rowNum][it].rEdge = 1;
		}
		else {
			randEdge = rand() % 2;
			if (randEdge) {
				m_cell[rowNum][it].rEdge = randEdge;
			}
			else {
				m_cell[rowNum][it + 1].val = m_cell[rowNum][it].val;
			}
		}
		//LogViever("rEdgeGen: ", (*(m_cell + rowNum) + it));
	}
	//std::cout << "\n";
	m_cell[rowNum][kMazeSize - 1].rEdge = 1;
}

void downEdgeGenerate(Cell** m_cell, int rowNum) {
	int ctDownEdge = 0;
	int ctCell = 0;
	int curCell = m_cell[rowNum][0].val;
	for (int it = 0; it < kMazeSize; ++it) {
		if (curCell == m_cell[rowNum][it].val) {
			++ctCell;
		}
		else {
			ctCell = 1;
			ctDownEdge = 0;
			curCell = m_cell[rowNum][it].val;
		}
		if (ctDownEdge < ctCell - 1) {
			m_cell[rowNum][it].dEdge = rand() % 2;
			ctDownEdge += m_cell[rowNum][it].dEdge;
		}
		//LogViever("dEdgeGen: ", (*(m_cell + rowNum) + it));
	}
	//std::cout << "\n";
}


void nextRowGenerate(Cell** m_cell, int rowNum) {
	for (int it = 0; it < kMazeSize; ++it) {
		m_cell[rowNum][it].val = m_cell[rowNum - 1][it].dEdge ? 0 : m_cell[rowNum-1][it].val;
		m_cell[rowNum][it].dEdge = 0; 
		m_cell[rowNum][it].rEdge = 0;
		//LogViever("NEXT ROW: ", (*(m_cell + rowNum) + it));
	}
	
	//std::cout << "\n";
	rowGenerate(m_cell, rowNum);
}

void endMaze(Cell** m_cell, int rowNum) {
	for (int it = 0; it < kMazeSize; ++it) {
		m_cell[rowNum][it].val = m_cell[rowNum - 1][it].val;
		m_cell[rowNum][it].dEdge = 1;
		m_cell[rowNum][it].rEdge = m_cell[rowNum - 1][it].rEdge;
	}
	
	int endCellVal = m_cell[rowNum][0].rEdge;

	for (int it = 1; it < kMazeSize; ++it) {
		if ((m_cell[rowNum][it].rEdge == 1) && (m_cell[rowNum][it].val != endCellVal)) {
			m_cell[rowNum][it].val = endCellVal;
			m_cell[rowNum][it].rEdge = 0;
		}
		else {
			m_cell[rowNum][it].val = endCellVal;
		}
	}
	m_cell[rowNum][kMazeSize-1].rEdge = 1;
	
	//std::cout << "\n";
	for (int it = 0; it < kMazeSize; ++it) {
		//LogViever("endMaze: ", (*(m_cell + rowNum) + it));
	}

}

void mazeGenerate(Cell** m_cell) {
	rowGenerate(m_cell, 0);			//Init row
	for (int it = 1; it < kMazeSize - 1; ++it) {
		nextRowGenerate(m_cell, it);
	}
	endMaze(m_cell, kMazeSize-1);
}


void mazeGraph(Cell** m_cell) {
	for (int it = 0; it < kMazeSize; ++it) {
		std::cout << "._";
	}
	std::cout << "\n";
	for (int row = 0; row < kMazeSize; ++row) {
		std::cout << "|";
		for (int col = 0; col < kMazeSize; ++col) {
			if (m_cell[row][col].dEdge) {
				std::cout << "_";
			}
			else {
				std::cout << " ";
			}
			if (m_cell[row][col].rEdge) {
				std::cout << "|";
			}
			else {
				std::cout << ".";
			}
		}
		std::cout << "\n";
	}
}

void LogViever(char const* point, Cell* logCell) {
	std::cout << point << "\n";
	std::cout << "cell val: " << logCell->val << " ";
	std::cout << "cell rEdge: " << logCell->rEdge << " ";
	std::cout << "cell dEdge: " << logCell->dEdge << " ";
	std::cout << "\n";
}