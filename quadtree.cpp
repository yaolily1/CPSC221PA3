
/**
 *
 * quadtree (pa3)
 * quadtree.cpp
 * This file will be used for grading.
 *
 */

#include "quadtree.h"
#include <math.h>
using namespace std;


// Node constructor, given.
quadtree::Node::Node(pair<int,int> ul, int d,RGBAPixel a, double v)
	:upLeft(ul),dim(d),avg(a),var(v),NW(NULL),NE(NULL),SE(NULL),SW(NULL)
	{}

// quadtree destructor, given.
quadtree::~quadtree() {
	clear();
}
// quadtree copy constructor, given.
quadtree::quadtree(const quadtree & other) {
	copy(other);
}
// quadtree assignment operator, given.
quadtree & quadtree::operator=(const quadtree & rhs) {
	if (this != &rhs) {
		clear();
		copy(rhs);
	}
	return *this;
}


quadtree::quadtree(PNG & imIn) {

	// STEP 1: determine the largest 2^k by 2^k square that can be extracted
	// from the PNG

	int dimD = floor(log2(std::min(imIn.width, imIn.height))); 

	edge = pow(2, dimD); 

	// STEP 2: initialize stats using imIn as the argument (i.e. stats(imIn)); 

	stats s = stats(imIn);

	// STEP 3: initialize upper left 

	pair<int, int> ul = (0, 0); 



	// STEP 4: build quadtree (recursively) using buildTree helper function

	buildTree(& s, & ul, dimD); 


	// base case: dim == 0
	// recursive case: dim > 0 
        /* Your code here! */

}


quadtree::Node * quadtree::buildTree(stats & s, pair<int,int> & ul, int dim) {
        // base case. node == leaf == pixel. 
		if (dim == 0) {

			// step1: make current node using the node constructor. 
			// return current node;

			Node *currentNode = new Node(ul, dim, s.getAvg(ul, dim), s.getVar(ul, dim));
			return currentNode;


		}
		
		else { 

	// step1: make current node using the node constructor. 
	// if root is NULL (i.e. nothing yet created), root assigned to the node. 

			
				Node *currentNode = new Node(ul, dim, s.getAvg(ul, dim), s.getVar(ul, dim));

				if (root == NULL) {

					root = currentNode; 
				}
	 

	// step1 I: point current node to its children, populate the default fields. 

	// step2: call buildTree recursively to create children nodes; 

	// step2 I: determine ul value for each of the children;

	// 
				pair<int, int> ulNW = (ul.first, ul.second);
				pair<int, int> ulNE = (ul.first + ((pow(2, dim))/2 + 1), ul.second); 
				pair<int, int> ulSW = (ul.first, ul.second + ((pow(2, dim))/2 + 1)); 
				pair<int, int> ulSE = (ul.first + ((pow(2, dim))/2 + 1), ul.second + ((pow(2, dim))/2 + 1));

	// step 2 II: decrement dimension, and pass the new value as children's dimension 

				dim--; 

	// step 2 III: buildTree for each of the children.

				*quadtree subTreeNW = buildTree(& s, ulNW, dim);
				*quadtree subTreeNE = buildTree(& s, ulNE, dim);
				*quadtree subTreeSW = buildTree(& s, ulSW, dim);
				*quadtree subTreeSE = buildTree(& s, ulSE, dim); 

				currentNode -> NW = subTreeNW;
				currentNode -> NE = subTreeNE;
				currentNode -> SW = subTreeSW;
				currentNode -> SE = subTreeSE; 

				return currentNode; 

		}
		/* Your code here! */

}


PNG quadtree::render() {
        /* Your code here! */
	// Created a recursive helper function, that takes node as its argument
	// this helper will go through the tree, pull pixel from those nodes = leaf
	// and continuing to drill for those nodes that have children. 
	// PNG is the return type for buildTreeImage. 

	return buildTreeImage(root); 


}

	// this function will populate the initially blank PNG with pixels found from those
	// nodes that constitute leaves, while recursively calling those nodes with children. 
	// referred PA1 for guidance re render (specifically PNG files, block).
	// created new PNG files within this assignment folder

PNG quadtree::buildTreeImage(Node* currentNode) {

	// step 1: create new square shaped PNG (blank canvas), of length and width edge == 2^dim.
	// "edge" represents the maximum square can be extracted from the image. 

	PNG quadPNG = new PNG(edge, edge); 

	// base case: the current node has no children;
	// this means that we are at a leaf
	// PNG pixels will be rendered from parameter (average pixel) contained within leaf node 

	if (currentNode -> NW == NULL) {

		pair<int, int> ul = currentNode.ul;
		int dim = currentNode.dim; 
		int length = pow(2, dim); 

		int startX = ul -> first;
		int startY = ul -> second;

		int endX = startX +  length; 
		int endY = startY + length;

		// y is the outer loop
		// x is the inner loop 

		for (int y = startY; y <= endY; y++) {
			for (int x = startX; x <= endX; x++) {

				RGBAPixel *pixel = quadPNG.getPixel(x, y); 
				*pixel = currentNode.avg;
			}
		}

		return quadPNG;
	}

	// recursive case: current node has children; call renderTree on each child. 
	// function will keep drilling down for such nodes. 
	// note that if a node has children, it must have four of them 
	// i.e. either a node has no children or it has four. 

	else {

		buildTreeImage(currentNode -> NW);
		buildTreeImage(currentNode -> NE); 
		buildTreeImage(currentNode -> SW); 
		buildTreeImage(currentNode -> SE); 

	}

}







int quadtree::idealPrune(int leaves){
        /* Your code here! */

}

int quadtree::pruneSize(int tol){
        /* Your code here! */

}

void quadtree::prune(int tol){
        /* Your code here! */

		// recursive function with helpers
		// base case: variability  > tolerance. Keep node. Do not need to recurse up tree for parent
		// recursive case: variability < tolerance. Clear node; move up to check parent. 
		// need clear helper function 

}

void quadtree::clear() {
/* your code here */
}

void quadtree::copy(const quadtree & orig){
/* your code here */
}


