#ifndef _MAZE_HPP_
#define _MAZE_HPP_


enum eCell {
	CELL_SOLID,
	CELL_EMPTY,
	CELL_OCCUPIED
};

struct tDimension {
	int height, width, depth;
	
	tDimension(int h=0, int w=0, int d=0): height(h), width(w), depth(d) {}
};

struct tCoord {
	int x, y, z;

	tCoord(int _x=0, int _y=0, int _z=0): x(_x), y(_y), z(_z) {}
};

struct tCell {

};

class Maze {
private:
	tDimension m_dim;

public:
	Maze(int layers);
	void buildMaze();
};

#endif // !defined(_MAZE_HPP_)
