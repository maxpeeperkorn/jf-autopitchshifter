//
//  gui.cpp
//  autoPitchShifter
//
//  Created by Max Peeperkorn on 19/12/2017.
//

#include "GuiRenderer.h"

void GuiRenderer::setup() {
    guiGroup.setup();
    guiGroup.setName("Settings");
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
}

void GuiRenderer::render() {
    guiGroup.draw();
}




