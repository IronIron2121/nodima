#pragma once
#include <vector>
#include <algorithm>

// forward declaration
class NoteNode;

class Anima{
private:
	int boredom; // chance of moving node on next note output
	int restlessness; // rate of boredom increase, likelyhood of moving to more distant nodes
	int BPM; // rate of note playing

	std::vector<double> Anima::softmax(std::vector<double>& z); // calculate movement probability distribution
	void move(); // move to another node

public:
	Anima(int boredom, int restlessness, int BPM); // constructor

	NoteNode* currentNode; // the node currently inhabited by the anima
	std::vector<int> distanceVector; // vector of distances between current node and all other nodes
	
	~Anima(); // destructor

};

