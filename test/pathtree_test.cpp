#include "pathtree_test.hpp"
#include "pathtree.hpp"
#include "maze.hpp"

#include <stdio.h>
#include <iostream>
#include <string>
#include <typeinfo>

using namespace std;

/**
 * Initialize the test, and also make sure to initialize the 
 * parent test unit as well.
 */
PathTreeTest::PathTreeTest(): TestUnit() {
	m_tests["PathTreeTest::TestCompareNodeToCell"] = &TestCompareNodeToCell;
	m_tests["PathTreeTest::TestAddCellsToPathTree"] = &TestAddCellsToPathTree;
	m_tests["PathTreeTest::TestAncstorCellSearch"] = &TestAncstorCellSearch;
	m_tests["PathTreeTest::TestChangeTreeRoot"] = &TestChangeTreeRoot;
	m_tests["PathTreeTest::TestSearchForNode"] = &TestSearchForNode;
}

/**
 * Delete the path tree object if it is set
 * @param pTestData container object of test data
 */
void PathTreeTest::afterEach(TestUnit::tTestData* pTestData) {
	if (pTestData->testObj != NULL) {
		delete (PathTree*)pTestData->testObj;
		pTestData->testObj = NULL;
	}

	TestUnit::afterEach(pTestData);
}

/**
 * Verifies a path node can be compared to a maze cell
 * @param pTestData - pointer to test container, not used for these tests
 * @returns error string if any.
 */
string PathTreeTest::TestCompareNodeToCell(TestUnit::tTestData* pTestData) {
	Maze::tCell cell1 = Maze::tCell(Maze::CELL_EMPTY, Maze::tCoord(1,1,1));
	Maze::tCell cell2 = Maze::tCell(Maze::CELL_EMPTY, Maze::tCoord(1,1,1));
	Maze::tCell cell3 = Maze::tCell(Maze::CELL_EMPTY, Maze::tCoord(2,2,2));

	PathTree* root = new PathTree(NULL, &cell1);

	if (*root != cell2) {
		delete root;
		return "Unable to compare two cells together of the same coords.";
	}

	if (*root == cell3) {
		delete root;
		return "Incorrectly matched cells with different coordinates.";
	}

	delete root;
	return "";
}


/**
 * Verify cells can be added to the path tree
 * @param pTestData - pointer to test container, not used for these tests
 * @returns error string if any.
 */
string PathTreeTest::TestAddCellsToPathTree(TestUnit::tTestData* pTestData) {
	Maze::tCell cell1 = Maze::tCell(Maze::CELL_EMPTY, Maze::tCoord(1,1,1));
	Maze::tCell cell2 = Maze::tCell(Maze::CELL_EMPTY, Maze::tCoord(2,2,2));
	Maze::tCell cell3 = Maze::tCell(Maze::CELL_EMPTY, Maze::tCoord(3,3,3));
	Maze::tCell dupCell = Maze::tCell(Maze::CELL_EMPTY, Maze::tCoord(3,3,3));

	PathTree* root = new PathTree(NULL, &cell1);

	root->addChild(&cell2);
	root->addChild(&cell3);

	PathTree::tChildren children = root->getChildren();
	if (*(children[0]) != cell2) {
		delete root;
		return "Child node 0 does not match cell 2";
	}
	if (*(children[1]) != cell3) {
		delete root;
		return "Child node 1 does not match cell 3";
	}
	if (root->addChild(&dupCell)) {
		delete root;
		return "Was able to add a duplicate cell to as a child to the node.";
	}

	delete root;
	return "";
}

/**
 * Verify that the tree can search for ancestors from a leaf
 * @param pTestData - pointer to test container, not used for these tests
 * @returns error string if any.
 */
string PathTreeTest::TestAncstorCellSearch(TestUnit::tTestData* pTestData) {
	Maze::tCell cell1 = Maze::tCell(Maze::CELL_EMPTY, Maze::tCoord(1,1,1));
	Maze::tCell cell2 = Maze::tCell(Maze::CELL_EMPTY, Maze::tCoord(2,2,2));
	Maze::tCell cell3 = Maze::tCell(Maze::CELL_EMPTY, Maze::tCoord(3,3,3));
	Maze::tCell cell4 = Maze::tCell(Maze::CELL_EMPTY, Maze::tCoord(4,4,4));

	PathTree* root = new PathTree(NULL, &cell1);
	root->addChild(&cell2);
	root->addChild(&cell4);

	PathTree::tChildren children = root->getChildren();
	if (!children[0]->addChild(&cell3)) {
		delete root;
		return "Failed to add a cell to a child.";
	}
	children = children[0]->getChildren();
	if (children[0]->addChild(&cell2)) {
		delete root;
		return "Incorrectly added a child cell which is an ancestor in this tree.";
	}
	if (!children[0]->addChild(&cell4)) {
		delete root;
		return "Failed to add cell which is not a ancestor of this branch, but another.";
	}

	delete root;
	return "";
}

/**
 * Verify that the root of the tree can be changed.
 * @param pTestData - pointer to test container, not used for these tests
 * @returns error string if any.
 */
string PathTreeTest::TestChangeTreeRoot(TestUnit::tTestData* pTestData) {
	Maze::tCell cell1 = Maze::tCell(Maze::CELL_EMPTY, Maze::tCoord(1,1,1));
	Maze::tCell cell2 = Maze::tCell(Maze::CELL_EMPTY, Maze::tCoord(2,2,2));
	Maze::tCell cell3 = Maze::tCell(Maze::CELL_EMPTY, Maze::tCoord(3,3,3));
	Maze::tCell cell4 = Maze::tCell(Maze::CELL_EMPTY, Maze::tCoord(4,4,4));
	Maze::tCell cell5 = Maze::tCell(Maze::CELL_EMPTY, Maze::tCoord(5,5,5));

	PathTree* root = new PathTree(NULL, &cell1);
	PathTree* last = root->addChild(&cell2);
	last = last->addChild(&cell3);
	last = last->addChild(&cell4);
	last = last->addChild(&cell5);

	last->makeRoot();

	if (*last != cell5 || last->getParent() != NULL) {
		delete last;
		delete root;
		return "The 5th node was not moved correctly.";
	}
	PathTree::tChildren children = last->getChildren();
	if (*(children[0]) != cell4 || *(children[0]->getParent()) != cell5) {
		delete last;
		return "The 4th node was not moved correctly.";
	}
	children = children[0]->getChildren();
	if (*(children[0]) != cell3 || *(children[0]->getParent()) != cell4) {
		delete last;
		return "The 3rd node was not moved correctly.";
	}
	children = children[0]->getChildren();
	if (*(children[0]) != cell2 || *(children[0]->getParent()) != cell3) {
		delete last;
		return "The 2nd node was not moved correctly.";
	}
	children = children[0]->getChildren();
	if (*(children[0]) != cell1 || *(children[0]->getParent()) != cell2) {
		delete last;
		return "The 1st node was not moved correctly.";
	}
	if (children[0]->getChildren().size() > 0) {
		delete last;
		return "The 1st node still has children. There should be none.";
	}

	delete last;
	return "";
}

/**
 * Verifty that we can search for a node in the tree.
 * @param pTestData - pointer to test container, not used for these tests
 * @returns error string if any.
 */
string PathTreeTest::TestSearchForNode(TestUnit::tTestData* pTestData) {
	Maze::tCell cell1 = Maze::tCell(Maze::CELL_EMPTY, Maze::tCoord(1,1,1));
	Maze::tCell cell2 = Maze::tCell(Maze::CELL_EMPTY, Maze::tCoord(2,2,2));
	Maze::tCell cell3 = Maze::tCell(Maze::CELL_EMPTY, Maze::tCoord(3,3,3));
	Maze::tCell cell4 = Maze::tCell(Maze::CELL_EMPTY, Maze::tCoord(4,4,4));
	Maze::tCell cell5 = Maze::tCell(Maze::CELL_EMPTY, Maze::tCoord(5,5,5));

	PathTree* root = new PathTree(NULL, &cell1);
	PathTree* last = root->addChild(&cell2);
	root->addChild(&cell5);
	last = last->addChild(&cell3);
	last = last->addChild(&cell4);
	last = last->addChild(&cell5);

	PathTree* node = root->getNode(cell3);
	if (node == NULL || *node != cell3) {
		delete root;
		return "Failed to find cell 3 in tree.";
	}

	node = root->getNode(cell5);
	if (node == NULL || *node != cell5) {
		delete root;
		return "Failed to find cell 5 in tree.";
	}

	return "";
}
