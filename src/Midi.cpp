//
//  midi.cpp
//  autoPitchShifter
//
//  Created by Max Peeperkorn on 20/12/2017.
//

#include "Midi.h"

void Midi::setup() {
    ofFile file;
    file.open("miditable.xml");

    ofBuffer buffer = file.readToBuffer();
    
    ofXml midiTable;
    midiTable.loadFromBuffer( buffer.getText() );
    
    midiTable.setTo("miditable");
    
    int nNotes = midiTable.getNumChildren();
    
    for (int i = 0; i < nNotes; i++) {
        midiTable.setToChild(i);
        
        int noteNumber = midiTable.getIntValue("number");
        string noteName = midiTable.getValue("name");
        float noteTransposition = midiTable.getFloatValue("transpose");
        
        midiMap.insert(make_pair(noteNumber, noteName));
        transpositionMap.insert(make_pair(noteNumber, noteTransposition));
        
        midiTable.setToParent();
    }
}

float Midi::getNoteTransposition(int midi) {
    map<int, float>::iterator it = transpositionMap.find(midi);
    
    if (midi == it->first) {
        return it->second;
    }
}

string Midi::getNotePitchName(int midi) {
    map<int, string>::iterator it = midiMap.find(midi);
    
    if (midi == it->first) {
        return it->second;
    }
}

string Midi::getNoteName(int midi) {
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


