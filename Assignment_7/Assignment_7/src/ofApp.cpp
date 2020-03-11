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

ofVec2f textOffset(50, 50);
ofVec2f torsoOffset(0, 55);
ofVec2f streetLineOffset(0, 500);


//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofSetCircleResolution(100);
    ofEnableSmoothing();
    
    bgm.load("lymeko.aiff");
    bgm.play();
    bgm.setLoop(true);
    bgm.setVolume(bgmVolume);
    
    volumeFloatSlider.addListener(this, &ofApp::volumeFloatSliderChanged);
    changeExpressionButton.addListener(this, &ofApp::changeExpressionButtonPressed);
    
    gui.setup(); // most of the time you don't need a name
    gui.add(volumeFloatSlider.setup("volume", 0.2f, 0.0f, 1.0f));
    gui.add(backgroundColorSlider.setup("color", ofColor(100, 100, 140), ofColor(0, 0), ofColor(255, 255)));
    gui.add(sunVecSlider.setup("sun position",ofVec2f(ofGetWidth()*.5, ofGetHeight()*.25), ofVec2f(0, 0), ofVec2f(ofGetWidth(), ofGetHeight())));
    gui.add(changeExpressionButton.setup("change expression"));
    gui.add(emotionalIntSlider.setup("emotional", 5, 0, 10));
    
    initializeWorld();
    initializePerson();
    
    currVec.set(ofGetWidth() - 100, 100);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    ofEnableAlphaBlending();
    
    //update person
    headAnchor.set(ofGetWidth()/2, ofGetHeight()/2 + bobOffset * sin(vertMoveAngle));
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
    ofBackground(backgroundColorSlider);
    
    drawText(textOffset);
    drawStar(ofPoint(sunVecSlider), 100, 90, 10);
    drawWorld(worldPosition);
    drawTorso(torsoAnchor);
    drawFace(headAnchor);
    
    if (emotionCounter == 0) {
        //screen auto cleared
    }
    if (emotionCounter == 1) {
        drawHappyParts(headAnchor, emotionalIntSlider);
    }
    if (emotionCounter == 2) {
        drawSadParts(headAnchor, emotionalIntSlider);
    }
    if (emotionCounter == 3) {
        drawAngryParts(headAnchor, emotionalIntSlider);
    }
    if (emotionCounter == 4) {
        drawSurprisedParts(headAnchor, emotionalIntSlider);
    }
    if (emotionCounter == 5) {
        emotionCounter = 0;
    }
    
    drawLegs(hipAnchor);
    
    gui.draw();
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
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    targetVec.set(x, y);
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

void ofApp::volumeFloatSliderChanged(float & volumeFloatSlider ) {
    bgm.setVolume(volumeFloatSlider);
}
void ofApp::changeExpressionButtonPressed() {
    emotionCounter++;
}

void ofApp::initializeWorld() {
     worldPosition.set(ofGetWidth()/2, ofGetHeight() + 280);
}

void ofApp::initializePerson() {
    faceColor = white;
    faceOutlineColor = black;
    
    initializeFace();
    
    topTorsoOffset.set(0, 0);
    leftTorsoOffset.set(-torsoWidth/2, torsoHeight);
    rightTorsoOffset.set(torsoWidth/2, torsoHeight);
    
    leftHandOffset.set(0, handArcRadius);
    rightHandOffset.set(0, handArcRadius);
    
    hipOffset.set(0, torsoHeight - 10);
    
    leftFootOffset.set(0, footArcRadius);
    rightFootOffset.set(0, footArcRadius);
    leftFrontFootOffset.set(frontFootRadius - 7, 0);
    rightFrontFootOffset.set(frontFootRadius - 7, 0);
}
void ofApp::initializeFace() {
    leftEyeOffset.set(-eyeDistanceX, eyeDistanceY);
    rightEyeOffset.set(eyeDistanceX, eyeDistanceY);
    
    leftEyebrowOffset.set(-eyeDistanceX, -eyebrowDistanceY);
    rightEyebrowOffset.set(eyeDistanceX, -eyebrowDistanceY);
    
    topNoseOffset.set(0, -noseHeight/2);
    leftNoseOffset.set(-noseWidth/2, noseHeight/2);
    rightNoseOffset.set(noseWidth/2, noseHeight/2);
    
    sadMouthOffset.set(0, noseHeight + 10);
    angryMouthOffset.set(0, noseHeight + 10);
    happyMouthOffset.set(0, noseHeight + 2);
    surprisedMouthOffset.set(0, noseHeight + 10);
}
void ofApp::drawText(ofVec2f position) {
    ofSetColor(black);
//    futura.drawString("Adventures", position.x, 100);
//    futura.drawString("of", position.x, 145);
//    futura.drawString("Derpy",position.x, 190);
//    futura.drawString("McDerpface", position.x, 235);
}

void ofApp::drawWorld(ofVec2f position) {
    ofSetColor(black);
    ofDrawCircle(position, 550);
    
    ofSetColor(white);
    ofDrawCircle(position, 550 - strokeThickness);
    
    ofSetColor(black);
    ofDrawCircle(position, 400);
    
    //draws streetlines
    streetLineOffset.set(0, 500);
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

void ofApp::drawFace(ofVec2f position) {
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
    
    //nose
    ofDrawTriangle(topNoseOffset + position, leftNoseOffset + position, rightNoseOffset + position) ;
   
}
void ofApp::drawEyebrows(ofVec2f position, int angle) {
    ofSetRectMode(OF_RECTMODE_CENTER);
    //eyebrows
    ofPushMatrix();
        ofTranslate(leftEyebrowOffset + position);
        ofRotateDeg(-angle);
        ofDrawRectangle(0, 0, eyebrowWidth, eyebrowHeight);
    ofPopMatrix();
    
    ofPushMatrix();
        ofTranslate(rightEyebrowOffset + position);
        ofRotateDeg(angle);
        ofDrawRectangle(0, 0, eyebrowWidth, eyebrowHeight);
    ofPopMatrix();
}

void ofApp::drawHappyParts(ofVec2f position, int intensity) {
    
    ofVec2f offset(0,ofMap(intensity, 0, 10, 4, -10));
    int mouthSize = ofMap(intensity, 0, 10, -5, 10);
    //int angle = ofMap(intensity, 0, 10, 10, 35);
    
    //eyebrows
    drawEyebrows(position + offset, 25);

    //mouth
    ofPath path;
    path.arc(position + happyMouthOffset, noseWidth/2, noseWidth/2 + mouthSize, 0, 180);
    path.setFilled(true);
    path.setFillColor(black);
    path.setStrokeWidth(5);
    path.draw();
}


void ofApp::drawSadParts(ofVec2f position, int intensity) {
    
    ofVec2f offset(0,ofMap(intensity, 0, 10, 0, 10));
    int mouthSize = ofMap(intensity, 0, 10, -5, 10);
    int angle = ofMap(intensity, 0, 10, 10, 45);
    
    //eyebrows
    drawEyebrows(position, angle);
    
    //mouth
    ofPath path;
    path.arc(position + sadMouthOffset + offset, noseWidth/2, noseWidth/2 + mouthSize, -180, 0);
    path.setFilled(true);
    path.setFillColor(black);
    path.setStrokeWidth(5);
    path.draw();
    
}
void ofApp::drawAngryParts(ofVec2f position, int intensity) {
    
    ofVec2f offset(0,ofMap(intensity, 0, 10, 0, 10));
    int mouthSize = ofMap(intensity, 0, 10, -5, 10);
    int angle = ofMap(intensity, 0, 10, -10, -45);
    
    //eyebrows
    drawEyebrows(position, angle);
    
    //mouth
    ofPath path;
    path.arc(position + sadMouthOffset + offset, noseWidth/2, noseWidth/2 + mouthSize, -180, 0);
    path.setFilled(true);
    path.setFillColor(black);
    path.setStrokeWidth(5);
    path.draw();
    
}
void ofApp::drawSurprisedParts(ofVec2f position, int intensity) {
    
    ofVec2f offset(0,ofMap(intensity, 0, 10, 5, -10));
    float mouthSize = ofMap(intensity, 0, 10, 0.5f, 1.2f);
    int angle = ofMap(intensity, 0, 10, -10, -45);
    
    //eyebrows
    drawEyebrows(position + offset, 0);
    
    //mouth
    ofPushMatrix();
        ofTranslate(position + surprisedMouthOffset);
        ofScale(1, mouthSize); //to change the mouth shape
        ofDrawCircle(0, 0, mouthWidth/2);
    ofPopMatrix();
    
}

void ofApp::drawTorso(ofVec2f position) {
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

void ofApp::drawLegs(ofVec2f position) {
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

void ofApp::drawStar(ofVec2f position, float r1, float r2, int vertices) {
    float alpha = 2 * PI / vertices;
    float i = PI/2;
    float revolution = 5 * PI/2;
    
    //outer star
    ofSetColor(yellow);
    ofPolyline star;
    while ( i < revolution ) {
        star.addVertex(ofPoint(position.x + cos(i) * r1,
                               position.y + sin(i) * r1));

        star.addVertex(ofPoint(position.x + cos(i + alpha/2) * r2,
                               position.y + sin(i + alpha/2) * r2));
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



