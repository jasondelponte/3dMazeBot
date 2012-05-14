#ifndef _PATHTREENODE_HPP_
#define _PATHTREENODE_HPP_

#include "maze.hpp"

#include <vector>


class PathTree {
public:
	// Defines the list of children in the tree
	typedef std::vector<PathTree*> tChildren;
	enum eCellMeta {
		VALID,
		DEAD_END
	};

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
	 * @returns the newly added child.
	 */
	PathTree* addChild(Maze::tCell* pChild);

	/**
	 * Appends a new node to this node as a child
	 * @param the node to add as a child to this node
	 * @returns the newly added child.
	 */
	PathTree* addChild(PathTree* pChild);

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

	/**
	 * Updates this Node's parent to be a child. This change cascades up the
	 * true until the original root node is now a child.
	 * NOTE: Chaning the root will make it possible for loops in the search tree to occure
	 * it won't create circular lookups, but the worst case branch could hit
	 * this new root twice if it already contined it as a child.
 	 * @returns a reference to this node which is now the root of the tree
	 */
	PathTree* makeRoot();

	/**
	 * Travels up the tree and returns the root node
 	 * @returns root tree node. NULL is returned if we're unable to find the root node some how.
	 */
	PathTree* getRoot();

	/**
	 * returns the child cell specified as a child using breath first search
	 * @param child node being serached for.
	 * @returns the child if found, null otherwise
 	 */
	PathTree* getNode(Maze::tCell cell);

	/**
	 * Searchs through the tree looking for the node containing the coord
	 * using breath first search.
	 * @param coord the location of the cell we're looking for
	 * @returns the node if found.
	 */
	PathTree* getNode(Maze::tCoord coord);

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
	 * @returns true if same coordinates
	 */
	bool operator==(const Maze::tCell cell) {
		return (m_cell->coord == cell.coord);
	}

	/**
	 * Compares this Node is not the same as the cell provided
	 * @param cell to compare the coordinates against
	 * @returns true if different coordinates
	 */
	bool operator!=(const Maze::tCell cell) {
		return (m_cell->coord != cell.coord);
	}

	/**
	 * Compares this Node is the same as the coord provided
	 * @param coord to compare the coordinates against
	 * @returns true if same coordinates
	 */
	bool operator==(const Maze::tCoord coord) {
		return (m_cell->coord == coord);
	}

	/**
	 * Compares this Node is not the same as the coord provided
	 * @param coord to compare the coordinates against
	 * @returns true if same coordinates
	 */
	bool operator!=(const Maze::tCoord coord) {
		return (m_cell->coord != coord);
	}

	/**
	 * Returns the parent of this node if there is one
	 * @returns parent
	 */
	 PathTree* getParent() { return m_parent; }

	/**
	 * Returns the list of children this node has
	 * @returns list of children
	 */
	tChildren getChildren() { return m_children; }

	/**
	 * Sets meta data about the cell this node is pointing to.
	 * @params meta extra information about the cell
	 */
	void setMeta(eCellMeta meta) { m_meta = meta; }
	
	/**
	 * returns the meta data stored on this cell
	 */
	eCellMeta getMeta() { return m_meta; }

	/**
	 * Returns the cell pointed to by this node
	 * @returns cell refernce
	 */
	Maze::tCell* getCell() { return m_cell; }

	/**
	 * returns the location in the grid of the cell contained at this node
	 * @returns coordinate of the cell in the grid
	 */
	Maze::tCoord getLoc() { return m_cell->coord; }

private:
	Maze::tCell* m_cell;
	eCellMeta m_meta;

	PathTree* m_parent;
	tChildren m_children;
};

#endif // !defined (_PATHTREENODE_HPP_)
