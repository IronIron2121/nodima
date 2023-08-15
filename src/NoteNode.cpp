#include "NoteNode.h"


NoteNode::NoteNode(int x, int y, float radius, int note){
    // grab the passed parameters
    this->x = x;
    this->y = y;
    this->radius = radius;
    this->note = note;
    this->osc = maxiOsc(this->note, 0);
}


void NoteNode::initDistanceVector(std::vector<std::vector<NoteNode*>> NoteVector) {
    distanceVector.resize(NoteVector.size());
    // for every row in the vector
    for(size_t i; i < NoteVector.size(); i++){
        // resize the row
        distanceVector[i].resize(NoteVector[i].size());
        // for every node in the row
        for(size_t j; j < NoteVector[i].size(); j++){
            // grab the node
            NoteNode* thatNode = NoteVector[i][j];
            // calculate the manhattan distance between this node and that node
            distanceVector[i][j] = abs(this->x - thatNode->getX()) + abs(this->y - thatNode->y);
        }
    }   
}


void NoteNode::playNote(){

}


int NoteNode::getX(){
    return this->x;
};
int NoteNode::getY(){
    return this->y;
};
float NoteNode::getRadius(){
    return this->radius;
};
ofPoint NoteNode::getPosition(){
    return this->position;
};
int NoteNode::getNote(){
    return this->note;
};
std::vector<std::vector<double>> NoteNode::getDistances(){
    return this->distanceVector;
};
