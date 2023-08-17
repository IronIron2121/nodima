#include "Anima.h"
#include "NoteNode.h"
#include "ofMain.h"
#include <cmath>
#include <random>
#include <vector>


// constructor
Anima::Anima(int rootBPM, NoteNode* startNode, std::vector<std::vector<NoteNode>>* noteNodeVector, maxiOsc anOsc, maxiEnv anEnv, maxiClock anClock) {
	this->initAttributes();
	this->rootBPM = rootBPM;
	this->currBPM = this->rootBPM;
	this->anClock = anClock;
	this->anClock.setTempo(this->rootBPM);
	this->anClock.setTicksPerBeat(1);
	this->currentNode = startNode;
	this->noteNodeVector = noteNodeVector;
	this->anEnv = anEnv;
	this->anOsc = anOsc;
};

void Anima::initAttributes(bool reset){
	this->fractionBase 		   = 2.0;
	this->boredom 			   = 0.0;
	this->boredomInterval 	   = 0.2;
	this->equanimity 		   = 1.0;
	this->restlessness 		   = 0.0;
	this->restlessnessInterval = 0.1;
	this->maxRestlessness 	   = 1000;
	this->patience 			   = 4.0;

}



void Anima::ifMove(){
	// get a random number between 0 and 1, compare against move probability
	// we manipulate an exponential function to make movement more likely as boredom and restlessness increase
	double moveNumerator   = std::pow(2.0, this->equanimity + (this->boredom 	  * this->boredomInterval	  ));
	double moveDenominator = std::pow(2.0, this->patience   - (this->restlessness * this->restlessnessInterval));
	double moveProbability = (moveNumerator / moveDenominator);
	double randomGen 	   = this->getRandomDouble();

	if(randomGen < moveProbability){
		this->move();
	} else{
		//std::cout << "No move!" << std::endl;
		//std::cout << "randomGen == " << randomGen << std::endl;
		//std::cout << "moveProbability == " << moveProbability << std::endl;
		this->boredom += 1;
	}
}


void Anima::move(){
	// get the distances from the current node, choose the next node based on them
	std::vector<std::vector<int>>    currDistances     = this->currentNode->getDistances();
	std::vector<std::vector<double>> moveProbabilities = this->softmax(currDistances);
	std::pair<int,int> indices 						   = chooseProb(moveProbabilities);
	this->currentNode 								   = &(*(this->noteNodeVector))[indices.first][indices.second];

	// update anima attributes
	this->boredom 	    = 0;
	if (this->restlessness < this->maxRestlessness) {
		this->restlessness += (1);
	}
	else {
		this->restlessness = 0;
		std::cout << "Restlessness reset!" << std::endl;
	}
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

double Anima::getRandomDouble(int min, int max){
	return ofRandom(min, max);
}




// softmax = e^z / sum(e^z),  where z == provided vector, e == euler's number
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

double Anima::getCurrentNote(){
	return this->currentNode->getNote();
}