//
//  gui.cpp
//  autoPitchShifter
//
//  Created by Max Peeperkorn on 19/12/2017.
//

#include "GuiRenderer.h"

void GuiRenderer::setup(ofSoundStream soundstream) {
    soundstream = soundstream;
    
    inputDevices = soundstream.getMatchingDevices("", 2, 0);
    outputDevices = soundstream.getMatchingDevices("", 0, 2);
    
    ofLog() << inputDevices.size();
    
    guiGroup.setup();
    guiGroup.setName("Settings");
    guiGroup.setPosition(792, 20);
    
    // -- Pitch Detection Variables
    
    guiGroup.add(pitchDetect.set("Pitch Detect"));
    
    guiGroup.add(midiPitch.set("Midi Pitch", 0, 0, 128));
    guiGroup.add(pitchConfidence.set("Confidence", 0, 0, 1));
    guiGroup.add(confidence.set("Confidence Level", 0.64, 0, 1));
    
    // -- Pitch Shifting Variables
    
    guiGroup.add(pitchShift.set("Pitch Shift"));
    
    guiGroup.add(transpose.set("Transpose", 0, -1, 1));
    guiGroup.add(mix.set("Wet/Dry Mix", 1, 0, 1));
    guiGroup.add(inGain.set("Input Gain", 0.5, 0, 1));
    guiGroup.add(outGain.set("Output Gain", 0.5, 0, 1));
    
    // -- Input / Output Variables
    
    inputDevicesMenu = new ofxDatGuiDropdown("Inputs", listSoundDevicesByName(inputDevices));
    inputDevicesMenu->setPosition(32, 48);
    inputDevicesMenu->onDropdownEvent(this, &GuiRenderer::onDropdownInputsEvent);
    
    outputDevicesMenu = new ofxDatGuiDropdown("Outputs", listSoundDevicesByName(outputDevices));
    outputDevicesMenu->setPosition(316, 48);
    outputDevicesMenu->onDropdownEvent(this, &GuiRenderer::onDropdownOutputsEvent);
}
void GuiRenderer::update() {
    inputDevicesMenu->update();
    outputDevicesMenu->update();
}

void GuiRenderer::render() {
    inputDevicesMenu->draw();
    outputDevicesMenu->draw();
    
    guiGroup.draw();
}

vector<string> GuiRenderer::listSoundDevicesByName(vector<ofSoundDevice> soundDevices) {
    vector<string> soundDevicesByName;
    soundDevicesByName.resize(soundDevices.size());
    
    for (int i = 0; i < soundDevices.size(); i++) {
        soundDevicesByName[i] = soundDevices[i].name;
    }
    
    return soundDevicesByName;
}
//
void GuiRenderer::onDropdownInputsEvent(ofxDatGuiDropdownEvent e) {
    ofLog() << e.child;
    
    soundstream.setDevice(inputDevices[e.child]);
}

void GuiRenderer::onDropdownOutputsEvent(ofxDatGuiDropdownEvent e) {
    ofLog() << e.child;
    soundstream.setDevice(outputDevices[e.child]);
}


