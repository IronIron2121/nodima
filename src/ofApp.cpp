#include "ofApp.h"
#include <iostream>



//--------------------------------------------------------------
void ofApp::setup(){


	// set background
	ofBackground(34, 34, 34);

	// settings for sound stream, all standard
	int bufferSize		= 512;
	sampleRate 			= 44100;
	phase 				= 0;
	phaseAdder 			= 0.0f;
	phaseAdderTarget 	= 0.0f;
	volume				= 0.1f;
	bNoise 				= false;

	// init stereo buffers
	lAudio.assign(bufferSize, 0.0);
	rAudio.assign(bufferSize, 0.0);

	// init sound stream
	soundStream.printDeviceList();
	// create empty settings object
	ofSoundStreamSettings settings;
	// set the settings
	settings.setOutListener(this);
	settings.sampleRate = sampleRate;
	settings.numOutputChannels = 2;
	settings.numInputChannels = 0;
	settings.bufferSize = bufferSize;
	soundStream.setup(settings);

	thisBPM = 120;
	// set up the BPM clock
    myClock.setTempo(thisBPM);  // Set BPM here
    myClock.setTicksPerBeat(1);  // 1 tick per beat

	currentScale = scaleTransposer.transpose("C", "Major");
	octaves = 4;

	initNoteNodeVector(octaves, currentScale);

	animas.push_back(Anima(thisBPM, noteNodeVector[0][0]));

}

void ofApp::initNoteNodeVector(int numOctaves, std::map<int, double> currentScale){
    for(int row = numOctaves; row >= 0; row--) {
        int col = 0;
        for(auto it = currentScale.begin(); it != currentScale.end(); it++) {
			
            // compute note value for this node, multiplying to get octvate
            double thisNote = it->second * std::pow(2, row);
            
            // init the note nodes with x, y, radius, and note value
            noteNodeVector.push_back(NoteNode(row, col, 20, thisNote));
            // debugging
            std::cout << "NoteNode created with value: " << thisNote << std::endl;
			col++;

        }
    }
}


//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	std::cout << "Testing!" << std::endl;

}

void ofApp::audioOut(ofSoundBuffer& buffer){
	beatClock.ticker();

	// run callbacks for all the animas
	for(int anima = 0; anima < animas.size(); anima++){
		animas[anima].bpmCB();
	}

	float leftScale = 1 - pan;
	float rightScale = pan;

	while(phase > TWO_PI){
		phase -= TWO_PI;
	}

	// if we're on a beat, trigger the envelope to play a note
	if beatClock.isTick(){
		noteEnvelope.trigger = 1;
	}

	if(bNoise == true){
		for(size_t i = 0; i < buffer.getNumFrames(); i++){
			lAudio[i] = buffer[i*buffer.getNumChannels()	] = ofRandom(0, 1);
			rAudio[i] = buffer[i*buffer.getNumChannels() + 1] = ofRandom(0, 1) * volume * rightScale;
		}
	} else{
		phaseAddar = 0.95f * phaseAddar + 0.05f * phaseAddarTarget;
		for(size_t i = 0; i < buffer.getNumFrames(); i++){
			phase += phaseAddar;
			float sample = sin(phase);
			lAudio[i] = buffer[i*buffer.getNumChannels()	] = sample * volume * leftScale;
			rAudio[i] = buffer[i*buffer.getNumChannels() + 1] = sample * volume * rightScale;
		}
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
