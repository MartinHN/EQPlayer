//
//  EQplayer.cpp
//  soundPlayerExample
//
//  Created by Martin Hermant on 05/07/2015.
//
//

#include "EQplayer.h"
#include "ofFmodSoundPlayer.cpp"

EQPlayer::EQPlayer(){
    
    ofFmodSoundPlayer::initializeFmod();
    fmodPlayer = dynamic_pointer_cast<ofFmodSoundPlayer>( player);
    /*
     Create the DSP effect.
     */
    {
        FMOD_DSP_DESCRIPTION dspdesc;
        memset(&dspdesc, 0, sizeof(dspdesc));
        dspdesc.read = EQPlayer::myDSPCallback;
        dspdesc.userdata = (void *)this;
        FMOD_System_CreateDSP(sys,&dspdesc,&myDSP);
    }
    
    
    // Set init value
    lowFreq = 600;
    highFreq = 1000;
    lg = 1.0;
    mg = 1.0;
    hg = 1.0;
    updateTimes();
    
};

void EQPlayer::updateTimes(){
    // Calculate filter cutoff frequencies in sample domain
    lf = 2 * sin(M_PI * ((double)lowFreq / (double)fmodPlayer->internalFreq));
    hf = 2 * sin(M_PI * ((double)highFreq / (double)fmodPlayer->internalFreq));
};




void EQPlayer::play(){
    ofSoundPlayer::play();
    // new channel at each play so we need to reconnect
    FMOD_Channel_AddDSP(fmodPlayer->channel, myDSP, 0);
}


FMOD_RESULT  EQPlayer::myDSPCallback(FMOD_DSP_STATE *dsp_state, float *inbuffer, float *outbuffer, unsigned int length, int inchannels, int outchannels)
{
    FMOD_RESULT result;
    char name[256];
    EQPlayer* me;
    
    // get back current player
    FMOD_DSP_GetUserData(dsp_state->instance,(void **)&me);


    /*
     This loop assumes inchannels = outchannels, which it will be if the DSP is created with '0'
     as the number of channels in FMOD_DSP_DESCRIPTION.
     Specifying an actual channel count will mean you have to take care of any number of channels coming in,
     but outputting the number of channels specified. Generally it is best to keep the channel
     count at 0 for maximum compatibility.
     */
    
    static float jitter = (float)1E-20;
    
    for (unsigned int samp = 0; samp < length; samp++)
    {
        for (int ch = 0; ch < outchannels; ch++)
        {
            
            float  sample = inbuffer[(samp * inchannels) + ch];
            // Locals
            
            double  l,m,h;      // Low / Mid / High - Sample Values
            
            // Filter #1 (lowpass)
            
            me->f1p0[ch]  += (me->lf * (sample   - me->f1p0[ch])) + jitter;
            me->f1p1[ch]  += (me->lf * (me->f1p0[ch] - me->f1p1[ch]));
            me->f1p2[ch]  += (me->lf * (me->f1p1[ch] - me->f1p2[ch]));
            me->f1p3[ch]  += (me->lf * (me->f1p2[ch] - me->f1p3[ch]));
            
            l = me->f1p3[ch];
            
            // Filter #2 (highpass)
            
            me->f2p0[ch]  += (me->hf * (sample   - me->f2p0[ch])) + jitter;
            me->f2p1[ch]  += (me->hf * (me->f2p0[ch] - me->f2p1[ch]));
            me->f2p2[ch]  += (me->hf * (me->f2p1[ch] - me->f2p2[ch]));
            me->f2p3[ch]  += (me->hf * (me->f2p2[ch] - me->f2p3[ch]));
            
            h = me->sdm3[ch] - me->f2p3[ch];
            
            // Calculate midrange (signal - (low + high))
            
            m  = me->sdm3[ch] - (h + l);
            
            // Scale, Combine and store
            
            l         *= me->lg;
            m         *= me->mg;
            h         *= me->hg;
            
            // Shuffle history buffer
            
            me->sdm3[ch]   = me->sdm2[ch];
            me->sdm2[ch]   = me->sdm1[ch];
            me->sdm1[ch]   = sample;
            
            // Return result
            
            outbuffer[(samp * outchannels) + ch] = (l + m + h);
        }
        jitter = -jitter;
    }
    
    return FMOD_OK;
}




