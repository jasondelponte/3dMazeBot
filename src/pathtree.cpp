#include "pathtree.hpp"

#include <queue>

using namespace std;

/**
 * Initializes the node
 * @param parent the parent node of this child
 * @param c the cell to set the node to represent
 * @param children, list of children to be attached to this node
 */
PathTree::PathTree(PathTree* p, Maze::tCell* c, PathTree::tChildren ch): m_parent(p), m_cell(c), m_children(ch), m_meta(VALID) {}

/** 
 * Takes care of deleting all children nodes still attached to this node
 */
PathTree::~PathTree() {
	// Delete all children still assigned to this node
	if (m_children.size() == 0) { return; }
	tChildren::iterator it;
	for (it = m_children.begin(); it != m_children.end(); it++) {
		PathTree* child = *it;
		if (child != NULL) {
			delete child;
			(*it) = NULL;
		}
	}
	m_children.clear();
}

/**
 * Appends a cell to this node as a child if it is not already
 * an ancestor of this node. It also makes sure that the cell adding
 * is not the same as this node's cell, and isn't already a sibling of
 * this node.
 * @param the cell to add as a child to this node
 * @returns the newly added child.
 */
PathTree* PathTree::addChild(Maze::tCell* pCell) {
	if (hasAncestor(*pCell) || *this == *pCell || hasSibling(*pCell)) { return NULL; }

	PathTree* pChild = new PathTree(this, pCell);
	m_children.push_back(pChild);

	return pChild;
}

/**
 * Appends a new node to this node as a child
 * @param the node to add as a child to this node
 * @returns the newly added child.
 */
PathTree* PathTree::addChild(PathTree* pChild) {
	pChild->detach();
	pChild->m_parent = this;
	m_children.push_back(pChild);
	return pChild;
}

/**
 * Removes the parent reference from this node
 * while also removing it from the parent's child list
 */
void PathTree::detach() {
	if (m_parent != NULL) {
		m_parent->removeChild(this);
	}
	m_parent = NULL;
}

/**
 * Removes the specified child from its parent's list of children
 * @param child node to deref
 */
void PathTree::removeChild(PathTree* pChild) {
	tChildren::iterator it;
	for (it = m_children.begin(); it != m_children.end(); it++) {
		PathTree* pNode = *it;
		if (pNode == pChild) {
			m_children.erase(it);
			break;
		}
	}
}

/*
 * Searches up the tree looking if the cell specified already exists
 * as a parent to the node provided.
 * @param node to start from
 * @param cell to search for
 * @returns if the cell was found as an ancestor
 */
bool PathTree::hasAncestor(Maze::tCell cell) {
	if (m_parent == NULL) { return false; }

	PathTree* pNode = this->m_parent;
	while (pNode != NULL) {
		if (*pNode == cell) {
			return true;
		}

		pNode = pNode->m_parent;
	}

	return false;
}

/**
 * Searches the children of the this node to make sure
 * this cell doesn't exist as a sibling
 * @param cell to search for
 * @returns true if this cell exists as a sibling
 */
bool PathTree::hasSibling(Maze::tCell cell) {
	if (m_children.size() == 0) { return false; }

	tChildren::const_iterator cIt;
	for (cIt = m_children.begin(); cIt != m_children.end(); cIt++) {
		PathTree* pNode = *cIt;
		if (*pNode == cell) {
			return true;
		}
	}

	return false;
}

/**
 * Updates this Node's parent to be a child. This change cascades up the
 * true until the original root node is now a child.
 * NOTE: Chaning the root will make it possible for loops in the search tree to occure
 * it won't create circular lookups, but the worst case branch could hit
 * this new root twice if it already contined it as a child.
 * @returns a reference to this node which is now the root of the tree.
 */
PathTree* PathTree::makeRoot() {
	if (m_parent == NULL) { return this; }

	PathTree* newParent = NULL;
	PathTree* oldParent = m_parent;
	PathTree* node = this;
	while (node != NULL) {
		if (oldParent != NULL) {
			oldParent->removeChild(node);
			node->m_children.push_back(oldParent);
		}
		node->m_parent = newParent;

		newParent = node;
		node = oldParent;
		if (oldParent != NULL) {
			oldParent = oldParent->m_parent;
		}
	}

	return this;
}

/**
 * Travels up the tree and returns the root node
 * @returns root tree node. NULL is returned if we're unable to find the root node some how.
 */
PathTree* PathTree::getRoot() {
	if (m_parent == NULL) { return this; }

	PathTree* parent = m_parent;
	while (parent != NULL) {
		if (parent->m_parent == NULL) { return parent; }

		parent = parent->m_parent;
	}

	return NULL;
}

/**
 * returns the child cell specified as a child using breath first search
 * @param child node being serached for.
 * @returns the child if found, null otherwise
 */
PathTree* PathTree::getNode(Maze::tCell cell) {
	return getNode(cell.coord);
}

/**
 * Searchs through the tree looking for the node containing the coord
 * using breath first search.
 * @param coord the location of the cell we're looking for
 * @returns the node if found.
 */
PathTree* PathTree::getNode(Maze::tCoord coord) {
	if (*this == coord) { return this; }

	queue<PathTree*> nodeQ;
	nodeQ.push(this);

	while (!nodeQ.empty()) {
		PathTree* node = nodeQ.front();
		nodeQ.pop();

		if (*node == coord) { return node; }

		tChildren::const_iterator cIt;
		for (cIt = node->m_children.begin(); cIt != node->m_children.end(); cIt++) {
			PathTree* child = *cIt;
			if (*child == coord) { return child; }

			nodeQ.push(child);
		}
	}

	return NULL;
}
