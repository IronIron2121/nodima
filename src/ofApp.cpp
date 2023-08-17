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
    numAnimas = 3;

	// set up the scale and the octaves

    currentRootNote = "C";
    currentScaleName = "Hijaz";

	currentScale = scaleTransposer.transpose(currentRootNote, currentScaleName);
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

        // push anima to the array
        animas.push_back(Anima(
            thisClock.bpm, 
            &noteNodeVector[randX][randY], 
            &noteNodeVector, 
            thisOsc, 
            thisClock,
            currentRootNote,
            currentScaleName
            )
        );
    }


    /*
    NOTE: I cannot for the life of me get maxiEnvelopes to work when dynamically allocated
    They have to be initialised in the header, or they just don't work.
    I tried making a vector of them. I tried making a vector of pointers of them. I tried initialising them in the anima class. 
    I don't have time to dig down into the memory, so for now this is all that I could figure out that actually works.
    But you can have values of "numAnimas" above 3 if you add more envelopes down here
    */
    env1.setAttack(10);
    env1.setDecay(500);
    env1.setSustain(1);
    env1.setRelease(1000);

    env2.setAttack(10);
    env2.setDecay(500);
    env2.setSustain(1);
    env2.setRelease(1000);

    env3.setAttack(10);
    env3.setDecay(500);
    env3.setSustain(1);
    env3.setRelease(1000);

    envVector.push_back(&(env1));
    envVector.push_back(&(env2));
    envVector.push_back(&(env3));
}

void ofApp::initNoteNodeVector(int numOctaves, std::map<int, double> currentScale){
    noteNodeVector.resize(numOctaves + 1);  
    for(int row = 0; row <= numOctaves; row++) {
        // make a vector of noteNodes
        std::vector<NoteNode> octaveNodes;
        // i don't remember why i did this rather than a conventional loop but i'm too afraid to change it now
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
        double totalLeft  = 0.;
        double totalRight = 0.;

        for (int j = 0; j < animas.size(); j++) {
            // see if we're on a beat
            animas[j].anClock.ticker();
            double thisNote = animas[j].getCurrentNote();

            if (animas[j].anClock.tick) {
                // if we are, get move calculations and trigger the envelope
                envVector[j]->trigger = 1;
                animas[j].ifMove();

            }
            else {
                // if we're not, untrigger the envelope
                envVector[j]->trigger = 0;

            }

            // compute the enveloped sinewave for this output
            double outWave          = animas[j].anOsc.sinewave(thisNote);
            double envelopeOut      = envVector[j]->adsr(1., envVector[j]->trigger);
            // add to output sum
            totalLeft += (outWave * (0.5 / animas.size())) * envelopeOut;
            totalRight += totalLeft;


        }
        // output the sums
        output[i * outChannels]     = totalLeft;
        output[i * outChannels + 1] = totalRight;
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
