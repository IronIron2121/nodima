#pragma once

#include "ofMain.h"
#include "ScaleTransposer.h"
#include "Anima.h"
#include "NoteNode.h"
#include "ofxMaxim.h"
 
class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		void initNoteNodeVector(int numOctaves, std::map<int, double>);

		// -- FROM AUDIO EXAMPLE 
		void audioOut(ofSoundBuffer& output);
		ofSoundStream soundStream;
		int		bufferSize;
		int		sampleRate;
		bool 	bNoise;
		float 	pan;
		float 	volume;
		vector <float> lAudio;
		vector <float> rAudio;
		//------------------- for the simple sine wave synthesis
		float 	targetFrequency;
		float 	phase;
		float 	phaseAdder;
		float 	phaseAdderTarget;
		double  outNote0;
		double  outNote1;

		double envelopeOut;

		int thisBPM;

		ScaleTransposer scaleTransposer;
		int octaves;

		std::vector<Anima> animas;
		int numAnimas;
		std::vector<std::vector<NoteNode>> noteNodeVector;
		maxiEnv thisEnvelope;
		maxiOsc myOsc;
		std::map<int, double> currentScale;
		std::vector<double> outNotes;

		
};
