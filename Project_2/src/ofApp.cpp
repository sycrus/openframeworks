#include "ofApp.h"
#include "ofxCv.h"

using namespace ofxCv;
using namespace cv;

ofColor navy, salmon, rubberDuck, babyBlue; //palette 1

int minCircleArea = 27;     int maxCircleArea = 32;
int minTriangleArea = 13;   int maxTriangleArea = 19 ;
int minSquareArea = 20;     int maxSquareArea = 25;

bool isLeftFlipperActive = false; bool isRightFlipperActive = false; bool isPlungerActive = false;
bool isGui = false;

void ofApp::setup() {
    ofSetBackgroundColor(0,0,0); //sets background to black
    ofSetFrameRate(60);
    // set colors
    navy.setHex(0x21243d);
    salmon.setHex(0xff7c7c);
    rubberDuck.setHex(0xffd082);
    babyBlue.setHex(0x88e1f2);
    ////https://colorhunt.co/palette/170829
    interstateFont.load("Interstate.ttf", 30);
    score = 0;
    
    initializeImgs();
    initializeSvgs();
    initializeKinect();
    initializeCV();
  
    // Box2d
    box2d.init();
    box2d.enableEvents();
    box2d.setGravity(0, 30);
    box2d.setFPS(40.0);
    
    //pinball
    initializeFlippers();
    createBackground();
    
    //Arduino
    ard.connect("/dev/tty.usbmodem145101", 57600);
    ofAddListener(ard.EInitialized, this, &ofApp::setupArduino);
    bSetupArduino    = false;
    
    //Box2D: register the listener so that we get the events
    ofAddListener(box2d.contactStartEvents, this, &ofApp::contactStart);
    ofAddListener(box2d.contactEndEvents, this, &ofApp::contactEnd);
    
    //Sounds: load the 8 sfx soundfile
    for (int i=0; i<N_SOUNDS; i++) {
        sound[i].load("sfx/"+ofToString(i)+".mp3");
        sound[i].setMultiPlay(true);
        sound[i].setLoop(false);
    }

}

void ofApp::update() {
    
    //remove off-screen circles
    ofRemove(circles, [](shared_ptr<ofxBox2dCircle> circles) -> bool {
        return !ofRectangle(0, -400, ofGetWidth(), ofGetHeight()+ 400).inside(circles->getPosition());
    });
    
    if (!bSetupArduino) ofLog() << "Arduino not ready..." << endl;;
    updateArduino();
    updateKinect();
   
    box2d.update();
    if (isLeftFlipperActive) { leftFlipper.addRepulsionForce(leftFlipperPos.x , leftFlipperPos.y + 100 , 60.0); }
    if (isRightFlipperActive) { rightFlipper.addRepulsionForce(rightFlipperPos.x, rightFlipperPos.y + 100, 60.0); }
    if (isPlungerActive) {
        ofVec2f forcePos(plungerPos.x + 14,plungerPos.y - 60);
        ofVec2f forceVec(0, -15);
        plunger.addImpulseForce(forcePos, forceVec);
    } else {
        
    }
}
void ofApp::draw() {
    ofSetBackgroundColor(navy);
    
    backgroundImg.draw(0,0);
    leftSCImg.draw(leftSCPos.x, leftSCPos.y);
    rightSCImg.draw(rightSCPos.x-4, rightSCPos.y);
    
    if (showContours) { contourFinder.draw(); }
    if (showShapes) { drawContourAreas();};
    
    ofPushStyle();
        ofSetColor(babyBlue);
        interstateFont.drawString(ofToString(score), 50, ofGetHeight() - 50);
    ofPopStyle();
    
    drawFlippers();
    leftSImg.draw(leftSlingshotPos.x, leftSlingshotPos.y);
    rightSImg.draw(rightSlingshotPos.x-2, rightSlingshotPos.y);
    drawBumpers();
    
    //for detected objects
    for(auto & bEdge : backgroundEdges) {
        ofPushStyle();
            ofFill();
            ofSetColor(salmon);
            //bEdge->draw();
        ofPopStyle();
    }
    for(auto & edge : edges) {
        ofPushStyle();
            ofFill();
            ofSetColor(salmon);
            edge->draw();
        ofPopStyle();
    }
    
    for(auto & obstaclesWheel : obstaclesWheels) {
        ofPushMatrix();
            ofTranslate(obstaclesWheel->getPosition().x , obstaclesWheel->getPosition().y );
            ofRotateDeg(obstaclesWheel->getRotation());
            wheel1.setAnchorPercent(0.5, 0.5);
            ofSetColor(255);
            wheel1.draw(0,0);
        ofPopMatrix();
    }
    
    for(auto & bumperCircle : bumpersCircle) {
        ofFill();
        SoundData * data = (SoundData*)bumperCircle->getData();
        if(data && data->bHit) {
            bumperImg = face4;
            score += 40;
        }
        else {
            bumperImg = face3;
        }
        bumperImg.setAnchorPercent(0.5, 0.5);
        ofPushStyle();
            ofSetColor(255);
            bumperImg.draw(bumperCircle->getPosition().x,bumperCircle->getPosition().y);
        ofPopStyle();
    }
    for(auto & targetRect : targetsRect) {
        ofFill();
        SoundData * data = (SoundData*)targetRect->getData();
        if(data && data->bHit) {
            targetImg = target2;
            score += 50;
        }
        else {
            targetImg = target1;
        }
        ofPushStyle();
        ofPushMatrix();
            ofTranslate(targetRect->getPosition().x , targetRect->getPosition().y );
            ofRotateDeg(targetRect->getRotation());
            targetImg.setAnchorPercent(0.5, 0.5);
            ofSetColor(255);
            targetImg.draw(0,0);
        ofPopMatrix();
        ofPopStyle();
    }

    //for ball
    if (!circles.empty()) {
        for (auto & circle : circles) {
            if (circle->getPosition().y > ofGetHeight() ) {
                score = 0;
            }
            ofPushMatrix();
                ofTranslate(circle->getPosition().x , circle->getPosition().y );
                ofRotateDeg(circle->getRotation());
                ballImg.setAnchorPercent(0.5, 0.5);
                ofSetColor(255);
                ballImg.draw(0,0);
            ofPopMatrix();
        }
    }

    if (isGui) {
        gui.draw();
        stringstream reportStream;
            
        ofSetColor(ofColor::white);
        reportStream << "FPS: " << ofGetFrameRate() << endl;
         reportStream << "Threshold: " << threshold << endl;
         reportStream << "Angle: " << angle << endl;
         reportStream << "Min Area: " << minAreaRadius << endl;
         reportStream << "Max Area: " << maxAreaRadius << endl;
        ofDrawBitmapString(reportStream.str(), 20, 652);
    }
    
}

void ofApp::exit() {
}

void ofApp::mousePressed(int x, int y, int button) {
}

void ofApp::mouseDragged(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    if(key == 'f') { ofToggleFullscreen();}
    if(key == 'd') { showContours = !showContours; }
    
    if (key == ' ') { isPlungerActive = true; }
    if (key == OF_KEY_LEFT) { isLeftFlipperActive = true; }
    if (key == OF_KEY_RIGHT) { isRightFlipperActive = true; }

    // Kinect : Adjust Angle
    if (key == OF_KEY_UP) { angle++; if(angle>30) angle=30; kinect.setCameraTiltAngle(angle);}
    if (key == OF_KEY_DOWN) {angle--; if(angle<-30) angle=-30;kinect.setCameraTiltAngle(angle);}
    // Kinect : Change Threshold
    if (key == '=') { threshold++; if (threshold > 255) threshold = 255; cout<< "Threshold: " << threshold <<endl; }
    if (key == '-') { threshold--; if (threshold < 0) threshold = 0;  cout<< "Threshold: " << threshold <<endl; }
    // Kinect : Change min Blob Size
    if(key == '.') { minAreaRadius ++; contourFinder.setMinAreaRadius(minAreaRadius);}
    if(key == ',') { minAreaRadius --;contourFinder.setMinAreaRadius(minAreaRadius);}
    // Kinect : Change max Blob Size
    if(key == ';') { maxAreaRadius ++;contourFinder.setMaxAreaRadius(maxAreaRadius);}
    if(key == 'l') { maxAreaRadius --;contourFinder.setMaxAreaRadius(maxAreaRadius);}
    
    if(key == 'h') { isGui = !isGui; }
}

void ofApp::keyReleased(int key) {
    if(key == '0') {
        auto circle = std::make_shared<ofxBox2dCircle>();
        circle->setPhysics(1.0, 0.2, 0.1); //density bounce friction
        circle->setup(box2d.getWorld(), 686, ofGetHeight() - 100, 12);
        circles.push_back(circle);
    }
    if (key == ' ') { isPlungerActive = false; }
    if (key == OF_KEY_LEFT) { isLeftFlipperActive = false; }
    if (key == OF_KEY_RIGHT) { isRightFlipperActive = false; }

    if(key == 'n') {
        getMarkerLocations();
        for(auto & wheel : wheels) { createWheel(wheel);}
        for(auto & bumper : bumpers) { createBumper(bumper);}
        for(auto & target : targets) { createTarget(target.position, target.rotation);}
    }
    if(key == 'c') {
        outlines.clear();
        wheels.clear(); bumpers.clear(); targets.clear(); //clear location vectors
        edges.clear(); //clear edges
        circles.clear(); //clear balls
        bumpersCircle.clear();      targetsRect.clear(); //clear obstacles
        axes.clear();               axles.clear();          obstaclesWheels.clear(); //clear wheels
        
    }
    
}
void ofApp::initializeImgs() {
    backgroundImg.load("png/background.png");
    face1.load("png/face1.png");        face2.load("png/face2.png"); //ball faces
    face3.load("png/face3.png");        face4.load("png/face4.png"); //bumper faces
    leftSFace1.load("png/leftS1.png");  rightSFace1.load("png/rightS1.png"); //slingshot faces
    leftSCImg.load("png/leftSC.png");   rightSCImg.load("png/rightSC.png");
    target1.load("png/target1.png");    target2.load("png/target2.png");
    wheel1.load("png/wheel.png");
    leftSlingshotPos.set(160, 500, 0); rightSlingshotPos.set(527, 500, 0);
    leftSCPos.set(108, 458, 0); rightSCPos.set(548, 458, 0);
    ballImg = face1; bumperImg = face3; leftSImg = leftSFace1; rightSImg = rightSFace1;
    
    bumperImg.setAnchorPercent(0.5, 0.5);
    wheel1.setAnchorPercent(0.5, 0.5);
    targetImg.setAnchorPercent(0.5, 0.5);
}
void ofApp::initializeSvgs() {
    wheelSvg.load("svg/rube/wheel.svg");
    backgroundSvg.load("svg/pinball/background.svg");
    leftSCSvg.load("svg/pinball/leftSC.svg");
    rightSCSvg.load("svg/pinball/rightSC.svg");
    leftSSvg.load("svg/pinball/leftS.svg");
    rightSSvg.load("svg/pinball/rightS.svg");
}

void ofApp::initializeKinect() {
    kinect.setRegistration(true);
    kinect.init();
    kinect.init(true); // shows infrared instead of RGB video image
    kinect.open();        // opens first available kinect
    angle = -6;
    kinect.setCameraTiltAngle(angle);
}
void ofApp::initializeCV() {
    minAreaRadius = 20;
    maxAreaRadius = 40;
    threshold = 220;
    bThreshWithOpenCV = true;

    contourFinder.setMinAreaRadius(minAreaRadius);
    contourFinder.setMaxAreaRadius(maxAreaRadius);
    
    grayImage.allocate(kinect.width, kinect.height);
    grayThresh.allocate(kinect.width, kinect.height);
    grayImage.resize(ofGetWidth(), ofGetHeight());
    grayImage.scale(1.3, 1.1);
    grayThresh = grayImage;
    grayThresh.resize(ofGetWidth(), ofGetHeight());
    grayThresh.scale(1.3, 1.1);
}
void ofApp::updateKinect(){
    kinect.update();
    if(kinect.isFrameNew()) {
        grayImage.setFromPixels(kinect.getPixels());
        grayImage.resize(ofGetWidth(), ofGetHeight());
        grayImage.scale(1.3, 1.1);
        grayThresh = grayImage;
        
        grayThresh.resize(ofGetWidth(), ofGetHeight());
        grayThresh.scale(1.3, 1.1);
        grayThresh.blurGaussian(1.0f);
        grayThresh.threshold(threshold);
        
        grayImage.flagImageChanged();
        contourFinder.findContours(grayThresh);
    }
}

void ofApp::setupArduino(const int & version) {
    
    ofRemoveListener(ard.EInitialized, this, &ofApp::setupArduino);
    bSetupArduino = true;
    
    ofLogNotice() << ard.getFirmwareName();
    ofLogNotice() << "firmata v" << ard.getMajorFirmwareVersion() << "." << ard.getMinorFirmwareVersion();
    
    ard.sendDigitalPinMode(2, ARD_INPUT_PULLUP); //left
    ard.sendDigitalPinMode(3, ARD_INPUT_PULLUP); //right
    ard.sendDigitalPinMode(5, ARD_INPUT_PULLUP); //plunger
   
    ofAddListener(ard.EDigitalPinChanged, this, &ofApp::digitalPinChanged);
}
void ofApp::updateArduino(){
    
    ard.update();
    
//    if (bSetupArduino) { //only send to Arduino when ready
//        cout << ard.getDigital(2) << "," <<ard.getDigital(3) << "," <<ard.getDigital(5) << endl;
//    }

}
void ofApp::digitalPinChanged(const int & pinNum) {

    if (!ard.getDigital(2)) {
        isLeftFlipperActive = true;
    } else {
        isLeftFlipperActive = false;
    }
    if (!ard.getDigital(3)) {
        isRightFlipperActive = true;
    } else {
        isRightFlipperActive = false;
    }
    if (!ard.getDigital(5)) {
        isPlungerActive = true;
    } else {
         isPlungerActive = false;
    }
}

void ofApp::drawBumpers() {
    for(size_t i=0; i<bumpers.size(); i++) {
        ofFill();
        SoundData * data = (SoundData*)bumpersCircle[i].get()->getData();
        if(data && data->bHit) {
            bumperImg = face4;
        }
        else {
            bumperImg = face3;
        }
        bumperImg.setAnchorPercent(0.5, 0.5);
        ofPushStyle();
            ofSetColor(255);
            bumperImg.draw(bumpersCircle[i]->getPosition().x,bumpersCircle[i]->getPosition().y);
        ofPopStyle();
    }
}
void ofApp::drawFlippers() {
    ofPushStyle();
        ofFill();
        ofSetColor(babyBlue);
        leftFlipper.draw(); rightFlipper.draw();
        leftAnchor.draw(); rightAnchor.draw();
        leftFlipperJoint.draw(); rightFlipperJoint.draw();
        plunger.draw();
    ofPopStyle();
}
void ofApp::drawContourAreas() {
    for (int i=0; i < contourFinder.size(); i++) {
        ofPolyline contourPolyline = contourFinder.getPolyline(i);
        contourPolyline.simplify(2.0f);
        blobArea[i] = abs(contourPolyline.getArea());
        int roundedBlobArea = blobArea[i]/100;
        if (showContours) {
            ofDrawBitmapString(100 * roundedBlobArea, contourPolyline.getCentroid2D().x, contourPolyline.getCentroid2D().y);
        }
        if (roundedBlobArea > minCircleArea && roundedBlobArea < maxCircleArea) {//bumper
            ofPoint centroid;
            centroid.set(contourPolyline.getCentroid2D().x, contourPolyline.getCentroid2D().y);
            ofPushStyle();
                ofSetColor(255,255,255,155);
                bumperImg.draw(centroid.x, centroid.y);
            ofPopStyle();
        }
        if (roundedBlobArea > minSquareArea && roundedBlobArea < maxSquareArea) { //target
            ofPoint centroid;
            centroid.set(contourPolyline.getCentroid2D().x, contourPolyline.getCentroid2D().y);
            auto rotatedRect = contourFinder.getMinAreaRect(i);
            targetImg = target1;
            ofPushMatrix();
                ofTranslate(centroid.x, centroid.y);
                ofRotateDeg(rotatedRect.angle);
                ofPushStyle();
                    ofSetColor(255,255,255,155);
                    targetImg.draw(0,0);
                ofPopStyle();
            ofPopMatrix();
        }
        if (roundedBlobArea > minTriangleArea && roundedBlobArea < maxTriangleArea) { //wheel
            ofPoint centroid;
            centroid.set(contourPolyline.getCentroid2D().x, contourPolyline.getCentroid2D().y);
            ofPushStyle();
                ofSetColor(255,255,255,155);
                wheel1.draw(centroid.x, centroid.y);
            ofPopStyle();
        }
    }
}

void ofApp::getMarkerLocations() {
    for (int i=0; i < contourFinder.size(); i++) {
        ofPolyline contourPolyline = contourFinder.getPolyline(i);
        blobArea[i] = abs(contourPolyline.getArea());
        int roundedBlobArea = blobArea[i]/100;
        if (roundedBlobArea > minCircleArea && roundedBlobArea < maxCircleArea) {//bumper
            ofPoint centroid;
            centroid.set(contourPolyline.getCentroid2D().x, contourPolyline.getCentroid2D().y);
            bumpers.push_back(centroid);
        }
        if (roundedBlobArea > minSquareArea && roundedBlobArea < maxSquareArea) { //target
            ofPoint centroid;
            centroid.set(contourPolyline.getCentroid2D().x, contourPolyline.getCentroid2D().y);
            auto rotatedRect = contourFinder.getMinAreaRect(i);
            Target tgt; tgt.position = centroid; tgt.rotation = rotatedRect.angle;
            targets.push_back(tgt);
        }
        if (roundedBlobArea > minTriangleArea && roundedBlobArea < maxTriangleArea) { //wheel
            ofPoint centroid;
            centroid.set(contourPolyline.getCentroid2D().x, contourPolyline.getCentroid2D().y);
            wheels.push_back(centroid);
        }
    }
}

void ofApp::createBackground() { //only once on setup
    //frame
    for (ofPath p: backgroundSvg.getPaths()){
        auto bEdge = make_shared<ofxBox2dEdge>();
        p.setPolyWindingMode(OF_POLY_WINDING_ODD);
        const vector<ofPolyline>& lines = p.getOutline();
        for(const ofPolyline & line: lines){
            outlines.push_back(line); //vector of polylines
        }
        for (ofPolyline outline: outlines) {
            outline.close();
            bEdge->addVertexes(outline);
        }
        bEdge->create(box2d.getWorld());
        backgroundEdges.push_back(bEdge);
    }
    //left side channel
    for (ofPath p: leftSCSvg.getPaths()){
        auto bEdge = make_shared<ofxBox2dEdge>();
        p.setPolyWindingMode(OF_POLY_WINDING_ODD);
        const vector<ofPolyline>& lines = p.getOutline();
        for(const ofPolyline & line: lines){
            outlinesLeftSC.push_back(line); //vector of polylines
        }
        for (ofPolyline outline: outlinesLeftSC) {
            ofVec3f position(leftSCPos);
            outline.translate(position);
            outline.close();
            bEdge->addVertexes(outline);
        }
        bEdge->create(box2d.getWorld());
        backgroundEdges.push_back(bEdge);
    }
    
    //right side channel
    for (ofPath p: rightSCSvg.getPaths()){
        auto bEdge = make_shared<ofxBox2dEdge>();
        p.setPolyWindingMode(OF_POLY_WINDING_ODD);
        const vector<ofPolyline>& lines = p.getOutline();
        for(const ofPolyline & line: lines){
            outlinesRightSC.push_back(line); //vector of polylines
        }
        for (ofPolyline outline: outlinesRightSC) {
            ofVec3f position(rightSCPos);
            outline.translate(position);
            outline.close();
            bEdge->addVertexes(outline);
        }
        bEdge->create(box2d.getWorld());
        backgroundEdges.push_back(bEdge);
    }
    
    //left slingshot
    for (ofPath p: leftSSvg.getPaths()){
        auto bEdge = make_shared<ofxBox2dEdge>();
        p.setPolyWindingMode(OF_POLY_WINDING_ODD);
        const vector<ofPolyline>& lines = p.getOutline();
        for(const ofPolyline & line: lines){
            outlinesLeftSlingshot.push_back(line); //vector of polylines
        }
        for (ofPolyline outline: outlinesLeftSlingshot) {
            ofVec3f position(leftSlingshotPos);
            outline.translate(position);
            bEdge->addVertexes(outline);
            bEdge->setPhysics(0.0, 2.8, 0.5);
        }
        bEdge->create(box2d.getWorld());
        backgroundEdges.push_back(bEdge);
    }
    for (ofPath p: rightSSvg.getPaths()){
        auto bEdge = make_shared<ofxBox2dEdge>();
        p.setPolyWindingMode(OF_POLY_WINDING_ODD);
        const vector<ofPolyline>& lines = p.getOutline();
        for(const ofPolyline & line: lines){
            outlinesRightSlingshot.push_back(line); //vector of polylines
        }
        for (ofPolyline outline: outlinesRightSlingshot) {
            ofVec3f position(rightSlingshotPos);
            outline.translate(position);
            bEdge->addVertexes(outline);
            bEdge->setPhysics(0.0, 2.8, 0.5);
        }
        bEdge->create(box2d.getWorld());
        backgroundEdges.push_back(bEdge);
    }
}
void ofApp::createEdgesContourFinder() {
    for (int i=0; i < contourFinder.size(); i++) {
        auto edge = make_shared<ofxBox2dEdge>();
        ofPolyline contourPolyline = contourFinder.getPolyline(i);
        
        for (int j = 0; j < contourPolyline.getVertices().size() ; j++) {
            auto pts = contourPolyline.getVertices();
            edge->addVertex(pts[j]);
        }
        edge->create(box2d.getWorld());
        edges.push_back(edge);
    }
}
void ofApp::initializeFlippers() {
    leftFlipperPos.set(ofGetWidth()/2 - 80, ofGetHeight() - 150);
    leftFlipper.setPhysics(1.0, 0.5, 0.5);
    leftFlipper.setup(box2d.getWorld(), leftFlipperPos.x, leftFlipperPos.y, 150, 20);
    
    leftAnchorPos.set(leftFlipperPos.x - 75, leftFlipperPos.y);
    leftAnchor.setup(box2d.getWorld(), leftAnchorPos, 10);

    leftFlipperJoint.setWorld(box2d.getWorld());
    leftFlipperJoint.setup(leftAnchor.body, leftFlipper.body, 0, 0);
    leftFlipperJoint.setLimits(-ofDegToRad(35), ofDegToRad(35));
    
    rightFlipperPos.set(ofGetWidth()/2 + 80 , ofGetHeight() - 150);
    rightFlipper.setPhysics(1.0, 0.5, 0.5);
    rightFlipper.setup(box2d.getWorld(), rightFlipperPos.x, rightFlipperPos.y, 150, 20);
    
    rightAnchorPos.set(rightFlipperPos.x + 75, rightFlipperPos.y);
    rightAnchor.setup(box2d.getWorld(), rightAnchorPos, 10);
    
    rightFlipperJoint.setWorld(box2d.getWorld());
    rightFlipperJoint.setup(rightAnchor.body, rightFlipper.body, 0, 0);
    rightFlipperJoint.setLimits(-ofDegToRad(35), ofDegToRad(35));
    
    plungerPos.set(671, ofGetHeight() - 60);
    plunger.setPhysics(0.5, 0.5, 0.5);
    plunger.setup(box2d.getWorld(), plungerPos.x, plungerPos.y, 39, 50);
    
    auto startPin = make_shared<ofxBox2dCircle>();
    startPin->setup(box2d.getWorld(), plungerPos.x + 34, plungerPos.y - 100, 2);
    ssPins.push_back(startPin);
    
    auto startPin2 = make_shared<ofxBox2dCircle>();
    startPin2->setup(box2d.getWorld(), plungerPos.x + 17, plungerPos.y + 80, 2);
    ssPins.push_back(startPin2);
}
void ofApp::createTarget(ofPoint position, int rotation) {
    auto r = std::make_shared<ofxBox2dRect>();
    r->setPhysics(0.0, 1., 0.9);
    r->setup(box2d.getWorld(), position.x, position.y, 100, 30);
    r->setRotation(rotation);
    r->setData(new SoundData());
    auto * sd = (SoundData*)r->getData();
    sd->soundID = ofRandom(0, N_SOUNDS); //set sound here
    sd->bHit    = false;
    targetsRect.push_back(r);
}
void ofApp::createBumper(ofPoint position) {
    auto c = std::make_shared<ofxBox2dCircle>();
    c->setPhysics(0.0, 0.8, 0.9);
    c->setup(box2d.getWorld(), position.x, position.y, 40);
    c->setData(new SoundData());
    auto * sd = (SoundData*)c->getData();
    sd->soundID = ofRandom(0, N_SOUNDS); //set sound here
    sd->bHit    = false;
    bumpersCircle.push_back(c);
}
void ofApp::createWheel(ofPoint position) { //update
    polylineToWheels(svgToPolyline(wheelSvg), position);
    
    auto axle = make_shared<ofxBox2dCircle>();
    axle->setup(box2d.getWorld(), position.x, position.y, 13);
    axles.push_back(axle);
    
    auto axis = make_shared<ofxBox2dRevoluteJoint>();
    axis->setup(axles.back()->body, obstaclesWheels.back()->body, 0, 0);
    axes.push_back(axis);
}

void ofApp::polylineToWheels(ofPolyline polyline, ofPoint position) {
    auto center = polyline.getCentroid2D();
    auto poly = std::make_shared<ofxBox2dPolygon>();
    poly->addVertices(polyline.getVertices());
    poly->triangulate();
    poly->setPhysics(1., 0.2, 0.4);
    poly->create(box2d.getWorld(), position.x - center.x, position.y - center.y);
//    poly->setData(new SoundData());
//    auto * sd = (SoundData*)poly->getData();
//    sd->soundID = ofRandom(0, N_SOUNDS); //set sound here
//    sd->bHit    = false;
    obstaclesWheels.push_back(poly);
}
ofPolyline ofApp::svgToPolyline(ofxSVG svg) {
    ofPolyline  contour;
    ofPath p = svg.getPathAt(0);
    p.setPolyWindingMode(OF_POLY_WINDING_ODD);
    contour.addVertices(p.getOutline().at(0).getVertices());
    contour.addVertex(p.getOutline().at(0).getVertices().at(0));
    contour.close();
    return contour;
}

void ofApp::contactStart(ofxBox2dContactArgs &e) {
    if(e.a != NULL && e.b != NULL) {
        ballImg = face2;
        if(e.a->GetType() == b2Shape::e_circle && e.b->GetType() == b2Shape::e_circle) {
            
            SoundData * aData = (SoundData*)e.a->GetBody()->GetUserData();
            SoundData * bData = (SoundData*)e.b->GetBody()->GetUserData();
            
            if(aData) {
                aData->bHit = true;
                sound[aData->soundID].play();
            }
            
            if(bData) {
                bData->bHit = true;
                sound[bData->soundID].play();
            }
        } else if (e.a->GetType() == b2Shape::e_polygon && e.b->GetType() == b2Shape::e_circle) {
            SoundData * aData = (SoundData*)e.a->GetBody()->GetUserData();
            SoundData * bData = (SoundData*)e.b->GetBody()->GetUserData();
            
            if(aData) {
                aData->bHit = true;
                sound[aData->soundID].play();
            }
            
            if(bData) {
                bData->bHit = true;
                sound[bData->soundID].play();
            }
        }
        else if (e.a->GetType() == b2Shape::e_edge && e.b->GetType() == b2Shape::e_circle) {
            SoundData * aData = (SoundData*)e.a->GetBody()->GetUserData();
            SoundData * bData = (SoundData*)e.b->GetBody()->GetUserData();
            
            if(aData) {
                aData->bHit = true;
                sound[aData->soundID].play();
            }
            
            if(bData) {
                bData->bHit = true;
                sound[bData->soundID].play();
            }
        }
    }
}
void ofApp::contactEnd(ofxBox2dContactArgs &e) {
    if(e.a != NULL && e.b != NULL) {
        ballImg = face1;
        SoundData * aData = (SoundData*)e.a->GetBody()->GetUserData();
        SoundData * bData = (SoundData*)e.b->GetBody()->GetUserData();
        
        if(aData) {
            aData->bHit = false;
        }
        
        if(bData) {
            bData->bHit = false;
        }
    }
}
