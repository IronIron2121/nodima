#include "Anima.h"

// constructor
Anima::Anima(int boredom, int restlessness, int BPM) {
	this->boredom = boredom;
	this->restlessness = restlessness;
	this->BPM = BPM;
}

void Anima::move(){
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
	*/
}

// recall that softmax = e^z / sum(e^z), where z is a given vector
std::vector<double> Anima::softmax(std::vector<double>& z) {

	// grab the max value in the input vector z. we'll use this to avoid huge numbers
	double max_val = *std::max_element(z.begin(), z.end());
	
	// init sum to 0
	double sum = 0.0;

	// get the exponential sum of the vector, minus maximum val.
	for (auto val : z) {
		sum += std::exp(val - max_val);
	}

	// make new vector with size as the input to store output probabilities
	std::vector<double> probs(z.size());

	// get softmax probability of every element in the input vector
	for (size_t i = 0; i < z.size(); i++) {
		// calculate the exponential of (element - max_val) then divide by the sum of vector to normalize
		probs[i] = std::exp(z[i] - max_val) / sum;
	}

	// return softmax probabilities
	return probs;
}



// calculate distance. we use the manhattan distance to account for orthogonality
