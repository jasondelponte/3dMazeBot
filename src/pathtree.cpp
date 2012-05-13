#include "pathtree.hpp"



/**
 * Initializes the node
 * @param parent the parent node of this child
 * @param c the cell to set the node to represent
 * @param children, list of children to be attached to this node
 */
PathTree::PathTree(PathTree* p, Maze::tCell* c, PathTree::tChildren ch): m_parent(p), m_cell(c), m_children(ch) {}

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
 * @returns if the child was dded.
 */
bool PathTree::addChild(Maze::tCell* pCell) {
	if (hasAncestor(*pCell) || *this == *pCell || hasSibling(*pCell)) { return false; }

	m_children.push_back(new PathTree(this, pCell));

	return true;
}

/**
 * Appends a new node to this node as a child
 * @param the node to add as a child to this node
 * @returns if the child was dded.
 */
void PathTree::addChild(PathTree* pChild) {
	pChild->detach();
	pChild->m_parent = this;
	m_children.push_back(pChild);
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