#include "ofApp.h"
#include <iostream>


//--------------------------------------------------------------
void ofApp::setup(){

	// ----- BORING NECESSARY STUFF ----- //
	// set background
	ofBackground(34, 124, 34);
	// settings for sound stream, all standard
	bufferSize		    = 512;
	sampleRate 			= 44100;

	phase 				= 0;
	phaseAdder 			= 0.0f;
	phaseAdderTarget 	= 0.0f;
	volume				= 0.1f;
	// init stereo buffers
	lAudio.assign(bufferSize, 0.0);
	rAudio.assign(bufferSize, 0.0);
	// init sound stream
	soundStream.printDeviceList();
	// create empty settings object and set out settings to it
	ofSoundStreamSettings settings;
	settings.setOutListener(this);
	settings.sampleRate 	   = sampleRate;
	settings.numOutputChannels = 2;
	settings.numInputChannels  = 0;
	settings.bufferSize 	   = bufferSize;
    // set-up soundstream and maximilian
    ofxMaxiSettings::setup(sampleRate, 2, bufferSize);
	soundStream.setup(settings);
	// ----- END OF BORING NECESSARY STUFF ----- //

	// set up the baseBPM
	thisBPM = 120;
    // set initial number of animas
    numAnimas = 2;

	// set up the scale and the octaves
	currentScale = scaleTransposer.transpose("C", "Lydian");
	octaves 	 = 3;
	initNoteNodeVector(octaves, currentScale);

    for (int i = 0; i < numAnimas; i++) {
        // get random coordinates for initial note node
        int randX = (int)ofRandom(noteNodeVector.size());
        int randY = (int)ofRandom(noteNodeVector[0].size());
        // create a clock for this anima
        maxiClock thisClock;
        thisClock.setTempo(thisBPM);
        thisClock.setTicksPerBeat(1);
        // create an oscillator for this anima
        maxiOsc thisOsc;
        // make an ADSR envelope for this anima
        maxiEnv thisEnv;
        envelopeOut = thisEnv.adsr(1., thisEnv.trigger);
        thisEnv.setAttack(10);
        thisEnv.setDecay(500);
        thisEnv.setSustain(1);   
        thisEnv.setRelease(500);
        // push anima to the array
        animas.push_back(Anima(thisClock.bpm, &noteNodeVector[randX][randY], &noteNodeVector, thisOsc, thisEnv, thisClock));
    }

    for (int i = 0; i < animas.size(); i++) {
        outNotes.push_back(animas[i].getCurrentNote());
    }

}

void ofApp::initNoteNodeVector(int numOctaves, std::map<int, double> currentScale){
    noteNodeVector.resize(numOctaves + 1);  
    for(int row = 0; row <= numOctaves; row++) {
        std::vector<NoteNode> octaveNodes;
        int col = 0;
        for(auto it = currentScale.begin(); it != currentScale.end(); it++) {
            double thisNote = it->second * std::pow(2, row);
            octaveNodes.push_back(NoteNode(row, col, 20, thisNote));
            col++;
        }
        noteNodeVector[row] = octaveNodes;
    }
    for (int i = 0; i < noteNodeVector.size(); i++) {
        for (int j = 0; j < noteNodeVector[i].size(); j++) {
            noteNodeVector[i][j].initDistanceVector(noteNodeVector);
        }
    }
}


//--------------------------------------------------------------
void ofApp::update(){



}

//--------------------------------------------------------------
void ofApp::draw(){

}

void ofApp::audioOut(ofSoundBuffer& output) {
    std::size_t outChannels = output.getNumChannels();
    for (int i = 0; i < output.getNumFrames(); i++) {
        double outWave = 0.0;
        for (int j = 0; j < animas.size(); j++) {
            // check if this anima's BPM clock has ticked
            animas[j].anClock.ticker();
            if (animas[j].anClock.tick) {
                animas[j].anEnv.trigger = 1;
                animas[j].ifMove();
            }
            else {
                animas[j].anEnv.trigger = 0;
            }
            double envOut = animas[j].anEnv.adsr(1., animas[j].anEnv.trigger);
            outWave += animas[j].anOsc.sinewave(animas[j].getCurrentNote()) * envOut;
             // outWave += animas[j].anOsc.sinewave(animas[j].getCurrentNote()) * animas[j].anEnv.adsr(1., animas[j].anEnv.trigger);
        }

        output[i * outChannels] = outWave / animas.size();
        // output[i * outChannels] = myOsc.sinewave(440);
        output[i * outChannels + 1] = output[i * outChannels];
    }
}



//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
