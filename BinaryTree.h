#pragma once

#ifndef BINARYTREE_H
#define BINARYTREE_H

#include "BinaryNode.h"
#include "Queue.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
template <class ItemType>
class BinaryTree
{
protected:
	BinaryNode<ItemType>* rootPtr;
	int count;
	int level;
public:
	// "admin" functions
	BinaryTree() { rootPtr = NULL; count = 0; }
	BinaryTree(const BinaryTree<ItemType> & tree) { rootPtr = copyTree(tree.rootPtr); }
	virtual ~BinaryTree() { destroyTree(this->rootPtr); }
	// all commong functions for BinaryTree

	bool isEmpty() const { return count == 0; }
	int size() const { return count; }
	void clear() { destroyTree(rootPtr); rootPtr = 0; count = 0; }
	void inOrder(void visit(ItemType &)) const { _inorder(visit, rootPtr); }
	void breadthTraversal(void visit(ItemType &)) const { _breadth(visit, rootPtr); }
	void printTree(void indent(ItemType &, int), int level) const { _printTree(indent, rootPtr, level); }
	void printToFile(void visit(ItemType &)) const;


	// abstract functions to be implemented by derived class
	virtual bool insert(const ItemType & newData, bool compare(ItemType&,ItemType&)) = 0;
	virtual bool remove(const ItemType & data) = 0;
	virtual bool getEntry(const ItemType & anEntry, ItemType & returnedItem) const = 0;

private:
	// delete all nodes from the tree
	void destroyTree(BinaryNode<ItemType>* nodePtr);

	// copy from the tree rooted at nodePtr and returns a pointer to the copy
	BinaryNode<ItemType>*copyTree(const BinaryNode<ItemType>* nodePtr);

	// internal traverse
	//void _preorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	void _inorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	//void _postorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	void _breadth(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	void _printTree(void indent(ItemType &, int), BinaryNode<ItemType>* nodePtr, int level) const;
	void _printToFile(void visit(ItemType &), BinaryNode<ItemType>* nodePtr, ofstream &outFile) const;

};


template<class ItemType>
BinaryNode<ItemType>* BinaryTree<ItemType>::copyTree(const BinaryNode<ItemType>* nodePtr)
{
	BinaryNode<ItemType> * newNodePtr = nullptr;

	if (nodePtr != nullptr)
	{
		newNodePtr = new BinaryNode<ItemType>(nodePtr->getItem(), NULL, NULL);
		newNodePtr->setLeftPtr(copyTree(nodePtr->getLeftPtr()));
		newNodePtr->setRightPtr(copyTree(nodePtr->getRightPtr()));
	}

	return newNodePtr;
}

template<class ItemType>
void  BinaryTree<ItemType>::destroyTree(BinaryNode<ItemType> *nodePtr)
{
	if (nodePtr != nullptr) {
		destroyTree(nodePtr->getLeftPtr());
		destroyTree(nodePtr->getRightPtr());
		delete nodePtr;
		nodePtr = nullptr;
	}
}
template<class ItemType>
void BinaryTree<ItemType>::_printTree(void indent(ItemType &, int), BinaryNode<ItemType>* nodePtr, int level) const
{
	if (nodePtr != 0) {
		ItemType item = nodePtr->getItem();
		if (nodePtr->getLeftPtr() == NULL && nodePtr->getRightPtr() == NULL) int level = 1;
		for (int i = 1; i < level; i++) {
			cout << "\t";
		}
		indent(item, level);
		level++;
		_printTree(indent, nodePtr->getLeftPtr(), level);
		_printTree(indent, nodePtr->getRightPtr(), level);
	}
}

template<class ItemType>
void BinaryTree<ItemType>::printToFile(void visit(ItemType &)) const
{
	ofstream outFile;
	outFile.open("AmazonDistribute.txt");
	_printToFile(visit, rootPtr, outFile);
	outFile.close();
}

template <class ItemType>
void BinaryTree<ItemType>::_inorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr != nullptr)
	{
		_inorder(visit, nodePtr->getLeftPtr());
		ItemType item = nodePtr->getItem();
		visit(item);
		_inorder(visit, nodePtr->getRightPtr());
	}
}

template<class ItemType>
void BinaryTree<ItemType>::_printToFile(void visit(ItemType &), BinaryNode<ItemType>* nodePtr, ofstream &outputFile) const
{
	if (nodePtr != nullptr)
	{
		_printToFile(visit, nodePtr->getLeftPtr(), outputFile);
		ItemType item = nodePtr->getItem();
		
		outputFile << setw(7) << left << item.getAsin()
			<< ";" << right << item.getName()
			<< ";" << left << item.getDistributor() << left
			<< ";" << item.getRating()
			<<";" << right << item.getInterShip() << endl;

		_printToFile(visit, nodePtr->getRightPtr(), outputFile);

	}
}
#endif
