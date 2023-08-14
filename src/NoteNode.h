#pragma once
#include "ofApp.h"

class NoteNode {
private:
	int x; // x-pos in vector
	int y; // y-pos in vector
	float radius;     // circle radius

	int note;         // midi note val for max
public:
	// openframeworks variables
	ofPoint position; // position on screen

};
