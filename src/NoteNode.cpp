#include "NoteNode.h"
#include <iostream>

NoteNode::NoteNode(int x, int y, float radius, int note){
    // grab the passed parameters
    this->x = x;
    this->y = y;
    this->radius = radius;
    this->note = note;
}


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

double NoteNode::getNote(){
    return this->note;
};
std::vector<std::vector<int>> NoteNode::getDistances(){
    //std::cout << "In NoteNode - rows size = " << this->distanceVector.size() << std::endl;
    //std::cout << "In NoteNode - cols size = " << this->distanceVector[0].size() << std::endl;
    return this->distanceVector;
};
