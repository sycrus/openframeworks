#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetLogLevel(OF_LOG_NOTICE);
    ofSetLineWidth(8);
    ofDisableArbTex();
    ofDisableDepthTest();
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofBackground(ofColor::black);
    ofSetFrameRate(60);
    
    testImage.load("testcard.png");
    initializeSvgs();
    initializePngs();
    initializeWarps();
    initializeAnchors();
    initializeFbos();
    initializeAnimationPolylines();

    scene = 1;
    sequence = 1;
    
    startTime = ofGetFrameNum();
    
}

//--------------------------------------------------------------
void ofApp::exit()
{
    this->warpController.saveSettings("settings.json");
}

//--------------------------------------------------------------
void ofApp::update()
{
    if (scene == 1) { //===========   ===   =================
        if (sequence == 1) {
            endTime = 2 * 60; //3 sec
            float timer = ofGetFrameNum() - startTime;
            pct = ofMap(timer, 0, endTime, 0.0, 1.0, true);
            if (pct < 1.0) {
                isFlapping = true;
                birdPos = sPoly1[0].getPointAtPercent(pct);
                fade = ofMap( pct, 0.0, 1.0, 0, 255, true);
                angleToRotate = 1.67989;
            } else {
                sequence++;
                pct = 0.0;
                startTime = ofGetFrameNum();
            }
        }
        if (sequence == 2) {
            endTime = 1 * 60; //1 sec
            float timer = ofGetFrameNum() - startTime;
            pct = ofMap(timer, 0, endTime, 0.0, 1.0, true);
            if (pct < 1.0) { //adjust for delay
                isFlapping = false;
            } else {
                sequence++;
                pct = 0.;
                startTime = ofGetFrameNum();
            }
        }
        if (sequence == 3) {
            endTime = 2 * 60; //1 sec
            float timer = ofGetFrameNum() - startTime;
            pct = ofMap(timer, 0, endTime, 0.0, 1.0, true);
            if (pct < 1) {
                isFlapping = true;
                birdPos = sPoly1[1].getPointAtPercent(pct);
                fade = ofMap( pct, 0.0, 1.0, 0, 255, true);
                angleToRotate = ofDegToRad(30);
            } else {
                sequence++;
                pct = 0.;
                startTime = ofGetFrameNum();
            }
        }
        if (sequence == 4) {
            endTime = 1 * 60; //1 sec
            float timer = ofGetFrameNum() - startTime;
            pct = ofMap(timer, 0, endTime, 0.0, 1.0, true);
            if (pct < 1.0) { //adjust for delay
                isFlapping = false;
            } else {
                sequence++;
                pct = 0;
                startTime = ofGetFrameNum();
            }
        }
        if (sequence == 5) {
            endTime = 1 * 60; //1 sec
            float timer = ofGetFrameNum() - startTime;
            pct = ofMap(timer, 0, endTime, 0.0, 1.0, true);
            if (pct < 1) {
                isFlapping = true;
                birdPos = sPoly1[2].getPointAtPercent(pct);
                angleToRotate = ofDegToRad(120);
            } else {
                sequence++;
                pct = 0;
                startTime = ofGetFrameNum();
            }
        }
        if (sequence == 6) {
            endTime = 1 * 60; //1 sec
            float timer = ofGetFrameNum() - startTime;
            pct = ofMap(timer, 0, endTime, 0.0, 1.0, true);
            if (pct < 1.0) { //adjust for delay
                isFlapping = false;
                
            } else {
                scene++;
                sequence = 1;
                pct = 0;
                startTime = ofGetFrameNum();
            }
        }
    }
    if (scene == 2) {//===========   ===   ===   =================
        
        if (sequence == 1) {
            endTime = 0.5 * 60; //1 sec
            float timer = ofGetFrameNum() - startTime;
            pct = ofMap(timer, 0, endTime, 0.0, 1.0, true);
            if (pct < 1) {
                isFlapping = true;
                birdPos = sPoly2b[0].getPointAtPercent(pct);
                angleToRotate = ofDegToRad(210);
            } else {
                sequence++;
                pct = 0;
                startTime = ofGetFrameNum();
            }
        }
        if (sequence == 2) {
            endTime = 1 * 60; //1 sec
            float timer = ofGetFrameNum() - startTime;
            pct = ofMap(timer, 0, endTime, 0.0, 1.0, true);
            if (pct < 1) {
                isFlapping = true;
                birdPos = sPoly2b[1].getPointAtPercent(pct);
            } else {
                sequence++;
                pct = 0;
                startTime = ofGetFrameNum();
            }
        }
        if (sequence == 3) {
            endTime = 1 * 60; //1 sec
            float timer = ofGetFrameNum() - startTime;
             pct = ofMap(timer, 0, endTime, 0.0, 1.0, true);
            if (pct < 1.0) { //adjust for delay
                isFlapping = false;
            } else {
                sequence++;
                pct = 0;
                startTime = ofGetFrameNum();
            }
        }
        if (sequence == 4) {
            endTime = 1 * 60; //1 sec
            float timer = ofGetFrameNum() - startTime;
             pct = ofMap(timer, 0, endTime, 0.0, 1.0, true);
            if (pct < 1) {
                isFlapping = true;
                birdPos = sPoly2b[2].getPointAtPercent(pct);
            } else {
                sequence++;
                pct = 0;
                startTime = ofGetFrameNum();
            }
        }
        if (sequence == 5) {
            endTime = 1 * 60; //1 sec
            float timer = ofGetFrameNum() - startTime;
             pct = ofMap(timer, 0, endTime, 0.0, 1.0, true);
            if (pct < 1.0) { //adjust for delay
                isFlapping = false;
            } else {
                sequence++;
                pct = 0;
                startTime = ofGetFrameNum();
            }
        }
        if (sequence == 6) {
            endTime = 1 * 60; //1 sec
            float timer = ofGetFrameNum() - startTime;
             pct = ofMap(timer, 0, endTime, 0.0, 1.0, true);
            if (pct < 1) {
                isFlapping = true;
                birdPos = sPoly2b[3].getPointAtPercent(pct);
            } else {
                sequence++;
                pct = 0;
                startTime = ofGetFrameNum();
            }
        }
        if (sequence == 7) {
            endTime = 1 * 60; //1 sec
            float timer = ofGetFrameNum() - startTime;
            pct = ofMap(timer, 0, endTime, 0.0, 1.0, true);
            if (pct < 1) {
                isFlapping = false;
            } else {
                sequence++;
                pct = 0;
                startTime = ofGetFrameNum();
            }
        }
        if (sequence == 8) {
            endTime = 3 * 60; //1 sec
            float timer = ofGetFrameNum() - startTime;
             pct = ofMap(timer, 0, endTime, 0.0, 1.0, true);
            if (pct < 1) {
                isFlapping = false;
                manPos = sPoly2c[0].getPointAtPercent(pct);
                ofSetColor(ofColor::white);
                ofDrawCircle(manPos.x, manPos.y, 20);
            } else {
                scene++;
                sequence = 1;
                pct = 0;
                startTime = ofGetFrameNum();
            }
        }
    }
    if (scene == 3) { //===========   ===   ===  ===  =================
        
        if (sequence == 1) {
            endTime = 1 * 60; //1 sec
            float timer = ofGetFrameNum() - startTime;
             pct = ofMap(timer, 0, endTime, 0.0, 1.0, true);
            if (pct < 1) {
                isFlapping = false;
                manPos = sPoly3c[0].getPointAtPercent(pct);
            } else {
                sequence++;
                pct = 0;
                startTime = ofGetFrameNum();
            }
        }
        if (sequence == 2) {
            endTime = 1 * 60; //1 sec
            float timer = ofGetFrameNum() - startTime;
             pct = ofMap(timer, 0, endTime, 0.0, 1.0, true);
            if (pct < 1) {
                isFlapping = true;
                birdPos = sPoly3b[0].getPointAtPercent(pct);
            } else {
                sequence++;
                pct = 0;
                startTime = ofGetFrameNum();
            }
        }
        if (sequence == 3) {
            endTime = 1 * 60; //1 sec
            float timer = ofGetFrameNum() - startTime;
             pct = ofMap(timer, 0, endTime, 0.0, 1.0, true);
            if (pct < 1) {
                isFlapping = false;
                manPos = sPoly3c[1].getPointAtPercent(pct);
            } else {
                sequence++;
                pct = 0;
                startTime = ofGetFrameNum();
            }
        }
        if (sequence == 4) {
            endTime = 1 * 60; //1 sec
            float timer = ofGetFrameNum() - startTime;
             pct = ofMap(timer, 0, endTime, 0.0, 1.0, true);
            if (pct < 1) {
                isFlapping = true;
                birdPos = sPoly3b[1].getPointAtPercent(pct);
            } else {
                sequence++;
                pct = 0;
                startTime = ofGetFrameNum();
            }
        }
        if (sequence == 5) {
            endTime = 1 * 60; //1 sec
            float timer = ofGetFrameNum() - startTime;
             pct = ofMap(timer, 0, endTime, 0.0, 1.0, true);
            if (pct < 1) {
                isFlapping = false;
                //pick up cup
            } else {
                sequence++;
                pct = 0;
                startTime = ofGetFrameNum();
            }
        }
        if (sequence == 6) {
            endTime = 1 * 60; //1 sec
            float timer = ofGetFrameNum() - startTime;
             pct = ofMap(timer, 0, endTime, 0.0, 1.0, true);
            if (pct < 1.0) { //adjust for delay
                isFlapping = false;
            } else {
                scene++;
                sequence = 1;
                pct = 0;
                startTime = ofGetFrameNum();
            }
        }
    }
    if (scene == 4) { //===========   ===   ===  ===  ===  =================
        
        if (sequence == 1) {
            endTime = 1 * 60; //1 sec
            float timer = ofGetFrameNum() - startTime;
             pct = ofMap(timer, 0, endTime, 0.0, 1.0, true);
            if (pct < 1) {
                isFlapping = false;
                manPos = sPoly4c[0].getPointAtPercent(pct);
            } else {
                sequence++;
                pct = 0;
                startTime = ofGetFrameNum();
            }
        }
        if (sequence == 2) {
            endTime = 1 * 60; //1 sec
            float timer = ofGetFrameNum() - startTime;
             pct = ofMap(timer, 0, endTime, 0.0, 1.0, true);
            if (pct < 1) {
                isFlapping = true;
                birdPos = sPoly4b[0].getPointAtPercent(pct);
            } else {
                sequence++;
                pct = 0;
                startTime = ofGetFrameNum();
            }
        }
        if (sequence == 3) {
            endTime = 1 * 60; //1 sec
            float timer = ofGetFrameNum() - startTime;
             pct = ofMap(timer, 0, endTime, 0.0, 1.0, true);
            if (pct < 1) {
                isFlapping = false;
                manPos = sPoly4c[1].getPointAtPercent(pct);
            } else {
                sequence++;
                pct = 0;
                startTime = ofGetFrameNum();
            }
        }
        if (sequence == 4) {
            endTime = 1 * 60; //1 sec
            float timer = ofGetFrameNum() - startTime;
             pct = ofMap(timer, 0, endTime, 0.0, 1.0, true);
            if (pct < 1) {
                isFlapping = true;
                birdPos = sPoly4b[1].getPointAtPercent(pct);
            } else {
                sequence++;
                pct = 0;
                startTime = ofGetFrameNum();
            }
        }
        if (sequence == 5) {
            endTime = 1 * 60; //1 sec
            float timer = ofGetFrameNum() - startTime;
             pct = ofMap(timer, 0, endTime, 0.0, 1.0, true);
            if (pct < 1) {
                isFlapping = false;
                manPos = sPoly4c[2].getPointAtPercent(pct);
            } else {
                sequence++;
                pct = 0;
                startTime = ofGetFrameNum();
            }
        }
        if (sequence == 6) {
            endTime = 1 * 60; //1 sec
            float timer = ofGetFrameNum() - startTime;
             pct = ofMap(timer, 0, endTime, 0.0, 1.0, true);
            if (pct < 1) {
                isFlapping = false;
            } else {
               scene++;
               sequence = 1;
               pct = 0;
               startTime = ofGetFrameNum();
            }
        }
    }
    if (scene == 5) { //===========   ===   ===  ===  ===  ===   =================
        
        if (sequence == 1) {
            endTime = 1 * 60; //1 sec
            float timer = ofGetFrameNum() - startTime;
             pct = ofMap(timer, 0, endTime, 0.0, 1.0, true);
            if (pct < 1) {
                isFlapping = false;
                manPos = sPoly5c[0].getPointAtPercent(pct);
            } else {
                sequence++;
                pct = 0;
                startTime = ofGetFrameNum();
            }
        }
        if (sequence == 2) {
            endTime = 1 * 60; //1 sec
            float timer = ofGetFrameNum() - startTime;
             pct = ofMap(timer, 0, endTime, 0.0, 1.0, true);
            if (pct < 1) {
                isFlapping = true;
                birdPos = sPoly5b[0].getPointAtPercent(pct);
                manPos = sPoly5c[1].getPointAtPercent(pct);
            } else {
                sequence++;
                pct = 0;
                startTime = ofGetFrameNum();
            }
        }
        if (sequence == 3) {
            endTime = 1 * 60; //1 sec
            float timer = ofGetFrameNum() - startTime;
             pct = ofMap(timer, 0, endTime, 0.0, 1.0, true);
            if (pct < 1) {
                isFlapping = true;
                birdPos = sPoly5b[1].getPointAtPercent(pct);
                manPos = sPoly5c[2].getPointAtPercent(pct);
            } else {
                sequence++;
                pct = 0;
                startTime = ofGetFrameNum();
            }
        }
        if (sequence == 4) {
            endTime = 1 * 60; //1 sec
            float timer = ofGetFrameNum() - startTime;
             pct = ofMap(timer, 0, endTime, 0.0, 1.0, true);
            if (pct < 1) {
                isFlapping = false;
                manPos = sPoly5c[3].getPointAtPercent(pct);
            } else {
                sequence++;
                pct = 0;
                startTime = ofGetFrameNum();
            }
        }
        if (sequence == 5) {
            endTime = 1 * 60; //1 sec
            float timer = ofGetFrameNum() - startTime;
             pct = ofMap(timer, 0, endTime, 0.0, 1.0, true);
            if (pct < 1) {
                isFlapping = true;
                birdPos = sPoly5b[2].getPointAtPercent(pct);
            } else {
                sequence++;
                pct = 0;
                startTime = ofGetFrameNum();
            }
        }
        if (sequence == 6) {
            endTime = 1 * 60; //1 sec
            float timer = ofGetFrameNum() - startTime;
             pct = ofMap(timer, 0, endTime, 0.0, 1.0, true);
            if (pct < 1) {
                isFlapping = false;
            } else {
                sequence++;
                pct = 0;
                startTime = ofGetFrameNum();
            }
        }
        if (sequence == 7) {
            endTime = 1 * 60; //1 sec
            float timer = ofGetFrameNum() - startTime;
             pct = ofMap(timer, 0, endTime, 0.0, 1.0, true);
            if (pct < 1.0) { //adjust for delay
                isFlapping = false;
            } else {
                scene++;
                sequence = 1;
                pct = 0;
                startTime = ofGetFrameNum();
            }
        }
    }
    if (scene == 6) { //===========   ===   ===  ===  ===  ===   ===   =================
        
        if (sequence == 1) {
            endTime = 1 * 60; //1 sec
            float timer = ofGetFrameNum() - startTime;
             pct = ofMap(timer, 0, endTime, 0.0, 1.0, true);
            if (pct < 1) {
                isFlapping = true;
                birdPos = sPoly6b[0].getPointAtPercent(pct);
                manPos = sPoly6c[0].getPointAtPercent(pct);
            } else {
                sequence++;
                pct = 0;
                startTime = ofGetFrameNum();
            }
        }
        if (sequence == 2) {
            endTime = 1 * 60; //1 sec
            float timer = ofGetFrameNum() - startTime;
             pct = ofMap(timer, 0, endTime, 0.0, 1.0, true);
            if (pct < 1) {
                isFlapping = true;
                birdPos = sPoly6b[1].getPointAtPercent(pct);
                manPos = sPoly6c[1].getPointAtPercent(pct);
            } else {
                sequence++;
                pct = 0;
                startTime = ofGetFrameNum();
            }
        }
        if (sequence == 3) {
            endTime = 1 * 60; //1 sec
            float timer = ofGetFrameNum() - startTime;
             pct = ofMap(timer, 0, endTime, 0.0, 1.0, true);
            if (pct < 1) {
                isFlapping = true;
                manPos = sPoly6c[2].getPointAtPercent(pct);
            } else {
                sequence++;
                pct = 0;
                startTime = ofGetFrameNum();
            }
        }
        if (sequence == 4) {
            endTime = 1 * 60; //1 sec
            float timer = ofGetFrameNum() - startTime;
             pct = ofMap(timer, 0, endTime, 0.0, 1.0, true);
            if (pct < 1) {
                isFlapping = true;
                birdPos = sPoly6b[2].getPointAtPercent(pct);
            } else {
                sequence++;
                pct = 0;
                startTime = ofGetFrameNum();
            }
        }
        if (sequence == 5) {
            endTime = 1 * 60; //1 sec
            float timer = ofGetFrameNum() - startTime;
             pct = ofMap(timer, 0, endTime, 0.0, 1.0, true);
            if (pct < 1) {
                isFlapping = true;
                manPos = sPoly6c[3].getPointAtPercent(pct);
            } else {
                sequence++;
                pct = 0;
                startTime = ofGetFrameNum();
            }
        }
        if (sequence == 6) {
            endTime = 1 * 60; //1 sec
            float timer = ofGetFrameNum() - startTime;
             pct = ofMap(timer, 0, endTime, 0.0, 1.0, true);
            if (pct < 1) {
                isFlapping = true;
                birdPos = sPoly6b[3].getPointAtPercent(pct);
            } else {
                sequence++;
                pct = 0;
                startTime = ofGetFrameNum();
            }
        }
        if (sequence == 7) {
            endTime = 1 * 60; //1 sec
            float timer = ofGetFrameNum() - startTime;
             pct = ofMap(timer, 0, endTime, 0.0, 1.0, true);
            if (pct < 1) {
                isFlapping = false;
                manPos = sPoly6c[4].getPointAtPercent(pct);
            } else {
                sequence++;
                pct = 0;
                startTime = ofGetFrameNum();
            }
        }
        if (sequence == 8) {
            endTime = 1 * 60; //1 sec
            float timer = ofGetFrameNum() - startTime;
             pct = ofMap(timer, 0, endTime, 0.0, 1.0, true);
            if (pct < 1.0) { //adjust for delay
                isFlapping = false;
            } else {
                sequence++;
                pct = 0;
                startTime = ofGetFrameNum();
            }
        }
        if (sequence == 9) {
            endTime = 1 * 60; //1 sec
            float timer = ofGetFrameNum() - startTime;
             pct = ofMap(timer, 0, endTime, 0.0, 1.0, true);
            if (pct < 1.0) { //adjust for delay
                isFlapping = false;
                 fade = pct * 255;
            } else {
                //sequence++;
                //startTime = ofGetFrameNum();
            }
        }
    }
    
    updateTopFbo();
    updateFrontFbo();
    updateSideFbo();
    
    ofSetWindowTitle(ofToString(ofGetFrameRate(), 2) + " FPS :: " + areaName + " :: " + (this->useBeginEnd ? "begin()/end()" : "draw()") + " " + ofToString(ofRadToDeg(angleToRotate)));
}

//--------------------------------------------------------------
void ofApp::draw()
{
    //for unprojected areas
    ofBackground(ofColor::black);

    if (this->texture.isAllocated())
    {
        for (auto i = 0; i < this->warpController.getNumWarps(); ++i)
        {
            auto warp = this->warpController.getWarp(i);
            
            //SIDE
            if ( i == 0) {
                fboSide.readToPixels(pixelSide);
                imgSide.setFromPixels(pixelSide);
                imgSide.update();
                this->texture.loadData(imgSide.getPixels());
            }
            //TOP
            if ( i == 1) {
                fboTop.readToPixels(pixelTop);
                imgTop.setFromPixels(pixelTop);
                imgTop.update();
                this->texture.loadData(imgTop.getPixels());
            }
            //FRONT
            if ( i == 2) {
                fboFront.readToPixels(pixelFront); //takes fbo frame and stores into pixels
                imgFront.setFromPixels(pixelFront); //takes pixels and stores into img
                imgFront.update();              //update the image
                this->texture.loadData(imgFront.getPixels());
            }
            if (this->useBeginEnd)
            {
                warp->begin();
                {
                    auto bounds = warp->getBounds();
                    this->texture.drawSubsection(bounds.x, bounds.y, bounds.width, bounds.height, this->srcAreas[i].x, this->srcAreas[i].y, this->srcAreas[i].width, this->srcAreas[i].height);
                }
                warp->end();
            }
            else
            {
                warp->draw(this->texture, this->srcAreas[i]);
            }
        }
    }
    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    if (key == ' ') {
        scene = 1;
        sequence = 1;
    }
    if (key == 'f')
    {
        ofToggleFullscreen();
    }
    else if (key == 'a')
    {
        this->areaMode = 1;
        if (this->areaMode == 1)
        {
            // Draw the full image for each warp.
            auto area = ofRectangle(0, 0, this->texture.getWidth(), this->texture.getHeight());
            for (auto i = 0; i < this->warpController.getNumWarps(); ++i)
            {
                this->srcAreas[i] = area;
            }
            this->areaName = "full";
        }
    }
    else if (key == 'd')
    {
        this->useBeginEnd ^= 1;
    }
    else if (key == OF_KEY_LEFT)
    {
        if (scene > 1) {
            scene--;
            cout << "Scene: " << scene <<endl;
        }
    }
    else if (key == OF_KEY_RIGHT)
    {
        if (scene < 6) {
            scene++;
            cout << "Scene: " << scene <<endl;
        }
    }
    else if (key == OF_KEY_UP)
    {
        speed++;
    }
    else if (key == OF_KEY_DOWN)
    {
        if (speed < 1) {
            speed = 1;
        } else speed--;
    }
}

void ofApp::initializeFbos() {
    fboTop.allocate(boxL, boxW, GL_RGBA);
        fboTop.begin();
        ofClear(255,255,255,0);
    fboTop.end();
    
    fboFront.allocate(boxL, boxH, GL_RGBA);
        fboFront.begin();
        ofClear(255,255,255,0);
    fboFront.end();
    
    fboSide.allocate(boxW, boxH, GL_RGBA);
        fboSide.begin();
        ofClear(255,255,255,0);
    fboSide.end();
}

void ofApp::initializeWarps() {
    boxL = 1600;
    boxW = 700;
    boxH = 1150;
    
    topW = boxL; topH = boxW;
    frontW = boxL; frontH = boxH;
    sideW = boxW; sideH = boxH;

    this->texture.enableMipmap();
    this->texture.loadData(testImage.getPixels()); //just to reset
    
    // Load warp settings from file if one exists.
    this->warpController.loadSettings("settings.json");
    if (this->warpController.getWarps().empty())
    {
        // Otherwise create warps from scratch.
        std::shared_ptr<ofxWarpBase> warp;
        
        warp = this->warpController.buildWarp<ofxWarpPerspective>();
        warp->setSize(this->texture.getWidth(), this->texture.getHeight());
        warp->setEdges(glm::vec4(0.0f, 0.0f, 0.5f, 0.5f));
        
        warp = this->warpController.buildWarp<ofxWarpPerspective>();
        warp->setSize(this->texture.getWidth(), this->texture.getHeight());
        warp->setEdges(glm::vec4(0.5f, 0.0f, 0.0f, 0.5f));
        
        warp = this->warpController.buildWarp<ofxWarpPerspective>();
        warp->setSize(this->texture.getWidth(), this->texture.getHeight());
        warp->setEdges(glm::vec4(0.5f, 0.5f, 0.0f, 0.0f));
    }
    this->srcAreas.resize(this->warpController.getNumWarps());
    this->areaMode = 1;
    this->useBeginEnd = true;
}

void ofApp::initializeAnchors() {
    
    boxedAnchor.set( topW/2 - 650, topH/2 - 100 );
    inAnchor.set( topW/2 , topH/2 - 100 );
    finAnchor.set(topW/2 - 150, topH/2 - 100);
    
    cBody.x = svgCBody.getWidth();
    cBody.y = svgCBody.getHeight();
    
    //initially facing left
    bBody.x = svgBBody.getWidth();
    bBody.y = svgBBody.getHeight();
    
    //intially facing top
    bBodyTop.x = svgBBody.getWidth();
    bBodyTop.y = svgBBody.getHeight();
    
    //scene anchors
    scene1[0] = ofPoint(-50, 250);
    scene1[1] = ofPoint(700, 580);
    scene1[2] = ofPoint(1090, 195);
    scene1[3] = ofPoint(1310, 660);
    
    scene2b[0] = ofPoint(1310, 660);
    scene2b[1] = ofPoint(1300, 700);
    scene2b[2] = ofPoint(1300, 0);
    scene2b[3] = ofPoint(800, 160);
    scene2b[4] = ofPoint(200, 470);
    scene2b[5] = ofPoint(420, 825);
    
    scene2c[0] = ofPoint(300, 910);
    scene2c[1] = ofPoint(300, 710);
    
    scene3b[0] = ofPoint(400, 825);
    scene3b[1] = ofPoint(605, 660);
    scene3b[2] = ofPoint(800, 825);
    scene3b[3] = ofPoint(1005, 660);
    scene3b[4] = ofPoint(1200, 825);
    
    scene3c[0] = ofPoint(300, 710);
    scene3c[1] = ofPoint(800, 710);
    scene3c[2] = ofPoint(1300, 710);
    
    scene4b[0] = ofPoint(1200, 825);
    scene4b[1] = ofPoint(1005, 660);
    scene4b[2] = ofPoint(800, 825);
    scene4b[3] = ofPoint(605, 660);
    scene4b[4] = ofPoint(400, 825);
    
    scene4c[0] = ofPoint(1300, 710);
    scene4c[1] = ofPoint(800, 710);
    scene4c[2] = ofPoint(300, 710);
    scene4c[3] = ofPoint(300, 750);
    
    scene5b[0] = ofPoint(400, 825);
    scene5b[1] = ofPoint(0, 590);
    scene5b[2] = ofPoint(700, 590);
    scene5b[3] = ofPoint(500, 410);
    scene5b[4] = ofPoint(220, 825);
    
    scene5c[0] = ofPoint(300, 750);
    scene5c[1] = ofPoint(300, 710);
    scene5c[2] = ofPoint(0, 710);
    scene5c[3] = ofPoint(700, 710);
    scene5c[4] = ofPoint(350, 710);
    scene5c[5] = ofPoint(350, 750);
    
    scene6b[0] = ofPoint(220, 825);
    scene6b[1] = ofPoint(700, 750);
    scene6b[2] = ofPoint(0, 750);
    scene6b[3] = ofPoint(300, 730);
    scene6b[4] = ofPoint(800, 400);
    scene6b[5] = ofPoint(980, 825);
    
    scene6c[0] = ofPoint(350, 750);
    scene6c[1] = ofPoint(350, 710);
    scene6c[2] = ofPoint(700, 710);
    scene6c[3] = ofPoint(0, 710);
    scene6c[4] = ofPoint(300, 710);
    scene6c[5] = ofPoint(800, 710);
    scene6c[6] = ofPoint(800, 750);
}

void ofApp::initializeSvgs() {
    
    //apartment
    svgFront.load("apartment/apartment_front.svg");
    svgSide.load("apartment/apartment_side.svg");
    svgSideBack.load("apartment/apartment_side_back.svg");
    svgTop.load("apartment/apartment_top.svg");
    
    //character
    svgCBody.load("character/c_body.svg");
    //bird
    svgBBody.load("bird/b_body.svg");
    svgBBodyTop.load("bird/b_body_top.svg");
    
   //text
    svgBoxed.load("text/boxed.svg");
    svgIn.load("text/in.svg");
    
}

void ofApp::initializePngs() {

    faces[0].load("character/c_face0.png");
    faces[1].load("character/c_face1.png");
    faces[2].load("character/c_face2.png");
    faces[3].load("character/c_face3.png");
    faces[4].load("character/c_face4.png");
    faces[5].load("character/c_face5.png");
    for (int i = 0; i < 6; i++) {
        faces[i].setImageType(OF_IMAGE_COLOR_ALPHA);
        faces[i].setAnchorPoint(faces[i].getWidth()/2, faces[i].getHeight()/2);
    }
    
    hands[0].load("character/c_hands0.png");
    hands[1].load("character/c_hands1.png");
    hands[2].load("character/c_hands2.png");
    for (int i = 0; i < 3; i++) {
        hands[i].setImageType(OF_IMAGE_COLOR_ALPHA);
        hands[i].setAnchorPoint(hands[i].getWidth()/2, hands[i].getHeight()/2);
    }
    
    bTopImg1.load("bird/b_body_topW.png");
    bTopImg1.setImageType(OF_IMAGE_COLOR_ALPHA);
    bTopImg1.setAnchorPoint(bTopImg1.getWidth()/2, bTopImg1.getHeight()/2);
    bTopImg2.load("bird/b_body_topNW.png");
    bTopImg2.setImageType(OF_IMAGE_COLOR_ALPHA);
    bTopImg2.setAnchorPoint(bTopImg2.getWidth()/2, bTopImg2.getHeight()/2);
    
    bTopWing1.load("bird/b_wing_top1.png");
    bTopWing1.setImageType(OF_IMAGE_COLOR_ALPHA);
    bTopWing1.setAnchorPoint(bTopWing1.getWidth()/2, bTopWing1.getHeight()/2);
    bTopWing2.load("bird/b_wing_top2.png");
    bTopWing2.setImageType(OF_IMAGE_COLOR_ALPHA);
    bTopWing2.setAnchorPoint(bTopWing2.getWidth()/2, bTopWing2.getHeight()/2);
    bTopWing3.load("bird/b_wing_top3.png");
    bTopWing3.setImageType(OF_IMAGE_COLOR_ALPHA);
    bTopWing3.setAnchorPoint(bTopWing3.getWidth()/2, bTopWing3.getHeight()/2);
    
    bSideWingLeft1.load("bird/b_wing_side1.png");
    bSideWingLeft1.setImageType(OF_IMAGE_COLOR_ALPHA);
    bSideWingLeft1.setAnchorPoint(bSideWingLeft1.getWidth()/2, bSideWingLeft1.getHeight()/2);
    bSideWingLeft2.load("bird/b_wing_side2.png");
    bSideWingLeft2.setImageType(OF_IMAGE_COLOR_ALPHA);
    bSideWingLeft2.setAnchorPoint(bSideWingLeft2.getWidth()/2, bSideWingLeft2.getHeight()/2);
    
    bSideWingRight1 = bSideWingLeft1;
    bSideWingRight1.mirror(false, true);
    bSideWingRight1.setImageType(OF_IMAGE_COLOR_ALPHA);
    bSideWingRight1.setAnchorPoint(bSideWingRight1.getWidth()/2, bSideWingRight1.getHeight()/2);
    
    bSideWingRight2 = bSideWingLeft2;
    bSideWingRight2.mirror(false, true);
    bSideWingRight2.setImageType(OF_IMAGE_COLOR_ALPHA);
    bSideWingRight2.setAnchorPoint(bSideWingRight2.getWidth()/2, bSideWingRight2.getHeight()/2);
    
    bLeft1.load("bird/b_body_sideW.png");
    bLeft1.setImageType(OF_IMAGE_COLOR_ALPHA);
    bLeft1.setAnchorPoint(bLeft1.getWidth()/2, bLeft1.getHeight()/2);
    
    bRight1 = bLeft1;
    bRight1.mirror(false, true);
    bRight1.setImageType(OF_IMAGE_COLOR_ALPHA);
    bRight1.setAnchorPoint(bRight1.getWidth()/2, bRight1.getHeight()/2);
    
    bLeft2.load("bird/b_body_sideNW.png");
    bLeft2.setImageType(OF_IMAGE_COLOR_ALPHA);
    bLeft2.setAnchorPoint(bLeft2.getWidth()/2, bLeft2.getHeight()/2);
    
    bRight2 = bLeft2;
    bRight2.mirror(false, true);
    bRight2.setImageType(OF_IMAGE_COLOR_ALPHA);
    bRight2.setAnchorPoint(bRight2.getWidth()/2, bRight2.getHeight()/2);
    
    cImg.load("character/c_body.png");
    cImg.setImageType(OF_IMAGE_COLOR_ALPHA);
    cImg.setAnchorPoint(cImg.getWidth()/2, cImg.getHeight()/2);
    
    boxedImg.load("text/boxed.png");
    boxedImg.setImageType(OF_IMAGE_COLOR_ALPHA);
//    boxedImg.setAnchorPoint(boxedImg.getWidth()/2, boxedImg.getHeight()/2);
    
    inImg.load("text/in.png");
    inImg.setImageType(OF_IMAGE_COLOR_ALPHA);
//    inImg.setAnchorPoint(inImg.getWidth()/2, inImg.getHeight()/2);
    finImg.load("text/fin.png");
    finImg.setImageType(OF_IMAGE_COLOR_ALPHA);
    
    angryImg.load("emotes/angry.png");
    angryImg.setImageType(OF_IMAGE_COLOR_ALPHA);
    angryImg.setAnchorPoint(angryImg.getWidth()/2, angryImg.getHeight()/2);
    
    curiousImg.load("emotes/curious.png");
    curiousImg.setImageType(OF_IMAGE_COLOR_ALPHA);
    curiousImg.setAnchorPoint(curiousImg.getWidth()/2, curiousImg.getHeight()/2);
    
    singImg.load("emotes/sing.png");
    singImg.setImageType(OF_IMAGE_COLOR_ALPHA);
    singImg.setAnchorPoint(singImg.getWidth()/2, singImg.getHeight()/2);
}

void ofApp::initializeAnimationPolylines() {
    //top
    sPoly1[0].addVertex(scene1[0].x, scene1[0].y);
    sPoly1[0].addVertex(scene1[1].x, scene1[1].y);
    sPoly1[1].addVertex(scene1[1].x, scene1[1].y);
    sPoly1[1].addVertex(scene1[2].x, scene1[2].y);
    sPoly1[2].addVertex(scene1[2].x, scene1[2].y);
    sPoly1[2].addVertex(scene1[3].x, scene1[3].y);
    //top
    sPoly2b[0].addVertex(scene2b[0].x, scene2b[0].y);
    sPoly2b[0].addVertex(scene2b[1].x, scene2b[1].y);
    //          front
    sPoly2b[1].addVertex(scene2b[2].x, scene2b[2].y);
    sPoly2b[1].addVertex(scene2b[3].x, scene2b[3].y);
    sPoly2b[2].addVertex(scene2b[3].x, scene2b[3].y);
    sPoly2b[2].addVertex(scene2b[4].x, scene2b[4].y);
    sPoly2b[3].addVertex(scene2b[4].x, scene2b[4].y);
    sPoly2b[3].addVertex(scene2b[5].x, scene2b[5].y);
    sPoly2c[0].addVertex(scene2c[0].x, scene2c[0].y);
    sPoly2c[0].addVertex(scene2c[1].x, scene2c[1].y);
    //          front
    sPoly3b[0].addVertex(scene3b[0].x, scene3b[0].y);
    sPoly3b[0].addVertex(scene3b[1].x, scene3b[1].y);
    sPoly3b[0].addVertex(scene3b[2].x, scene3b[2].y);
    sPoly3b[1].addVertex(scene3b[2].x, scene3b[2].y);
    sPoly3b[1].addVertex(scene3b[3].x, scene3b[3].y);
    sPoly3b[1].addVertex(scene3b[4].x, scene3b[4].y);
    sPoly3c[0].addVertex(scene3c[0].x, scene3c[0].y);
    sPoly3c[0].addVertex(scene3c[1].x, scene3c[1].y);
    sPoly3c[1].addVertex(scene3c[1].x, scene3c[1].y);
    sPoly3c[1].addVertex(scene3c[2].x, scene3c[2].y);
    //          front
    sPoly4b[0].addVertex(scene4b[0].x, scene4b[0].y);
    sPoly4b[0].addVertex(scene4b[1].x, scene4b[1].y);
    sPoly4b[0].addVertex(scene4b[2].x, scene4b[2].y);
    sPoly4b[1].addVertex(scene4b[2].x, scene4b[2].y);
    sPoly4b[1].addVertex(scene4b[3].x, scene4b[3].y);
    sPoly4b[1].addVertex(scene4b[4].x, scene4b[4].y);
    
    sPoly4c[0].addVertex(scene4c[0].x, scene4c[0].y);
    sPoly4c[0].addVertex(scene4c[1].x, scene4c[1].y);
    sPoly4c[1].addVertex(scene4c[1].x, scene4c[1].y);
    sPoly4c[1].addVertex(scene4c[2].x, scene4c[2].y);
    sPoly4c[2].addVertex(scene4c[2].x, scene4c[2].y);
    sPoly4c[2].addVertex(scene4c[3].x, scene4c[3].y);
    //          front
    sPoly5b[0].addVertex(scene5b[0].x, scene5b[0].y);
    sPoly5b[0].addVertex(scene5b[1].x, scene5b[1].y);
    //side
    sPoly5b[1].addVertex(scene5b[2].x, scene5b[2].y);
    sPoly5b[1].addVertex(scene5b[3].x, scene5b[3].y);
    sPoly5b[2].addVertex(scene5b[3].x, scene5b[3].y);
    sPoly5b[2].addVertex(scene5b[4].x, scene5b[4].y);
    //          front
    sPoly5c[0].addVertex(scene5c[0].x, scene5c[0].y);
    sPoly5c[0].addVertex(scene5c[1].x, scene5c[1].y);
    sPoly5c[1].addVertex(scene5c[1].x, scene5c[1].y);
    sPoly5c[1].addVertex(scene5c[2].x, scene5c[2].y);
    //side
    sPoly5c[2].addVertex(scene5c[3].x, scene5c[3].y);
    sPoly5c[2].addVertex(scene5c[4].x, scene5c[4].y);
    sPoly5c[3].addVertex(scene5c[4].x, scene5c[4].y);
    sPoly5c[3].addVertex(scene5c[5].x, scene5c[5].y);
    //side
    sPoly6b[0].addVertex(scene6b[0].x, scene6b[0].y);
    sPoly6b[0].addVertex(scene6b[1].x, scene6b[1].y);
    //          front
    sPoly6b[1].addVertex(scene6b[2].x, scene6b[2].y);
    sPoly6b[1].addVertex(scene6b[3].x, scene6b[3].y);
    sPoly6b[2].addVertex(scene6b[3].x, scene6b[3].y);
    sPoly6b[2].addVertex(scene6b[4].x, scene6b[4].y);
    sPoly6b[3].addVertex(scene6b[4].x, scene6b[4].y);
    sPoly6b[3].addVertex(scene6b[5].x, scene6b[5].y);
    //side
    sPoly6c[0].addVertex(scene6c[0].x, scene6c[0].y);
    sPoly6c[0].addVertex(scene6c[1].x, scene6c[1].y);
    sPoly6c[1].addVertex(scene6c[1].x, scene6c[1].y);
    sPoly6c[1].addVertex(scene6c[2].x, scene6c[2].y);
    //          front
    sPoly6c[2].addVertex(scene6c[3].x, scene6c[3].y);
    sPoly6c[2].addVertex(scene6c[4].x, scene6c[4].y);
    sPoly6c[3].addVertex(scene6c[4].x, scene6c[4].y);
    sPoly6c[3].addVertex(scene6c[5].x, scene6c[5].y);
    sPoly6c[4].addVertex(scene6c[5].x, scene6c[5].y);
    sPoly6c[4].addVertex(scene6c[6].x, scene6c[6].y);
}

void ofApp::svgToPolyline(ofxSVG svg) {
        
    for (ofPath p: svg.getPaths()){
        p.setPolyWindingMode(OF_POLY_WINDING_ODD);
        const vector<ofPolyline>& lines = p.getOutline();
        for(const ofPolyline & line: lines){
            outlines.push_back(line.getResampledBySpacing(1));
        }
    }
}

void ofApp::updateTopFbo() {

    fboTop.begin();
        ofClear(255,255,255, 0);
        svgTop.draw();
        
    if (scene == 1) {
        drawBirdTop(birdPos.x, birdPos.y, angleToRotate + 0.10);
        
        if (sequence == 1) {
        //finImg.draw(finAnchor.x, finAnchor.y);
            ofSetColor(255, 255, 255, fade);
            boxedImg.draw(boxedAnchor.x, boxedAnchor.y);
        }
        if (sequence >=2) {
            boxedImg.draw(boxedAnchor.x, boxedAnchor.y);
        }
        if (sequence == 3) {
            ofSetColor(255, 255, 255, fade);
            inImg.draw(inAnchor.x, inAnchor.y);
        }
        if (sequence >=4) {
              inImg.draw(inAnchor.x, inAnchor.y);
       }
    }
    if (scene == 2) {
        if (sequence == 1) {
            drawBirdTop(birdPos.x, birdPos.y, angleToRotate + 0.10);
        }
    }
    if (scene == 6) {
        if (sequence == 9) {
            if (fade < 255) {
                ofSetColor(255, 255, 255, fade);
                finImg.draw(finAnchor.x, finAnchor.y);
                inImg.draw(inAnchor.x, inAnchor.y);
            } else {
                finImg.draw(finAnchor.x, finAnchor.y);
                inImg.draw(inAnchor.x, inAnchor.y);
            }
        }
    }
   fboTop.end();
}
void ofApp::updateFrontFbo() {
   
    fboFront.begin();
        ofClear(255,255,255, 0);
    
    if (scene == 1) {
        svgFront.draw();
    }
    if (scene == 2) {
        drawMan(manPos.x, manPos.y);
        if (sequence == 8) {
            faces[2].draw(manPos.x, manPos.y - 100);
            curiousImg.draw(manPos.x, manPos.y - 300);
        }
        
        svgFront.draw();
        
        if (sequence > 1 && sequence <= 5 ) { // 1,2,3,4,5
            drawBirdSide(birdPos.x, birdPos.y, true);
            
        }
        else if (sequence >= 6 ) {
            drawBirdSide(birdPos.x, birdPos.y, false);
        }
       if (sequence >= 7) {
            singImg.draw(scene2b[5].x, scene2b[5].y - 100);
        }
    }
    if (scene == 3) {
        drawMan(manPos.x, manPos.y);
        faces[1].draw(manPos.x, manPos.y - 100);
        if (sequence == 5) {
            hands[0].draw(manPos.x + 20, manPos.y + 20);
        }
        svgFront.draw();
        
        drawBirdSide(birdPos.x, birdPos.y, false);
        if (sequence == 3) {
            singImg.draw(scene3b[2].x, scene3b[2].y - 100);
        }
        if (sequence >= 5) {
            singImg.draw(scene3b[4].x, scene3b[4].y - 100);
        }
    }
    if (scene == 4) {
        drawMan(manPos.x, manPos.y);
        faces[1].draw(manPos.x, manPos.y - 100);
        if (sequence == 6) {
            hands[1].draw(manPos.x, manPos.y);
        }
        svgFront.draw();
        
        drawBirdSide(birdPos.x, birdPos.y, true);
        if (sequence == 3) {
            singImg.draw(scene3b[2].x, scene3b[2].y - 100);
        }
        if (sequence >= 6) {
            singImg.draw(scene4b[4].x, scene4b[4].y - 100);
        }
    }
    if (scene == 5) {
        if (sequence < 3) {
            drawMan(manPos.x, manPos.y);
            faces[1].draw(manPos.x, manPos.y - 100);
        }
        svgFront.draw();
        
        if (sequence <= 2) {
           drawBirdSide(birdPos.x, birdPos.y, true);
       }
        
    }
    if (scene == 6) {
        if (sequence > 2 && sequence < 6) {
            drawMan(manPos.x, manPos.y);
            faces[3].draw(manPos.x, manPos.y - 100);
        } else if (sequence >= 6 && sequence < 7) {
            drawMan(manPos.x, manPos.y);
            faces[4].draw(manPos.x, manPos.y - 100);
        } else if (sequence >= 7 ) {
            drawMan(manPos.x, manPos.y);
            faces[5].draw(manPos.x, manPos.y - 100);
        }
        
        svgFront.draw();
        
        if (sequence > 1 && sequence <=7 ) {
            drawBirdSide(birdPos.x, birdPos.y, false);
        }
        if (sequence >= 8) {
            drawBirdSide(birdPos.x, birdPos.y, true);
        }
        if (sequence == 8) {
            singImg.draw(scene6b[5].x, scene6b[5].y - 100);
        }
        if (sequence == 9) {
            singImg.draw(scene6c[6].x, scene6c[6].y - 300);
        }
    }
    fboFront.end();
}
void ofApp::updateSideFbo() {
    
   fboSide.begin();
       //similar to Processing clear canvas each draw
       ofClear(255,255,255, 0);
       if (scene == 1) {
           svgSideBack.draw();
           svgSide.draw();
       }
       if (scene == 2) {
           svgSideBack.draw();
           svgSide.draw();
       }
       if (scene == 3) {
           svgSideBack.draw();
           svgSide.draw();
       }
       if (scene == 4) {
           svgSideBack.draw();
           svgSide.draw();
       }
       if (scene == 5) {
           svgSideBack.draw();
           if (sequence > 2) {
               drawMan(manPos.x, manPos.y);
               faces[1].draw(manPos.x, manPos.y - 100);
           }
           if (sequence >= 4) {
               hands[2].draw(manPos.x, manPos.y);
           }
           svgSide.draw();
           
           if (sequence > 2 && sequence <= 5) {
               drawBirdSide(birdPos.x, birdPos.y, true);
           }
           if (sequence == 6 ) {
               drawBirdSide(birdPos.x, birdPos.y, false);
           }
           if (sequence == 7 ) {
               drawBirdSide(birdPos.x, birdPos.y, false);
               singImg.draw(scene5b[4].x, scene5b[4].y - 100);
           }
       }
       if (scene == 6) {
           svgSideBack.draw();
           if (sequence < 3) {
               drawMan(manPos.x, manPos.y);
               faces[3].draw(manPos.x, manPos.y - 100);
           }
           svgSide.draw();
           
           if (sequence == 1) {
               drawBirdSide(birdPos.x, birdPos.y, false);
           }
       }
   fboSide.end();
}

//updates the counter for drawing polylines incrementally
void ofApp::updateStepPolyline() {
    
}

//in draw(), draws the polyline incrementally
void  ofApp::drawPolyline(vector<ofPolyline> outlines, float pct) {
    
    ofNoFill();
    for (ofPolyline & line: outlines){
        int num = pct * line.size();
        
        ofBeginShape();
        for (int j = 0; j < num; j++){
            ofVertex(line[j]);
        }
        ofEndShape();
    }
}

float ofApp::getAngle(ofPoint point1 , ofPoint point2) {
    ofPoint lineBetween  = point1 - point2; //point 1 > point 2
    float theta = atan2(lineBetween.x,lineBetween.y);
    return theta;
}

void ofApp::drawBirdTop(int x, int y, float angle) {
    ofPushMatrix();
        ofTranslate(x, y);
        ofRotateZRad(angle);
        ofPushStyle();
            ofEnableAlphaBlending();
            ofDisableDepthTest();
            ofSetColor(255, 255, 255, 255);
            if (isFlapping) {
                bTopImg2.draw(0,0);
                drawBirdWingsTop(0, 0);
            } else {
                bTopImg1.draw(0,0);
            }
        ofPopStyle();
    ofPopMatrix();
    
}

void ofApp::drawBirdWingsTop(int x, int y) {
    //alternate between three positions
    int percent = pct * 100;
    if (percent % 3 == 0) {
        bTopWing1.draw(x,y + 15);
    } else if (percent % 3 == 1) {
        bTopWing2.draw(x,y - 20);
    } else if (percent % 3 == 2) {
       bTopWing3.draw(x,y - 25 );
    }
}

void ofApp::drawBirdSide(int x, int y, bool faceLeft) {
   
    ofPushMatrix();
        ofTranslate(x, y);
        ofPushStyle();
            ofEnableAlphaBlending();
            ofDisableDepthTest();
            ofSetColor(255, 255, 255, 255);
            if (!faceLeft) {
                if (isFlapping) {
                    bRight2.draw(0,0);
                    drawBirdWingsSide(0, 0, false);
                } else {
                    bRight1.draw(0,0);
                }
                
            } else {
                if (isFlapping) {
                    bLeft2.draw(0,0);
                    drawBirdWingsSide(0, 0, true);
                } else {
                    bLeft1.draw(0,0);
                }
            }
        ofPopStyle();
        
    ofPopMatrix();
}
void ofApp::drawBirdWingsSide(int x, int y, bool faceLeft) {
    //alternate between two positions
    int percent = pct * 100;
    if (percent % 2 == 0) {
        if (faceLeft) {
            bSideWingLeft1.draw(x,y + 30);
        }
        else {
            bSideWingRight1.draw(x+15,y + 30);
        }
    } else if (percent % 2 == 1) {
         if (faceLeft) {
             bSideWingLeft2.draw(x + 50,y - 20);
         }
         else {
             bSideWingRight2.draw(x - 30,y - 20);
         }
    }
}


void ofApp::drawMan(int x, int y) {
    ofPushMatrix();
        ofTranslate(x, y);
        ofPushStyle();
            ofEnableAlphaBlending();
            ofDisableDepthTest();
            ofSetColor(255, 255, 255, 255);
            cImg.draw(0,0);
        ofPopStyle();
    ofPopMatrix();
}

void ofApp::drawFace(int x, int y) {
   
   //face
   ofSetColor(ofColor::white);
   face.width = faceWidth;
   face.height = faceHeight;
   face.x = x - faceWidth/2;
   face.y = y - faceHeight/2;
   ofDrawRectRounded(face, 80);
   
   //left eye
   ofSetColor(ofColor::black);
   ofDrawCircle(x - eyeDistanceX , y - eyeDistanceY , eyeSize);
   //right eye
   ofDrawCircle(x + eyeDistanceX , y - eyeDistanceY , eyeSize);
   
   //nose polyline
    ofPolyline nose;
    nose.addVertex(ofVec3f(x, y - noseHeight/2,0));
    nose.addVertex(ofVec3f(x - noseWidth/2, y + noseHeight/2, 0));
    nose.addVertex(ofVec3f(x + noseWidth/2, y + noseHeight/2, 0));
    nose.close();
    nose.draw();
    
    //converts nose polyline to shape
    ofBeginShape();
         for( int i = 0; i < nose.getVertices().size(); i++) {
             ofVertex(nose.getVertices().at(i).x, nose.getVertices().at(i).y);
         }
     ofEndShape();
    
// using primitives
//  ofDrawTriangle(x, y - noseHeight/2,
//                 x - noseWidth/2, y + noseHeight/2,
//                 x + noseWidth/2, y + noseHeight/2);
   
}
