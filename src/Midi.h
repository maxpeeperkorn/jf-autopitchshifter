//
//  midi.h
//  autoPitchShifter
//
//  Created by Max Peeperkorn on 20/12/2017.
//

#ifndef midi_h
#define midi_h

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <map>

#include "ofMain.h"
#include "ofXml.h"

using namespace std;

//typedef tuple<string, float> midiValue;
//typedef pair<int, midiValue> tMidiPair;

typedef map<int, string> tMidiMap;

class Midi {
    
    public:
        // -- initialization
        void setup();
    
        // -- variables
        map<int, string> midiMap;
        map<int, float> transpositionMap;
    
        string latestNote;
        float latestTransposition;
    
        // -- methods
        float getNoteTransposition(int midi);
        string getNotePitchName(int midi);  // Pitch Notation, ie: C2, F#3
        string getNoteName(int midi);       // General Notation, ie: C, F#
    
    private:
    
};


#endif /* midi_h */
