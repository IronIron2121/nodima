#include "NoteNode.h"


NoteNode::NoteNode(int x, int y, float radius, int note){
    // grab the passed parameters
    this->x = x;
    this->y = y;
    this->radius = radius;
    this->note = note;
}


void NoteNode::initDistanceVector(std::vector<std::vector<NoteNode*>> NoteVector) {
    distanceVector.resize(NoteVector.size());
    // for every row in the vector
    for(size_t i; i < NoteVector.size(); i++){
        // for every node in the row
        for(size_t j; j < NoteVector[i].size(); j++){
            // grab the node
            NoteNode* thatNode = NoteVector[i][j];
            // calculate the manhattan distance between this node and that node two nodes
            distanceVector[i][j] = abs(this->x - thatNode.x) + abs(this->y - thatNode.y);
        }
    }   
}

void NoteNode::playNote(){

}