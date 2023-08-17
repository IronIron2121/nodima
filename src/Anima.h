#pragma once
#include <vector>
#include <algorithm>
#include "ofxMaxim.h"
#include "ScaleTransposer.h"


// forward declaration
class NoteNode;

class Anima{
private:
	// base numerator and denominator for movement calculation
	double fractionBase;
	// movement calculation numerator exponent
	double equanimity;
	// movement calculation numerator exponent additive
	double boredom; 
	// movement calculation denominator exponent
	double patience; 
	// movement calculation denominator exponent subtractive
	double restlessness;
	// max value for restlessness before resetting
	double maxRestlessness; 
	// the number that forms a product with boredom to 
	double boredomInterval;
	double restlessnessInterval;

	int rootBPM; 
	int currBPM; 
	bool pineal;

	std::vector<std::vector<NoteNode>>* noteNodeVector; // vector of all note nodes
	NoteNode* currentNode; // the node currently inhabited by the anima
	NoteNode* previousNode; // the node previously inhabited by the anima


	void move(); // move to another node
	void initAttributes(bool reset = false);
	double Anima::getRandomDouble(int min = 0, int max = 1);
	std::vector<std::vector<double>> softmax(const std::vector<std::vector<int>>& z); // calculate movement probability distribution
	std::pair<int,int> chooseProb(const std::vector<std::vector<double>>& probabilities); // choose a node based on the probability distribution
	ScaleTransposer localTransposer;
	std::string thisNote;
	std::string thisScale;

public:
	// constructor
	Anima(int rootBPM, NoteNode* startNode, std::vector<std::vector<NoteNode>>*, maxiOsc anOsc, maxiClock anClock, std::string thisNote, std::string thisScale);
	void ifMove();
	double Anima::getCurrentNote();
	maxiClock anClock;
	maxiOsc anOsc;
	double getRandomNote();





};

