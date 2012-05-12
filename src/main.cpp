#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "bot.hpp"
#include "maze.hpp"
#include "game.hpp"

using namespace std;


/**
 * Makes sure the input arguments are valid before
 * allowing the rest of the program to run.
 * @param argc int - Number of command line arguments
 * @param argv char*[] - Array of strings containing the input arguments
 * @returns bool - True if the input is valid, false otherwise
 */
bool validateInput(int argc, char* argv[]) {
	if (argc != 2) {
		cerr << "Missing maze config file" << endl;
		return false;
	} 

	struct stat sb;
	// Make sure the input file exists, and its not a directory.
	if (stat(argv[1], &sb) != 0 || !S_ISREG(sb.st_mode) || S_ISDIR(sb.st_mode)) {
		cerr << "Maze config file not found or not a file." << endl;
		return false;
	}	

	return true;
}


/**
 * Main entry, creats and starts the game.  Will exit on error parsing the
 * input, or when the game finishes.
 * @param argc int - Number of command line arguments
 * @param argv char*[] - Array of strings containing the input arguments
 */
int main(int argc, char* argv[]) {
	if (!validateInput(argc, argv)) {
		cout << "Usage: " << argv[0] << " <inputfile>" << endl;
		return EXIT_FAILURE;
	};

	EnvConfig cfg;
	// Parses the input file and builds sets up the environment so 
	// the game maze can be built.
	if (!cfg.parseEnv(argv[1])) {
		cerr << "Failed to load environment config file" << endl;
		return EXIT_FAILURE;
	}


	Game game;
	// We need to build the environment for the game.  This includes
	// placing the bot, and building the maze and exit.
	game.buildMaze(cfg);

	// We've build the game environment. The maze, and bot have been
	// created. Time to find our way out!  We'll wait here until the
	// game finishes.
	game.run();

	return EXIT_SUCCESS;
}
