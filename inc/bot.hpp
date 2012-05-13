#ifndef _BOT_HPP_
#define _BOT_HPP_

#include "maze.hpp"

class Bot {
public:
	Bot(Maze::tCoord loc);

private:
	Maze::tCoord m_loc;
};

#endif // !defined(_BOT_HPP_)