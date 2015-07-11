//
//  EQplayer.h
//  soundPlayerExample
//
//  Created by Martin Hermant on 05/07/2015.
//
// dsp routine adapted from :
// Neil C / Etanza Systems / 2K6
// http://www.musicdsp.org/archive.php?classid=3#236

#ifndef __soundPlayerExample__EQplayer__
#define __soundPlayerExample__EQplayer__

#include "ofSoundPlayer.h"

#define MAX_CHANNELS 2

class EQPlayer: public ofSoundPlayer{
    
public:
    EQPlayer();
    
    // override of ofSoundPlayer
    void play();
    
    
    // Setters
    void setLowGain(float g){lg = g;};
    void setMidGain(float g){mg = g;};
    void setHighGain(float g){hg = g;};
    
    void setLowFreq(float f){lowFreq = f ; updateTimes();}
    void setHighFreq(float f){highFreq = f ; updateTimes();}
    
private:
    
    // eq state
    
    void updateTimes();
    float lowFreq = 600;
    float highFreq = 1000;
    
    
    // Filter #1 (Low band)
    
    double  lf;       // Frequency
    double  f1p0[MAX_CHANNELS];     // Poles ...
    double  f1p1[MAX_CHANNELS];
    double  f1p2[MAX_CHANNELS];
    double  f1p3[MAX_CHANNELS];
    
    // Filter #2 (High band)
    
    double  hf;       // Frequency
    double  f2p0[MAX_CHANNELS];     // Poles ...
    double  f2p1[MAX_CHANNELS];
    double  f2p2[MAX_CHANNELS];
    double  f2p3[MAX_CHANNELS];
    
    // Sample history buffer
    
    double  sdm1[MAX_CHANNELS];     // Sample data minus 1
    double  sdm2[MAX_CHANNELS];     //                   2
    double  sdm3[MAX_CHANNELS];     //                   3
    
    // Gain Controls
    
    double  lg;       // low  gain
    double  mg;       // mid  gain
    double  hg;       // high gain
    
    
    
    // fmod
    
    static FMOD_RESULT myDSPCallback(FMOD_DSP_STATE *dsp_state, float *inbuffer, float *outbuffer, unsigned int length, int inchannels, int outchannels);
    
    shared_ptr<ofFmodSoundPlayer>  fmodPlayer;
    FMOD_DSP * myDSP;
    
    
};

#endif /* defined(__soundPlayerExample__EQplayer__) */
