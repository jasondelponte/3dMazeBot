#ifndef _PATHTREENODE_HPP_
#define _PATHTREENODE_HPP_

#include "maze.hpp"

#include <vector>


class PathTree {
public:
	// Defines the list of children in the tree
	typedef std::vector<PathTree*> tChildren;

	/**
	 * Initializes the node
	 * @param parent the parent node of this child
	 * @param c the cell to set the node to represent
	 * @param children, list of children to be attached to this node
	 */
	PathTree(PathTree* p=NULL, Maze::tCell* c=NULL, tChildren ch=tChildren());

	/** 
	 * Takes care of deleting all children nodes still attached to this node
	 */
	~PathTree();

	/**
	 * Appends a cell to this node as a child if it is not already
	 * an ancestor of this node. It also makes sure that the cell adding
	 * is not the same as this node's cell.
	 * @param the cell to add as a child to this node
	 * @returns if the child was dded.
	 */
	bool addChild(Maze::tCell* pChild);

	/**
	 * Appends a new node to this node as a child
	 * @param the node to add as a child to this node
	 * @returns if the child was dded.
	 */
	void addChild(PathTree* pChild);

	/**
	 * Removes the parent reference from this node
	 * while also removing it from the parent's child list
	 */
	void detach();

	/**
	 * Removes the specified child from its parent's list of children
	 * @param child node to deref
	 */
	void removeChild(PathTree* pChild);

	/*
	 * Searches up the tree looking if the cell specified already exists
	 * as a parent to the node provided.
	 * @param cell to search for
	 * @returns if the cell was found as an ancestor
	 */
	bool hasAncestor(Maze::tCell cell);

	/**
	 * Searches the children of the parent node to makesure
	 * this cell doesn't exist as a sibling
	 * @param cell to search for
	 * @returns true if this cell exists as a sibling
	 */
	bool hasSibling(Maze::tCell cell);

	/**
	 * Compares this Node if contains the cell provided
	 * @param cell to compare the coordinates against
	 * @returns if same coordinates
	 */
	bool operator==(const Maze::tCell cell) {
		return (m_cell->coord == cell.coord);
	}

	/**
	 * Compares this Node is not the same as the cell provided
	 * @param cell to compare the coordinates against
	 * @returns if same coordinates
	 */
	bool operator!=(const Maze::tCell cell) {
		return (m_cell->coord != cell.coord);
	}

	/**
	 * Returns the list of children this node has
	 * @returns list of children
	 */
	tChildren getChildren() { return m_children; }

private:
	Maze::tCell* m_cell;

	PathTree* m_parent;
	tChildren m_children;
};

#endif // !defined (_PATHTREENODE_HPP_)