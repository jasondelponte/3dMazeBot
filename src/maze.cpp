#include "maze.hpp"



/**
 * Initializes the maze and with a given size. Once it is initialized it is
 * read to have its cells' state set.
 * @param dim tDimension - Size of the maze.
 */
Maze::Maze(tDimension dim) {
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
			for (int c=0; c < dim.depth; c++) {

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
