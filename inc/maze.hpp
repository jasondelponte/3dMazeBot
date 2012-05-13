#ifndef _MAZE_HPP_
#define _MAZE_HPP_

#include <stdlib.h>

/**
 * Definies the maze object that the entities will travel through.
 */
class Maze {
public:
	// Possible states of the cells that make up the maze
	enum eCell {
		CELL_SOLID,
		CELL_EMPTY,
		CELL_OCCUPIED,
		CELL_EXIT
	};

	// defines the size of a maze in all three deminsions.
	// Width coorisponds to X
	// Height coorisponds to Y
	// Depth coorisponds to Z
	struct tDimension {
		int width, height, depth;
		
		tDimension(int w=0, int h=0, int d=0): width(w), height(h), depth(d) {}
	};

	// Defines a location inside of the maze
	struct tCoord {
		int x, y, z;

		tCoord(int _x=0, int _y=0, int _z=0): x(_x), y(_y), z(_z) {}
	};

	// defines a specific cell in the maze. it contains its location and state
	struct tCell {
		tCoord coord;
		eCell state;

		tCell(eCell s = CELL_EMPTY, tCoord c=tCoord()): state(s), coord(c) {}
	};

	// defines the maze's grid
	struct tGrid {
		tCell*** layout;
		tDimension dim;
		tGrid(tDimension d=tDimension(), tCell*** l=NULL): dim(d), layout(l) {}
	};

	/**
	 * Initializes the maze and with a given size. Once it is initialized it is
	 * read to have its cells' state set.
	 * @param dim tDimension - Size of the maze.
	 */
	Maze(tDimension dim);

	/**
	 * Cleans up the maze object once when it is being deconstructed.
	 * This will delete all allocated memory needed to create
	 * the maze object
	 */
	~Maze();

	/**
	 * Returns a reference to the maze grid
	 * @returns reference to maze grid
	 */
	tGrid* getGrid() { return m_grid; }

	/**
	 * Returns if the grid specified  and is valid
	 * @returns state of the grid
	 */
	bool hasGrid() { return (m_grid != NULL && m_grid->layout != NULL); }

	/**
	 * returns if the coordinate provided are valid inside of the grid
	 * @param coord - a location in the grid
	 * @returns if the coordinate is valid
	 */
	bool isValidCoord(tCoord coord);

	/**
	 * Updates the cell located at the coordiantes with the state provided
	 * @param coord - Location of the cell to update
	 * @param state - Not state
	 * @returns success if the cell was updated
	 */
	bool updateCell(tCoord coord, eCell state);

private:
	// 3d size dimension of the maze.
	tGrid* m_grid;


	/**
	 * Creates and returns a new maze grid with the dimenions provided
	 * @param dim - the dimenional size of the grid.
	 * @returns a new grid object.
	 */
	tGrid* createGrid(tDimension dim);


	/**
	 * Delete the passed in maze grid and reset its pointer valuE to null.
	 * @param grid - reference to the pointer containing the grid
	 */
	void deleteGrid(tGrid* &grid);

};

#endif // !defined(_MAZE_HPP_)
