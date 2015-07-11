#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    synth.loadSound("sounds/synth.wav");
    beats.loadSound("sounds/1085.mp3");
    vocals.loadSound("sounds/Violet.mp3");
    synth.setVolume(0.75f);
    beats.setVolume(0.75f);
    vocals.setVolume(0.5f);
    font.load("Sudbury_Basin_3D.ttf", 32);
    beats.setMultiPlay(false);
    vocals.setMultiPlay(true);
    
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    ofBackground(255,255,255);
    
    // update the sound playing system:
    ofSoundUpdate();
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    // draw the background colors:
    float widthDiv = ofGetWidth() / 3.0f;
    ofSetHexColor(0xeeeeee);
    ofDrawRectangle(0,0,widthDiv,ofGetHeight());
    ofSetHexColor(0xffffff);
    ofDrawRectangle(widthDiv,0,widthDiv,ofGetHeight());
    ofSetHexColor(0xdddddd);
    ofDrawRectangle(widthDiv*2,0,widthDiv,ofGetHeight());
    
    
    //---------------------------------- synth:
    if (synth.getIsPlaying()) ofSetHexColor(0xFF0000);
    else ofSetHexColor(0x000000);
    font.drawString("synth !!", 50,50);
    
    ofSetHexColor(0x000000);
    string tempStr = "click to play\npct done: "+ofToString(synth.getPosition())+"\nspeed: " + ofToString(synth.getSpeed()) + "\npan: " + ofToString(synth.getPan()) ;
    ofDrawBitmapString(tempStr, 50,ofGetHeight()-50);
    
    
    
    //---------------------------------- beats:
    if (beats.getIsPlaying()) ofSetHexColor(0xFF0000);
    else ofSetHexColor(0x000000);
    font.drawString("beats !!", widthDiv+50,50);
    
    ofSetHexColor(0x000000);
    tempStr = "click and drag\npct done: "+ofToString(beats.getPosition())+"\nspeed: " +ofToString(beats.getSpeed());
    ofDrawBitmapString(tempStr, widthDiv+50,ofGetHeight()-50);
    
    //---------------------------------- vocals:
    if (vocals.getIsPlaying()) ofSetHexColor(0xFF0000);
    else ofSetHexColor(0x000000);
    font.drawString("vocals !!", widthDiv*2+50,50);
    
    ofSetHexColor(0x000000);
    tempStr = "click to play (multiplay)\npct done: "+ofToString(vocals.getPosition())+"\nspeed: " + ofToString(vocals.getSpeed());
    ofDrawBitmapString(tempStr, widthDiv*2+50,ofGetHeight()-50);
    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed  (int key){
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    // continuously control the speed of the beat sample via drag,
    // when in the "beat" region:
    float widthStep = ofGetWidth() / 3.0f;
    int ca = x/widthStep;
    float gain= y*1.0/ofGetHeight();
    switch(ca){
        case 0:
            synth.setHighGain(gain);
            break;
        case 1:
            beats.setHighGain(gain);

            break;
        case 2:
            vocals.setHighGain(gain);
            break;
    }
    
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    float widthStep = ofGetWidth() / 3.0f;
    int ca = x/widthStep;
    float gain= y*1.0/ofGetHeight();
    switch(ca){
        case 0:
            synth.play();
            break;
        case 1:
            beats.play();
            
            break;
        case 2:
            vocals.play();
            break;
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
