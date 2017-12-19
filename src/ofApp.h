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

#pragma once

#include "ofMain.h"

#include "ofxPd.h"
#include "ofxSimpleSlider.h"
#include "ofxAubio.h"
#include "ofxGui.h"

#include <string>
#include <map>
#include <tuple>

// a namespace for the Pd types
using namespace pd;

typedef std::tuple<string, float> midiValue;
typedef std::map<int, string> tMidiMap;
typedef std::pair<int, midiValue> tMidiPair;

class ofApp : public ofBaseApp, public PdReceiver {

	public:
		// main
		void setup();
		void update();
		void draw();
        void exit();
		
		// input callbacks
		void keyPressed(int key);
    
        // soundstream
        int sampleRate;
        int bufferSize;
        int nBuffers;
		
		// audio callbacks
        ofSoundStream soundstream;
    
        vector<ofSoundDevice> inputDevices;
        vector<ofSoundDevice> outputDevices;
    
		void audioReceived(float * input, int bufferSize, int nChannels);
		void audioRequested(float * output, int bufferSize, int nChannels);
    
		// pd message receiver callbacks
		void print(const std::string& message);
		
		ofxPd pd;	//< pd instance
		vector<float> scopeArray;

		// gui
        ofxGuiGroup gui;
    
        ofParameterGroup parameters;
        ofParameter<string> pitchDetect, pitchShift;
    
        ofParameter<float> midiPitch, pitchConfidence;
        ofParameter<float> transpose, mix, inGain, outGain;
    
        ofParameter<float> confidence;
    
        ofXml settings;
    
    
        // aubio pitch detection / note conversion
        ofxAubioPitch pitch;
    
        string midiToNote(int midi);
        string latestNote;
    
        tMidiMap midiMap;
};
