#include "ofApp.h"

//palette
ofColor red(255,0,0);
ofColor black(0,0,0);
ofColor white(255,255,255);
ofColor green(0, 255, 0);
ofColor gray(128, 128, 128);
ofColor cyan(0, 255, 255);
ofColor yellow(255, 255, 0);
ofColor pink(255, 192, 203);

ofVec3f textOffset(50, 50, 0);
ofVec3f torsoOffset(0, 55, 0);
ofVec3f streetLineOffset(0, 500, 0);


//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofSetCircleResolution(100);
    ofEnableSmoothing();
    
    futura.load("Futura.ttc", 30);
    
    fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA32F_ARB); // higher precision alpha (no artifacts)
    fbo.begin();
    ofClear(255,255,255, 0);
    fbo.end();
    
    initializeWorld();
    initializePerson();
    
    currVec.set(ofGetWidth() - 100, 100, 0);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    ofEnableAlphaBlending();
    
    fbo.begin();
        //for fbo
        ofFill();
        ofSetColor(255,255,255, 1);
        ofDrawRectangle(ofGetWidth()/2,ofGetHeight()/2,ofGetWidth(),ofGetHeight());
        
        drawText(textOffset);
        drawStar(currVec, 100, 90, 10);
        drawWorld(worldPosition);
        drawTorso(torsoAnchor);
        drawFace(headAnchor);
        drawLegs(hipAnchor);
    fbo.end();
    
    //update person
    headAnchor.set(ofGetWidth()/2, ofGetHeight()/2 + bobOffset * sin(vertMoveAngle), 0);
    torsoAnchor = headAnchor + torsoOffset;
    hipAnchor = torsoAnchor + hipOffset;
    
    if (moveRight) {
        worldAngle -= 1;
        vertMoveAngle -= 0.5;
        
        thetaLeft = thetaLeft + leftDirection * handSpeed;
        thetaRight = thetaRight + rightDirection * handSpeed;
        if (thetaLeft > 50 || thetaLeft < -50 ) {
            leftDirection *= -1;
        }
        if (thetaRight > 50 || thetaRight < -50 ) {
            rightDirection *= -1;
        }
    }
    if (moveLeft) {
        worldAngle += 1;
        vertMoveAngle += 0.5;
        
        thetaLeft = thetaLeft + leftDirection * handSpeed;
        thetaRight = thetaRight + rightDirection * handSpeed;
        if (thetaLeft > 50 || thetaLeft < -50 ) {
            leftDirection *= -1;
        }
        if (thetaRight > 50 || thetaRight < -50 ) {
            rightDirection *= -1;
        }
    }
    
    //update sun
    if (targetVec != currVec) {
        currVec = currVec + (targetVec - currVec) * 0.2;
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(cyan);
    
    if (useFbo) {
        fbo.draw(ofGetWidth()/2,ofGetHeight()/2);
    } else {
        drawText(textOffset);
        drawStar(currVec, 100, 90, 10);
        drawWorld(worldPosition);
        drawTorso(torsoAnchor);
        drawFace(headAnchor);
        drawLegs(hipAnchor);
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'a') {
        moveLeft = true;
    }
    if(key == 'd') {
        moveRight = true;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if(key == 'a') {
        moveLeft = false;
    }
    if(key == 'd') {
        moveRight = false;
    }
    if(key == 'f') {
        useFbo = !useFbo;
        fbo.begin();
            ofClear(255,255,255, 0);
        fbo.end();
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    targetVec.set(x, y, 0);
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

void ofApp::initializeWorld() {
     worldPosition.set(ofGetWidth()/2, ofGetHeight() + 280);
}

void ofApp::initializePerson() {
    faceColor = white;
    faceOutlineColor = black;
    
    leftEyeOffset.set(-eyeDistanceX, eyeDistanceY, 0);
    rightEyeOffset.set(eyeDistanceX, eyeDistanceY, 0);
    
    leftEyebrowOffset.set(-eyeDistanceX, -eyebrowDistanceY, 0);
    rightEyebrowOffset.set(eyeDistanceX, -eyebrowDistanceY, 0);
    
    topNoseOffset.set(0, -noseHeight/2, 0);
    leftNoseOffset.set(-noseWidth/2, noseHeight/2, 0);
    rightNoseOffset.set(noseWidth/2, noseHeight/2, 0);
    
    topTorsoOffset.set(0, 0, 0);
    leftTorsoOffset.set(-torsoWidth/2, torsoHeight, 0);
    rightTorsoOffset.set(torsoWidth/2, torsoHeight, 0);
    
    leftHandOffset.set(0, handArcRadius, 0);
    rightHandOffset.set(0, handArcRadius, 0);
    
    hipOffset.set(0, torsoHeight - 10, 0);
    
    leftFootOffset.set(0, footArcRadius, 0);
    rightFootOffset.set(0, footArcRadius, 0);
    leftFrontFootOffset.set(frontFootRadius - 7, 0, 0);
    rightFrontFootOffset.set(frontFootRadius - 7, 0, 0);
}
void ofApp::drawText(ofVec3f position) {
    ofSetColor(black);
    futura.drawString("Adventures", position.x, 100);
    futura.drawString("of", position.x, 145);
    futura.drawString("Derpy",position.x, 190);
    futura.drawString("McDerpface", position.x, 235);
}

void ofApp::drawWorld(ofVec3f position) {
    ofSetColor(black);
    ofDrawCircle(position, 550);
    
    ofSetColor(white);
    ofDrawCircle(position, 550 - strokeThickness);
    
    ofSetColor(black);
    ofDrawCircle(position, 400);
    
    //draws streetlines
    streetLineOffset.set(0, 500, 0);
    ofSetColor(black);
    ofSetRectMode(OF_RECTMODE_CENTER);
    for (int i = 0; i < 360; i += 20) {
        ofPushMatrix();
        ofTranslate(position);
        ofRotateDeg(i + worldAngle);
        ofDrawRectangle(streetLineOffset, 60, 20);
        ofPopMatrix();
    }
}

void ofApp::drawFace(ofVec3f position) {
    //outline of face
    ofSetColor(faceOutlineColor);
    ofDrawCircle(position, faceWidth/2 + strokeThickness);
    
    //face
    ofSetColor(faceColor);
    ofDrawCircle(position, faceWidth/2);
    
    //eyes
    ofSetColor(faceOutlineColor);
    ofDrawCircle(leftEyeOffset + position, eyeSize);
    ofDrawCircle(rightEyeOffset + position, eyeSize);
    
    //eyebrows
    ofDrawRectangle(leftEyebrowOffset + position, eyebrowWidth, eyebrowHeight);
    ofDrawRectangle(rightEyebrowOffset + position, eyebrowWidth, eyebrowHeight);
    
    //nose
    ofDrawTriangle(topNoseOffset + position, leftNoseOffset + position, rightNoseOffset + position) ;
    
}

void ofApp::drawTorso(ofVec3f position) {
    //left hand
    ofSetColor(black);
    ofPushMatrix();
    ofTranslate(position);
    ofRotateDeg(thetaLeft);
    ofDrawCircle(leftHandOffset, handRadius);
    ofPopMatrix();
    
    //torso
    ofSetColor(black);
    ofDrawTriangle(topTorsoOffset + position, leftTorsoOffset + position, rightTorsoOffset + position);
    
    //right hand
    ofPushMatrix();
    ofTranslate(position);
    ofRotateDeg(thetaRight);
    ofSetColor(black);
    ofDrawCircle(rightHandOffset, handRadius);
    ofSetColor(white);
    ofDrawCircle(rightHandOffset, handRadius - strokeThickness/2);
    ofPopMatrix();
    
}

void ofApp::drawLegs(ofVec3f position) {
    //left leg
    ofSetColor(black);
    ofPushMatrix();
    ofTranslate(position);
    ofRotateDeg(thetaRight);
    //ofSetRectMode(OF_RECTMODE_CENTER);
    ofDrawRectangle(rightFootOffset, footWidth, frontFootRadius * 2);
    ofDrawCircle(rightFootOffset + rightFrontFootOffset, frontFootRadius);
    ofPopMatrix();
    
    //right leg
    ofPushMatrix();
    ofTranslate(position);
    ofRotateDeg(thetaLeft);
    ofSetColor(black);
    ofDrawRectangle(leftFootOffset, footWidth, frontFootRadius * 2);
    ofDrawCircle(leftFootOffset + leftFrontFootOffset, frontFootRadius);
    
    ofSetColor(white);
    ofDrawCircle(leftFootOffset + leftFrontFootOffset,
                 frontFootRadius - strokeThickness/2);
    ofDrawRectangle(leftFootOffset,
                    footWidth - strokeThickness,
                    frontFootRadius - strokeThickness/4 + 7);
    ofPopMatrix();
    
}

void ofApp::drawStar(ofVec3f position, float r1, float r2, int vertices) {
    float alpha = 2 * PI / vertices;
    float i = PI/2;
    float revolution = 5 * PI/2;
    
    //outer star
    ofSetColor(yellow);
    ofPolyline star;
    while ( i < revolution ) {
        star.addVertex(ofVec3f(position.x + cos(i) * r1,
                               position.y + sin(i) * r1, 0));
        
        star.addVertex(ofVec3f(position.x + cos(i + alpha/2) * r2,
                               position.y + sin(i + alpha/2) * r2, 0));
        i += alpha;
    }
    star.close();
    star.draw();
    ofBeginShape();
    for( int i = 0; i < star.getVertices().size(); i++) {
        ofVertex(star.getVertices().at(i).x, star.getVertices().at(i).y);
    }
    ofEndShape();
    
    //inner star
    ofSetColor(black);
    ofDrawCircle(position, r2 - 20);
    
    ofSetColor(white);
    ofDrawCircle(position, r2 - 40);
}



