#pragma once

#include <vector>


class NoteNode {
private:
	// x and y pos in vector
	int x; 
	int y; 
	// the note that this node plays when triggers by an anima 
	double note; 
	// distances between one node and all other nodes
	std::vector<std::vector<int>> distanceVector; 


public:
	// constructor
	NoteNode(int x, int y, int note); 
	// getters for private vars
	int getX();
	int getY();
	double getNote();
	std::vector<std::vector<int>> getDistances();
	void initDistanceVector(std::vector<std::vector<NoteNode>> NoteVector); // calculate distances above

};
