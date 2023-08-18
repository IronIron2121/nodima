#include "NoteNode.h"
#include <iostream>


NoteNode::NoteNode(int x, int y, int note){
    // grab the passed parameters
    this->x = x;
    this->y = y;
    this->note = note;
}


// a vector containing distances of all nodes relative to this node
void NoteNode::initDistanceVector(std::vector<std::vector<NoteNode>> NoteVector) {
    this->distanceVector.resize(NoteVector.size());
    // for every row in the vector
    for(size_t i = 0; i < NoteVector.size(); i++){
        // resize the row
        this->distanceVector[i].resize(NoteVector[i].size());
        // for every node in the row
        for(size_t j = 0; j < NoteVector[i].size(); j++){
            // grab the node
            NoteNode thatNode = NoteVector[i][j];
            // calculate the manhattan distance between this node and that node
            distanceVector[i][j] = abs(this->x - thatNode.getX()) + abs(this->y - thatNode.y);
        }
    }   
}


// get x-pos in vector
int NoteNode::getX(){
    return this->x;
};


// get y-pos in vector
int NoteNode::getY(){
    return this->y;
};


// get note for this node
double NoteNode::getNote(){
    return this->note;
};


// get distance relative to this node
std::vector<std::vector<int>> NoteNode::getDistances(){

    return this->distanceVector;
};
