#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofFileDialogResult result = ofxNative :: systemLoadDialog("Choose image to load", false, ofToDataPath(""), {"jpg", "jpeg", "png"});
    
    if(result.bSuccess) {
        loadedImage.load(result.getPath());
    }
    
    message = "Mouse click to open save dialog";
    
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    ofFill();
    ofDrawBitmapString(message, 0, 15);
    loadedImage.draw(0,20);
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
    ofFileDialogResult result = ofxNative :: systemSaveDialog("test.txt", "Choose file to save", {"txt", "rtf"});
    if(result.bSuccess) {
        message = result.getPath();
    }
    
}
