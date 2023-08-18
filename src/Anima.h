#pragma once
#include <vector>
#include <algorithm>
#include "ofxMaxim.h"
#include "ScaleTransposer.h"


// forward declaration
class NoteNode;

class Anima{
private:
	// ------------------------------------ PRIVATE FUNCTIONS ------------------------------------ /
	// initialise attributes
	void initAttributes(bool reset = false);
	
	// move to a new node
	void move();

	// return a random double 
	double Anima::getRandomDouble(int min = 0, int max = 1);

	// calculate probability of movement to different nodes relative to current position
	std::vector<std::vector<double>> softmax(const std::vector<std::vector<int>>& z); 

	// choose a node based on the probability distribution and returns its indices
	std::pair<int, int> chooseProb(const std::vector<std::vector<double>>& probabilities); 
	
	// base numerator and denominator for movement calculation
	double fractionBase;
	double maxRestlessness;

	// default / minimum BPM. we speed up from here, and also return to it when restlessness resets
	int rootBPM; 

	// boolean to track pineal mode activation and threshold of activation
	bool pineal;
	int pinealThresh;

	// vector of all note nodes
	std::vector<std::vector<NoteNode>>* noteNodeVector; 
	// the node currently inhabited by the anima
	NoteNode* currentNode; 

	// we have a local transposer so we can get random notes from different scales in pineal mode
	ScaleTransposer localTransposer;
	std::string thisNote;
	std::string thisScale;

public:
	// constructor
	Anima(int rootBPM, NoteNode* startNode, std::vector<std::vector<NoteNode>>*, maxiOsc anOsc, maxiClock anClock, std::string thisNote);
	// figure out if we're going to move or not on this beat
	void ifMove();
	// return the note corresponding to anima's current node
	double Anima::getCurrentNote();
	// get a random note if we're in pineal mode
	double getRandomNote();


	// ------------------------------------ PRIVATE FUNCTIONS ------------------------------------ /
	// determines and track tempo
	maxiClock anClock;
	// computes current signal output
	maxiOsc anOsc;


	// sadly I had to make these public due to some problems accessing them from outside the object
	// movement calculation numerator exponent
	double equanimity;
	// movement calculation numerator exponent additive
	double boredom;
	// movement calculation denominator exponent
	double patience;
	// movement calculation denominator exponent subtractive
	double restlessness;
	// max value for restlessness before resetting
	double restlessnessInterval;
	// the number that forms a product with boredom to 
	double boredomInterval;





};

