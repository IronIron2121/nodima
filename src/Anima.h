#pragma once
#include <vector>
#include <algorithm>

// forward declaration
class NoteNode;

class Anima{
private:
	int boredom; // chance of moving node on next note output
	int restlessness; // rate of boredom increase, likelyhood of moving to more distant nodes
	int rootBPM; // base speed of note playing
	int currBPM; // current speed of note playing

	std::vector<std::vector<double>> softmax(std::vector<double>& z); // calculate movement probability distribution
	void move(); // move to another node
	std::pair<int,int> chooseProb(std::vector<std::vector<int>>); // choose a node based on the probability distribution

public:
	Anima(int rootBPM, NoteNode* startNode); // constructor
	NoteNode* startNode; // the node the anima starts on
	NoteNode* currentNode; // the node currently inhabited by the 
	~Anima(); // destructor

};

