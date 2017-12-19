//
//  gui.h
//  autoPitchShifter
//
//  Created by Max Peeperkorn on 19/12/2017.
//

#ifndef GuiRenderer_h
#define GuiRenderer_h

#include "ofMain.h"
#include "ofxGui.h"

class GuiRenderer {
    public:
        void setup();
        void render();
    
    
        ofxGuiGroup guiGroup;
    
        ofParameterGroup parameters;
        ofParameter<string> pitchDetect, pitchShift;
    
        ofParameter<float> midiPitch, pitchConfidence;
        ofParameter<float> transpose, mix, inGain, outGain;
    
        ofParameter<float> confidence;
    
        vector<ofSoundDevice> inputDevices;
        vector<ofSoundDevice> outputDevices;
};


#endif /* GuiRenderer_h */
