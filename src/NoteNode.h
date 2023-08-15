#pragma once

class NoteNode {
private:
	// x and y pos in vector
	int x; 
	int y; 
	// radius of circle on screen
	float radius;
	// the note that this node plays when triggers by an anima 
	double note; 
	// maxiOsc osc; // oscillator for playing notes
	// envelope env; // envelope for playing notes
	std::vector<std::vector<int>> distanceVector; // distances between one node and all other nodes
	void initDistanceMap(std::vector<std::vector<NoteNode*>> NoteVector); // calculate distances above


public:
	// constructor
	NoteNode(int x, int y, float radius, int note); 
	// getters for private vars
	int getX() const;
	int getY() const;
	float getRadius() const;
	int getNote() const;
	void playNote();
	std::vector<std::vector<int>> getDistances() const;
};
