#include "maze.hpp"

#include <iostream>

using namespace std;

/**
 * Initializes the maze and with a given size. Once it is initialized it is
 * read to have its cells' state set.
 * @param dim tDimension - Size of the maze.
 */
Maze::Maze(tDimension dim): m_grid(NULL) {
	m_grid = createGrid(dim);
}

/**
 * Cleans up the maze object once when it is being deconstructed.
 * This will delete all allocated memory needed to create
 * the maze object
 */
Maze::~Maze() {
	if (m_grid != NULL) {
		deleteGrid(m_grid);
	}
}

/**
 * Updates the cell located at the coordiantes with the state provided
 * @param coord - Location of the cell to update
 * @param state - Not state
 * @returns success if the cell was updated
 */
bool Maze::updateCell(Maze::tCoord coord, Maze::eCell state) {
	if (!isValidCoord(coord)) { return false; }

	m_grid->layout[coord.x][coord.y][coord.z].state = state;

	return true;
}

/**
 * returns if the coordinate provided are valid inside of the grid
 * @param coord - a location in the grid
 * @returns if the coordinate is valid
 */
bool Maze::isValidCoord(Maze::tCoord coord) {
	if (!hasGrid()) { return false; }
	if (coord.x < 0 || coord.y < 0 || coord.z < 0) { return false; }
	if (coord.x >= m_grid->dim.width || coord.y >= m_grid->dim.height || coord.z >= m_grid->dim.depth) { return false; }

	return true;
}

/**
 * Prints out the layer of the maze along the Y axis of the X/Z plain.
 * If the layer is invalid (above or below the maze) nothing will be printed.
 * @param layer - the section of the maze to be printed to stdout
 */
void Maze::printLayer(int layer) {
	cout << "Told to print layer " << layer << endl;
}

/**
 * Creates and returns a new maze grid with the dimenions provided
 * @param dim - the dimenional size of the grid.
 * @returns a new grid object.
 */
Maze::tGrid* Maze::createGrid(tDimension dim) {
	// Create all the cells
	tCell*** layout = new tCell**[dim.width];
	for (int x=0; x < dim.width; x++) {
		layout[x] = new tCell*[dim.height];
		for (int y=0; y < dim.height; y++) {
			layout[x][y] = new tCell[dim.depth];
			// Initialize the cell coords
			for (int z=0; z < dim.depth; z++) {
				layout[x][y][z] = tCell(CELL_EMPTY, tCoord(x, y, z));
			}
		}
	}

	return new tGrid(dim, layout);
;
}

/**
 * Delete the passed in maze grid and reset its pointer valuE to null.
 * @param grid - reference to the pointer containing the grid
 * @param dim - dimensions of the grid to be removed
 */
void Maze::deleteGrid(tGrid* &grid) {
	if (grid == NULL) {
		return;
	}

	if (grid->layout == NULL) {
		for (int x=0; x < grid->dim.width; x++) {
			for (int y=0; y < grid->dim.height; y++) {
				delete[] grid->layout[x][y];
			}
			delete[] grid->layout[x];
		}
		delete[] grid->layout;
		grid->layout = NULL;
	}

	delete grid;
	grid = NULL;
}
