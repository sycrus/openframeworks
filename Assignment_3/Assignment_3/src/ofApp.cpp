#include "ofApp.h"

//face variables
ofRectangle face;
ofRectangle faceOutline;
int faceWidth = 170;
int faceHeight = 110;

int strokeThickness = 15;

int eyeDistanceX = 45;
int eyeDistanceY = 2;
int eyeSize = 12;

int eyebrowDistanceX = 33;
int eyebrowDistanceY = 32;
int eyebrowWidth = 30;
int eyebrowHeight = 13;

int noseWidth = 28;
int noseHeight = 20;

int mouthWidth = 26;

//tree variables
int treeSize = 50;
int trunkWidth = 30;
int trunkHeight = 80;

//controls
int slideNumber = 0;

//palette
ofColor red(255,0,0);
ofColor black(0,0,0);
ofColor white(255,255,255);
ofColor green(0, 255, 0);

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    
    ofSetCircleResolution(100);
    ofEnableSmoothing();
    
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(0, 255, 255);
    if (slideNumber == 0) {
        drawFace(ofGetWidth()/2, ofGetHeight()/2);
    }
    if (slideNumber == 1) {
          drawTree(ofGetWidth()/2, ofGetHeight()/2 - 60);
   }
    if (slideNumber == 2) {
           drawCat(ofGetWidth()/2, ofGetHeight()/2);
   }
    if (slideNumber == 3) {
            drawMountain(ofGetWidth()/2, ofGetHeight()/2 - 60);
    }
    
    if ((ofGetFrameNum() % 120) == 0) {
        if (slideNumber > 2){
            slideNumber = 0;
        } else {
            slideNumber++;
        }
    }

      ofLog(OF_LOG_NOTICE, ofToString(slideNumber));
    
    
        
    
}

void ofApp::drawMountain(int x, int y) {
    ofSetColor(black);
    //center outline
    ofDrawTriangle(x , y - 60,
                   x - 140, y + 150,
                   x + 140, y + 150);
    
    //left outline
    ofDrawTriangle(x -  80 , y - 10,
                   x - 210, y + 150,
                   x + 50, y + 150);
    
    
    //right outline
    ofDrawTriangle(x +  80 , y - 10,
                   x + 210, y + 150,
                   x - 50, y + 150);
    
    //center peak
    ofSetColor(white);
   ofDrawTriangle(x , y - 30,
                  x - 60, y + 60,
                  x + 60, y + 60);
    //left peak
    
    ofDrawTriangle(x -  80 , y + 10,
                   x - 110, y + 50,
                   x - 50, y + 50);
    
    //right peak
    ofDrawTriangle(x +  80 , y + 10,
                   x + 110, y + 50,
                   x + 50, y + 50);
    
}

void ofApp::drawCat(int x, int y) {
    
     //face
     ofSetColor(black);
     faceOutline.width = faceWidth + (2 * strokeThickness);
     faceOutline.height = faceHeight + (2 * strokeThickness);
     faceOutline.x =  x - (faceOutline.width/2);
     faceOutline.y = y - (faceOutline.height/2);
     ofDrawRectRounded(faceOutline, 80);
     
    //left ear
    ofDrawTriangle(x - faceWidth/2 - strokeThickness, y - 100,
                   x - faceWidth/2 - strokeThickness, y,
                   x + faceWidth/4, y + faceHeight/3);
    //right ear
    ofDrawTriangle(x + faceWidth/2 + strokeThickness, y - 100,
                   x + faceWidth/2 + strokeThickness, y,
                   x - faceWidth/4, y + faceHeight/3);
     //left eye
     ofSetColor(white);
     ofDrawCircle(x- eyeDistanceX , y - eyeDistanceY , eyeSize);
     //right eye
     ofDrawCircle(x + eyeDistanceX , y - eyeDistanceY , eyeSize);
     
     
     //nose
     ofDrawTriangle(x - noseWidth/2, y - noseHeight/2,
                    x + noseWidth/2, y - noseHeight/2,
                    x, y + noseHeight/2);
     
     //mouth
     ofPath mouth1;
     mouth1.arc(x - mouthWidth/2 , y + 10, mouthWidth/2, mouthWidth/2, 0, 150);
     mouth1.setFilled(false);
     mouth1.setStrokeWidth(5);
     mouth1.setStrokeColor(white);
     mouth1.setCurveResolution(500);
     mouth1.draw();
    
    ofPath mouth2;
    mouth2.arc(x + mouthWidth/2 + 2 , y + 10, mouthWidth/2, mouthWidth/2, 30, 180);
    mouth2.setFilled(false);
    mouth2.setStrokeWidth(5);
    mouth2.setStrokeColor(white);
    mouth2.setCurveResolution(500);
    mouth2.draw();
    
}

void ofApp::drawTree(int x, int y) {

    //trunk
    ofSetColor(black);
    ofDrawRectangle(x - trunkWidth/2 , y + 150, trunkWidth, trunkHeight);
    
    //outline of tree
    ofDrawCircle(x , y , treeSize + strokeThickness);
    ofDrawCircle(x , y + 50 + strokeThickness , treeSize + strokeThickness);
    ofDrawCircle(x , y + 100 + strokeThickness, treeSize + strokeThickness);
    
    //foliage
    ofSetColor(white);
    ofDrawCircle(x , y , treeSize);
    ofDrawCircle(x , y + 50 + strokeThickness , treeSize);
    ofDrawCircle(x , y + 100 + strokeThickness, treeSize);
    
}

void ofApp::drawFace(int targetX, int targetY) {
     //outline of face
        ofSetColor(black);
        faceOutline.width = faceWidth + (2 * strokeThickness);
        faceOutline.height = faceHeight + (2 * strokeThickness);
        faceOutline.x =  targetX - (faceOutline.width/2);
        faceOutline.y = targetY - (faceOutline.height/2);
        ofDrawRectRounded(faceOutline, 80);
        
        //face
        ofSetColor(white);
        face.width = faceWidth;
        face.height = faceHeight;
        face.x = targetX - faceWidth/2;
        face.y = targetY - faceHeight/2;
        ofDrawRectRounded(face, 80);
        
        //left eye
        ofSetColor(black);
        ofDrawCircle(targetX - eyeDistanceX , targetY - eyeDistanceY , eyeSize);
        //right eye
        ofDrawCircle(targetX + eyeDistanceX , targetY - eyeDistanceY , eyeSize);
        
        //left eyebrow
        ofDrawRectangle(targetX - eyebrowDistanceX - eyebrowWidth,  targetY - eyebrowDistanceY, eyebrowWidth, eyebrowHeight);
        //right eyebrow
        ofDrawRectangle(targetX + eyebrowDistanceX, targetY - eyebrowDistanceY, eyebrowWidth, eyebrowHeight);
        
        //nose
        ofDrawTriangle(targetX, targetY - noseHeight/2,
                       targetX - noseWidth/2, targetY + noseHeight/2,
                       targetX + noseWidth/2, targetY + noseHeight/2);
        
        //mouth
        ofPath mouth;
        mouth.arc(targetX, targetY + 20, mouthWidth/2, mouthWidth/2, 0, 180);
        mouth.setFilled(true);
        mouth.setFillColor(black);
        mouth.draw();
       
        //anchor for reference
    //    ofSetColor(red);
    //    ofDrawCircle(targetX , targetY, 5);
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
