#pragma once

#include <vector>


class NoteNode {
private:
	// x and y pos in vector
	int x; 
	int y; 
	// radius of circle on screen
	float radius;
	// the note that this node plays when triggers by an anima 
	double note; 
	std::vector<std::vector<int>> distanceVector; // distances between one node and all other nodes


public:
	// constructor
	NoteNode(int x, int y, float radius, int note); 
	// getters for private vars
	int getX();
	int getY();
	float getRadius();
	double getNote();
	void playNote();
	std::vector<std::vector<int>> getDistances();
	void initDistanceVector(std::vector<std::vector<NoteNode>> NoteVector); // calculate distances above

};
