/*
 * Copyright (c) 2017 Max Peeperkorn <post@maxpeeperkorn.nl>
 * based on ofxPd Pitch Shifter example by Dan Wilcox
 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
    ofBackground(54, 54, 54);
    
	// the number of libpd ticks per buffer,
	// used to compute the audio buffer len: tpb * blocksize (always 64)
	#ifdef TARGET_LINUX_ARM
		// longer latency for Raspberry PI
		int ticksPerBuffer = 32; // 32 * 64 = buffer len of 2048
		
		// you'll need a USB mic on the Raspberry PI and may need to set the audio device,
		// otherwise this app won't really do anything without an incoming audio signal ...
		int numInputs = 0; // no built in mic, change this if you have a USB mic
	#else
		int ticksPerBuffer = 3; // 8 * 64 = buffer len of 512
		int numInputs = 1;
	#endif
    
    // stereo output, of soundstream variables
    int numOutputs = 2;
    
    sampleRate = 44100;
    bufferSize = ofxPd::blockSize() * ticksPerBuffer;
    nBuffers = 3; // 2 output, 1 input
    
    // setup pitch detections
    latestNote = "";
    pitch.setup();
	
    // setup of sound stream
    ofSoundStreamSetup(numOutputs, numInputs, this, sampleRate, bufferSize, nBuffers);
    
    inputDevices = soundstream.getMatchingDevices("", 2, 0);
    outputDevices = soundstream.getMatchingDevices("", 0, 2);
	
    // setup pd
	if(!pd.init(numOutputs, numInputs, sampleRate, ticksPerBuffer)) {
		OF_EXIT_APP(1);
	}
    
	pd.subscribe("mix");
	pd.subscribe("transpose");
	pd.subscribe("inputGain");
	pd.subscribe("outputGain");
	pd.addToSearchPath("pd");
	pd.start();

	// open patch
	Patch patch = pd.openPatch("pd/_main.pd");
	cout << patch << endl;

    // gui
    guiGroup.setup();
    guiGroup.setName("Monitor");
    guiGroup.setPosition(792, 20);
    
    guiGroup.add(pitchDetect.set("Pitch Detect"));
    
    guiGroup.add(midiPitch.set("Midi Pitch", 0, 0, 128));
    guiGroup.add(pitchConfidence.set("Confidence", 0, 0, 1));
    guiGroup.add(confidence.set("confidence level", 0.64, 0, 1));
    
    guiGroup.add(pitchShift.set("Pitch Shift"));
    
    guiGroup.add(transpose.set("Transpose", 0, -1, 1));
    guiGroup.add(mix.set("Wet/Dry Mix", 1, 0, 1));
    guiGroup.add(inGain.set("Input Gain", 0.5, 0, 1));
    guiGroup.add(outGain.set("Output Gain", 0.5, 0, 1));
    
    
    
    ofEnableAlphaBlending();
}

//--------------------------------------------------------------
void ofApp::update() {
    // update scope array from pd
	pd.readArray("scope", scopeArray);
	
	// update pd from gui
    pd << StartMessage() << "transpose" << transpose.get() << FinishList("TO_PD");
    pd << StartMessage() << "mix" << mix.get() << FinishList("TO_PD");
    pd << StartMessage() << "inGain" << inGain.get() << FinishList("TO_PD");
    pd << StartMessage() << "outGain" << outGain.get() << FinishList("TO_PD");
    
    ofLog() << transpose;
}

//--------------------------------------------------------------
void ofApp::draw() {
    ofSetColor(225);
    ofDrawBitmapString("JAN FOOTE VARIABLE AUTO PITCHSHIFTER", 32, 32);
    
    ofNoFill();
	
    // draw scope
    
    float w1 = ofGetWidth() / (float) scopeArray.size();
    float h = ofGetHeight() / 2;
    
    ofSetColor(245, 58, 135);
    ofSetLineWidth(2);
    
    ofBeginShape();
        for (int i = 0; i < scopeArray.size(); i++){
            ofVertex(i * w1, h - (scopeArray[i] * h) * 5);
        }
    ofEndShape(false);
    
    // get pitch
    
    ofSetColor(255);
    
    pitchConfidence = pitch.pitchConfidence;
    
    if (pitch.latestPitch) {
        midiPitch = pitch.latestPitch;
        
        if (pitchConfidence >= confidence.get()) {
            string note = midiToNote(round(midiPitch));
            
            if (latestNote != note) latestNote = note;
        }
    };
    
    ofDrawBitmapString("Current Note: " + latestNote, 32, 64);
    
    ofDrawBitmapString("Current Note: " + latestNote, 32, 64);
    
    // draw gui
    
    guiGroup.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    if (key == 's') {
        settings.serialize(parameters);
        settings.save("settings.xml");
    }
    
    if (key == 'l') {
        settings.load("settings.xml");
        settings.deserialize(parameters);
    }
}

//--------------------------------------------------------------
void ofApp::exit() {
    ofSoundStreamStop();
    ofSoundStreamClose();
}

//--------------------------------------------------------------
void ofApp::audioReceived(float * input, int bufferSize, int nChannels) {
    pitch.audioIn(input, bufferSize, nChannels);
	pd.audioIn(input, bufferSize, nChannels);
}

//--------------------------------------------------------------
void ofApp::audioRequested(float * output, int bufferSize, int nChannels) {
	pd.audioOut(output, bufferSize, nChannels);
}

//--------------------------------------------------------------
void ofApp::print(const std::string& message) {
	cout << message << endl;
}

//--------------------------------------------------------------
string ofApp::midiToNote(int midi) {
    string noteName;
    int mod = midi % 12;
    
    switch (mod){
        case 0:
            noteName = "C";
            break;
        case 1:
            noteName = "C#";
            break;
        case 2:
            noteName = "D";
            break;
        case 3:
            noteName = "D#";
            break;
        case 4:
            noteName = "E";
            break;
        case 5:
            noteName = "F";
            break;
        case 6:
            noteName = "F#";
            break;
        case 7:
            noteName = "G";
            break;
        case 8:
            noteName = "G#";
            break;
        case 9:
            noteName = "A";
            break;
        case 10:
            noteName = "Bb";
            break;
        case 11:
            noteName = "B";
            break;
        default:
            break;
    }
    
    return (noteName);
}

