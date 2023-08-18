#include "Anima.h"
#include "NoteNode.h"
#include "ofMain.h"
#include <cmath>
#include <random>
#include <vector>


// constructor
Anima::Anima(int rootBPM, NoteNode* startNode, std::vector<std::vector<NoteNode>>* noteNodeVector, maxiOsc anOsc, maxiClock anClock, std::string thisNote) {
	// init some basic attributes 
	this->initAttributes();
	// init BPM settings and clock parameters
	this->rootBPM = rootBPM;
	this->anClock = anClock;
	this->anClock.setTempo(this->rootBPM);
	this->anClock.setTicksPerBeat(1);
	// set starting node and the full vector of available nodes
	this->currentNode = startNode;
	this->noteNodeVector = noteNodeVector;
	// init oscillator for this anima
	this->anOsc = anOsc;
	this->thisNote = thisNote;
};

// differentcoefficients that determine the movement logic
// you can tweak these to adjust movement behavior
void Anima::initAttributes(bool reset){
	// fractionBase is the base number for exponential calculations.
	this->fractionBase 		   = 2.0;
	// boredom modulates the numerator of the move probability
	this->boredom 			   = 0.0;
	this->boredomInterval 	   = 0.2;
	// boredom is the basic exponent of the numerator of move probability
	this->equanimity 		   = 1.0;
	// restlessness modulates the move prob denominator and also activates pineal mode
	this->restlessness 		   = 0.0;
	this->restlessnessInterval = 0.04;
	// maximum permitted value for restlessness
	this->maxRestlessness 	   = 1000;
	// the basic exponent of the denominator of move probability
	this->patience 			   = 4.0;
	// activation of pineal mode and value and value that determines threshold of activation
	this->pineal			   = false;
	this->pinealThresh		   = 2;
}
 

// do movement from current to next node
void Anima::move(){
	// get next move based on probabilities calculated from distances to neighboring nodes
	// this is based on exponential functions, so the rate of movement is accelerating slowly until it reaches a blistering pace near the end
	// i.e. the speed of movement is being accelerated at an accelerating rate
	std::vector<std::vector<int>>    currDistances     = this->currentNode->getDistances();
	std::vector<std::vector<double>> moveProbabilities = this->softmax(currDistances);
	std::pair<int,int> indices 						   = chooseProb(moveProbabilities);
	this->currentNode 								   = &(*(this->noteNodeVector))[indices.first][indices.second];

	// update and reset movement attributes after making a move
	this->boredom = 0;
	if (this->restlessness < this->maxRestlessness) {
		// restlessness increases after every move, towards the max
		this->restlessness += 1;

		// if pineal mode is not on and we're over the threshold for it, then activate it
		if (!(this->pineal) && this->restlessness > (this->maxRestlessness / this->pinealThresh)) {
			this->pineal = true;
		}
	}
	else {
		// once it hits the maximum, we reset it and turn off pineal mode
		this->restlessness = 0;
		this->pineal = false;
	}

	// we determine the tempo based on the current level of restlessness
	this->anClock.setTempo(this->rootBPM + (this->restlessness*3.0));
};


std::pair<int,int> Anima::chooseProb(const std::vector<std::vector<double>>& probabilities){
	// generate random value between 0 and 1 and compare softmax probabilities against it
	double threshold 	  = this->getRandomDouble(); 
	double cumulativeProb = 0.0;
	for (size_t i = 0; i < probabilities.size(); ++i) {
		for(size_t j = 0; j < probabilities[i].size(); ++j){
			// add the probability of current index to cumulative probability
			cumulativeProb += probabilities[i][j]; 

			// if the cumulative probability is greater than the random value, return the index
			if (threshold <= cumulativeProb) {
				std::pair<int, int> index(i, j);
				return index; 
			}
		}
	}
}


// pretty simple - just returns a random double
double Anima::getRandomDouble(int min, int max){
	return ofRandom(min, max);
}



// recall that softmax = e^z / sum(e^z),  where z == provided vector, e == euler's number
std::vector<std::vector<double>> Anima::softmax(const std::vector<std::vector<int>>& z) {
    double sum = 0.0;
    // calculate the sum of exponentials for input vector
    for (const auto& row : z) {
        for (double val : row) {
            sum += std::exp(val);
        }
    }
	// get row and column sizes
	int zRowSize = z.size();
	int zColSize = z[0].size();
	// compute softmax probabilities
    std::vector<std::vector<double>> softmaxProbabilities(zRowSize, std::vector<double>(zColSize));
    for (size_t i = 0; i < zRowSize; i++) {
        for (size_t j = 0; j < zColSize; j++) {
            softmaxProbabilities[i][j] = std::exp(z[i][j]) / sum;
        }
    }

    return softmaxProbabilities;
}


// gets a random note from any given scale with whatever note we're currently using as the root
double Anima::getRandomNote() {
	// get a random scale name
	std::string randomScale = this->localTransposer.availableScales[ofRandom(0, this->localTransposer.availableScales.size())];

	// get the indices for the selected scale
	std::vector<int> selectedScaleIndices = this->localTransposer.scaleIndices[randomScale];

	// select a random note index from the selected scale's indices
	int randomNoteIndex = selectedScaleIndices[ofRandom(0, selectedScaleIndices.size())];

	// use that name to key into the map of scales and get the frequency using the random note index
	double randomNote = this->localTransposer.baseScale[this->thisNote][randomNoteIndex]; 

	return randomNote;
}


// returns the note relevant to this anima's current node
double Anima::getCurrentNote() {
	if (this->pineal) {
		if (this->getRandomDouble() < (0.25 * (this->restlessness/this->maxRestlessness))) {
			return this->getRandomNote();
		}
	}

	return this->currentNode->getNote();
}