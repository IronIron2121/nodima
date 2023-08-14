#include "Anima.h"
#include "NoteNode.h"


// constructor
Anima::Anima(int rootBPM, NoteNode* startNode) {
	this->boredom = 0;
	this->restlessness = 0;
	this->rootBPM = rootBPM;
	this->currBPM = this->rootBPM;
}


void Anima::move(){
	std::vector<std::vector<int>>currDistances = this->currentNode->getDistances();
	this->chooseProb(currDistances);


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
}


std::pair<int,int> Anima::chooseProb(std::vector<std::vector<int>>){
	// generate random value between 0 and 1
	std::random_device rd; 
	std::mt19937 gen(rd()); 
	std::uniform_real_distribution<> dis(0, 1); 
	double threshold = dis(gen); 

	// choose sample from dsitribution based on random value & softmax probabilities
	double cumulativeProb = 0.0;
	for (size_t i = 0; i < probs.size(); ++i) {
		for(size_t j = 0; j < probs[i].size(); ++j{
			// add the probability of current index to cumulative probability
			cumulativeProb += probs[i][j]; 

			// if the cumulative probability is greater than the random value, return the index
			if (threshold <= cumulativeProb) {
				std::pair<int, int> index(i, j);
				return index; 
			}
		}
	}
}


// softmax = e^z / sum(e^z),  z == provided vector, e == euler's number
std::vector<std::vector<double>> Anima::softmax(const std::vector<std::vector<double>>& z) {
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