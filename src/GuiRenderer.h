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
#include "ofxDatGui.h"

class GuiRenderer {
    public:
        void setup(ofSoundStream soundstream);
        void update();
        void render();
    
        ofSoundStream soundstream;
    
        vector<ofSoundDevice> inputDevices;
        vector<ofSoundDevice> outputDevices;
    
        ofxGuiGroup guiGroup;
    
        ofParameterGroup parameters;
        ofParameter<string> pitchDetect, pitchShift;
    
        ofParameter<float> midiPitch, pitchConfidence;
        ofParameter<float> transpose, mix, inGain, outGain;
        ofParameter<float> confidence;
    
        ofxDatGuiDropdown* inputDevicesMenu;
        ofxDatGuiDropdown* outputDevicesMenu;
    
        vector<string> listSoundDevicesByName(vector<ofSoundDevice> soundDevices);
        ofSoundDevice getSoundDeviceByName(vector<ofSoundDevice> soundDevices, string deviceName);
    
        void onDropdownInputsEvent(ofxDatGuiDropdownEvent e);
        void onDropdownOutputsEvent(ofxDatGuiDropdownEvent e);
};


#endif /* GuiRenderer_h */
