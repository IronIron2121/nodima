#include "Anima.h"
#include "NoteNode.h"
#include <cmath>
#include <random>
#include <vector>


// constructor
Anima::Anima(int rootBPM, NoteNode* startNode, const std::vector<std::vector<NoteNode*>> noteNodeVector) {
	this->initAttributes();
	this->rootBPM = rootBPM;
	this->currBPM = this->rootBPM;
	this->noteNodeVector = noteNodeVector;
};

void Anima::initAttributes(bool reset = false){
	this->fractionBase 		   = 2.0;
	this->equanimity 		   = 1.0;
	this->boredom 			   = 0.0;
	this->patience 			   = 0.0;
	this->restlessness 		   = 0.0;
	this->maxRestlessness 	   = 20;
	this->boredomInterval 	   = 0.2;
	this->restlessnessInterval = 0.1;
}


void Anima::bpmCallBack(){

	this->boredom += 1;
}


void Anima::move(){
	// get the distances from the current node, choose the next node based on them
	std::vector<std::vector<int>>    currDistances    = this->currentNode->getDistances();
	std::vector<std::vector<double>> softmaxDistances = this->softmax(currDistances);
	std::pair<int,int> indices 						  = chooseProb(softmaxDistances);
	this->currentNode 								  = this->noteNodeVector[indices.first][indices.second];

	// update anima attributes
	this->boredom 	    = 0;
	this->restlessness += 1;
	this->patience 	   -= (this->restlessness * 0.2);

	double numerator   = std::pow(2.0, this->equanimity + (this->boredom 	  * this->boredomInterval	  ));
	double denominator = std::pow(2.0, this->patience   - (this->restlessness * this->restlessnessInterval));

	double moveProbability = (numerator / denominator);


	/*
	PSEUDEO-CODE

	probDist = this->softmax(distanceVector)
	nextNode = this->sample(probDist)
	this->currentNode = nextNode
	this->currentNode->playNote()

	this->boredom = 0
	this->restlessness += 1
	this->BPM += 1

	this->distanceVector = this->currentNode->getDistances()
	// yeah - actually, it's a lot simpler if every node contains its distance information in...itself
	although in that case we're holding a lot more in memory
	*/
};



std::pair<int,int> Anima::chooseProb(const std::vector<std::vector<double>>& probabilities){
	// generate random value between 0 and 1
	double threshold = this->getRandomDouble(); 

	// choose sample from dsitribution based on random value & softmax probabilities
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

double Anima::getRandomDouble(int min = 0, int max = 1){
	// get random int
	std::random_device getRandomIntSeed;
	// use random int as seed for mersenne twister 
	std::mt19937 twista(getRandomIntSeed()); 
	// create distribution between min and max
	std::uniform_real_distribution<> distribution(min, max);
	// generate a super-duper random value between 0 and 1, and return it
	double randomDouble = distribution(twista); 
	return randomDouble;
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

    // compute softmax probabilities
    std::vector<std::vector<double>> softmaxProbabilities(z.size(), std::vector<double>(z[0].size()));
    for (size_t i = 0; i < z.size(); i++) {
        for (size_t j = 0; j < z[i].size(); j++) {
            softmaxProbabilities[i][j] = std::exp(z[i][j]) / sum;
        }
    }

    return softmaxProbabilities;
}