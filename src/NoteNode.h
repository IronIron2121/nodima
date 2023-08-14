#pragma once
#include "ofApp.h"

class NoteNode {
private:
	int x; // x-pos in vector
	int y; // y-pos in vector
	float radius; // circle radius

	int note; // midi note val for maximilian

	ofPoint position; // position on screen

	// vector detailing distances between a given Note and all the other nodes
	std::vector<std::vector<float>> distanceVector; 
	// orthogonal disance of all NoteNodes relative to a given instance. why manhattan? because it's more fun! 
	void initDistanceMap(std::vector<std::vector<NoteNode*>> NoteVector);

public:
	// constructor
	NoteNode(int x, int y, float radius, int note); 

	// getters for private vars
	int getX() const;
	int getY() const;
	float getRadius() const;
	int getNote() const;
	void playNote();
	ofPoint getPosition() const;
	std::vector<std::vector<int>> getDistances() const;


};
