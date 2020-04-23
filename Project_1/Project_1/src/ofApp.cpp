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
    
    pct = 1;
    scene = 1;
    sequence = 1;
    progress = 0;
    speed = 1;
    //currentTime = ofGetFrameNum();
}

//--------------------------------------------------------------
void ofApp::exit()
{
    this->warpController.saveSettings("settings.json");
}

//--------------------------------------------------------------
void ofApp::update()
{
    pct += speed;
    if (scene == 1) { //===========   ===   =================
        if (sequence == 1) {
            if (pct < 100) {
                progress = pct / 100.0;
                bird = sPoly1[0].getPointAtPercent(progress);
                angleToRotate = getAngle(scene1[1], scene1[0]);
            } else {
                sequence++;
                pct = 0;
            }
        }
        if (sequence == 2) {
            if (pct < 100) { //adjust for delay
                progress = pct / 100.0;
            } else {
                sequence++;
                pct = 0;
            }
        }
        if (sequence == 3) {
            if (pct < 100) {
                progress = pct / 100.0;
                bird = sPoly1[1].getPointAtPercent(progress);
                
                prevPathAngle = getAngle(scene1[1], scene1[0]);
                currPathAngle = getAngle(scene1[2], scene1[1]);
                if (currPathAngle > prevPathAngle) {
                    angleToRotate = currPathAngle - prevPathAngle;
                } else {
                     angleToRotate = prevPathAngle - currPathAngle;
                }
            } else {
                sequence++;
                pct = 0;
            }
        }
        if (sequence == 4) {
            if (pct < 100) {
                progress = pct / 100.0;
            } else {
                sequence++;
                pct = 0;
            }
        }
        if (sequence == 5) {
            if (pct < 100) {
                progress = pct / 100.0;
                bird = sPoly1[2].getPointAtPercent(progress);
                prevPathAngle = getAngle(scene1[2], scene1[1]);
                currPathAngle = getAngle(scene1[3], scene1[2]);
                angleToRotate = prevPathAngle - currPathAngle;
            } else {
                sequence++;
                pct = 0;
            }
        }
        if (sequence == 6) {
            if (pct < 100) {
                progress = pct / 100.0;
            } else {
                scene++;
                pct = 0;
                sequence = 1;
            }
        }
    }
    if (scene == 2) {//===========   ===   ===   =================
        if (sequence == 1) {
            if (pct < 100) {
                progress = pct / 100.0;
                bird = sPoly2b[0].getPointAtPercent(progress);
                angleToRotate = getAngle(scene2b[1], scene2b[0]);
            } else {
                sequence++;
                pct = 0;
            }
        }
        if (sequence == 2) {
            if (pct < 100) {
                progress = pct / 100.0;
                bird = sPoly2b[1].getPointAtPercent(progress);
            } else {
                sequence++;
                pct = 0;
            }
        }
        if (sequence == 3) {
            if (pct < 100) {
                progress = pct / 100.0;
            } else {
                sequence++;
                pct = 0;
            }
        }
        if (sequence == 4) {
            if (pct < 100) {
                progress = pct / 100.0;
                bird = sPoly2b[2].getPointAtPercent(progress);
            } else {
                sequence++;
                pct = 0;
            }
        }
        if (sequence == 5) {
            if (pct < 100) {
                progress = pct / 100.0;
                
            } else {
                sequence++;
                pct = 0;
            }
        }
        if (sequence == 6) {
            if (pct < 100) {
                progress = pct / 100.0;
                bird = sPoly2b[3].getPointAtPercent(progress);
            } else {
                sequence++;
                pct = 0;
            }
        }
        if (sequence == 7) {
            if (pct < 100) {
                progress = pct / 100.0;
                man = sPoly2c[0].getPointAtPercent(progress);
            } else {
                scene++;
                pct = 0;
                sequence = 1;
            }
        }
        
    }
    if (scene == 3) { //===========   ===   ===  ===  =================
        if (sequence == 1) {
            if (pct < 100) {
                progress = pct / 100.0;
                man = sPoly3c[0].getPointAtPercent(progress);
            } else {
                sequence++;
                pct = 0;
            }
        }
        if (sequence == 2) {
            if (pct < 100) {
                progress = pct / 100.0;
                bird = sPoly3b[0].getPointAtPercent(progress);
            } else {
                sequence++;
                pct = 0;
            }
        }
        if (sequence == 3) {
            if (pct < 100) {
                progress = pct / 100.0;
                man = sPoly3c[1].getPointAtPercent(progress);
            } else {
                sequence++;
                pct = 0;
            }
        }
        if (sequence == 4) {
            if (pct < 100) {
                progress = pct / 100.0;
                bird = sPoly3b[1].getPointAtPercent(progress);
                //pick up cup
            } else {
                sequence++;
                pct = 0;
            }
        }
        if (sequence == 5) {
            if (pct < 100) {
                progress = pct / 100.0;
            } else {
                scene++;
                pct = 0;
                sequence = 1;
            }
            
        }
    }
    if (scene == 4) { //===========   ===   ===  ===  ===  =================
        if (sequence == 1) {
            if (pct < 100) {
                progress = pct / 100.0;
                man = sPoly4c[0].getPointAtPercent(progress);
            } else {
                sequence++;
                pct = 0;
            }
        }
        if (sequence == 2) {
            if (pct < 100) {
                progress = pct / 100.0;
                bird = sPoly4b[0].getPointAtPercent(progress);
            } else {
                sequence++;
                pct = 0;
            }
        }
        if (sequence == 3) {
            if (pct < 100) {
                progress = pct / 100.0;
                man = sPoly4c[1].getPointAtPercent(progress);
            } else {
                sequence++;
                pct = 0;
            }
        }
        if (sequence == 4) {
            if (pct < 100) {
                progress = pct / 100.0;
                bird = sPoly4b[1].getPointAtPercent(progress);
            } else {
                sequence++;
                pct = 0;
            }
        }
        if (sequence == 5) {
            if (pct < 100) {
                progress = pct / 100.0;
                man = sPoly4c[2].getPointAtPercent(progress);
            } else {
                scene++;
                pct = 0;
                sequence = 1;
            }
            
        }
    }
    if (scene == 5) { //===========   ===   ===  ===  ===  ===   =================
        if (sequence == 1) {
            if (pct < 100) {
                progress = pct / 100.0;
                man = sPoly5c[0].getPointAtPercent(progress);
                
            } else {
                sequence++;
                pct = 0;
            }
        }
        if (sequence == 2) {
            if (pct < 100) {
                progress = pct / 100.0;
                bird = sPoly5b[0].getPointAtPercent(progress);
                man = sPoly5c[1].getPointAtPercent(progress);
            } else {
                sequence++;
                pct = 0;
            }
        }
        if (sequence == 3) {
            if (pct < 100) {
                progress = pct / 100.0;
                bird = sPoly5b[1].getPointAtPercent(progress);
                man = sPoly5c[2].getPointAtPercent(progress);
            } else {
                sequence++;
                pct = 0;
            }
        }
        if (sequence == 4) {
            if (pct < 100) {
                progress = pct / 100.0;
                man = sPoly5c[3].getPointAtPercent(progress);
            } else {
                sequence++;
                pct = 0;
            }
        }
        if (sequence == 5) {
            if (pct < 100) {
                progress = pct / 100.0;
                bird = sPoly5b[2].getPointAtPercent(progress);
            } else {
                sequence++;
                pct = 0;
            }
        }
        if (sequence == 6) {
            if (pct < 100) {
                progress = pct / 100.0;
            } else {
                scene++;
                pct = 0;
                sequence = 1;
            }
            
        }
    }
    if (scene == 6) { //===========   ===   ===  ===  ===  ===   ===   =================
        if (sequence == 1) {
            if (pct < 100) {
                progress = pct / 100.0;
                bird = sPoly6b[0].getPointAtPercent(progress);
                man = sPoly6c[0].getPointAtPercent(progress);
            } else {
                sequence++;
                pct = 0;
            }
        }
        if (sequence == 2) {
            if (pct < 100) {
                progress = pct / 100.0;
                bird = sPoly6b[1].getPointAtPercent(progress);
                man = sPoly6c[1].getPointAtPercent(progress);
            } else {
                sequence++;
                pct = 0;
            }
        }
        if (sequence == 3) {
            if (pct < 100) {
                progress = pct / 100.0;
                man = sPoly6c[2].getPointAtPercent(progress);
            } else {
                sequence++;
                pct = 0;
            }
        }
        if (sequence == 4) {
            if (pct < 100) {
                progress = pct / 100.0;
                bird = sPoly6b[2].getPointAtPercent(progress);
            } else {
                sequence++;
                pct = 0;
            }
        }
        if (sequence == 5) {
            if (pct < 100) {
                progress = pct / 100.0;
                man = sPoly6c[3].getPointAtPercent(progress);
            } else {
                sequence++;
                pct = 0;
            }
        }
        if (sequence == 6) {
            if (pct < 100) {
                progress = pct / 100.0;
                bird = sPoly6b[3].getPointAtPercent(progress);
                
            } else {
                sequence++;
                pct = 0;
            }
        }
        if (sequence == 7) {
            if (pct < 100) {
                progress = pct / 100.0;
                man = sPoly6c[4].getPointAtPercent(progress);
            } else {
                sequence++;
                pct = 0;
            }
        }
        if (sequence == 8) {
            if (pct < 100) {
                progress = pct / 100.0;
                
            } else {
                sequence++;
                pct = 0;
            }
        }
        if (sequence == 9) {
            if (pct < 100) {
                progress = pct / 100.0;
            } else {
                pct = 0;
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
    scene2b[3] = ofPoint(800, 180);
    scene2b[4] = ofPoint(200, 470);
    scene2b[5] = ofPoint(420, 825);
    
    scene2c[0] = ofPoint(300, 910);
    scene2c[1] = ofPoint(300, 710);
    
    scene3b[0] = ofPoint(400, 850);
    scene3b[1] = ofPoint(605, 690);
    scene3b[2] = ofPoint(800, 850);
    scene3b[3] = ofPoint(1005, 690);
    scene3b[4] = ofPoint(1200, 850);
    
    scene3c[0] = ofPoint(300, 710);
    scene3c[1] = ofPoint(800, 710);
    scene3c[2] = ofPoint(1300, 710);
    
    scene4b[0] = ofPoint(1200, 850);
    scene4b[1] = ofPoint(1005, 690);
    scene4b[2] = ofPoint(800, 850);
    scene4b[3] = ofPoint(605, 690);
    scene4b[4] = ofPoint(400, 850);
    
    scene4c[0] = ofPoint(1300, 710);
    scene4c[1] = ofPoint(800, 710);
    scene4c[2] = ofPoint(300, 710);
    scene4c[3] = ofPoint(300, 750);
    
    scene5b[0] = ofPoint(400, 850);
    scene5b[1] = ofPoint(0, 590);
    scene5b[2] = ofPoint(700, 590);
    scene5b[3] = ofPoint(500, 430);
    scene5b[4] = ofPoint(220, 850);
    
    scene5c[0] = ofPoint(300, 750);
    scene5c[1] = ofPoint(300, 710);
    scene5c[2] = ofPoint(0, 710);
    scene5c[3] = ofPoint(700, 710);
    scene5c[4] = ofPoint(350, 710);
    scene5c[5] = ofPoint(350, 750);
    
    scene6b[0] = ofPoint(220, 850);
    scene6b[1] = ofPoint(700, 750);
    scene6b[2] = ofPoint(0, 750);
    scene6b[3] = ofPoint(300, 730);
    scene6b[4] = ofPoint(800, 400);
    scene6b[5] = ofPoint(980, 850);
    
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
    //imgFront.load("front_night.png");
    bTopImg.load("bird/b_body_top.png");
    bTopImg.setImageType(OF_IMAGE_COLOR_ALPHA);
    bTopImg.setAnchorPoint(bTopImg.getWidth()/2, bTopImg.getHeight()/2);
    
    bImgFaceLeft.load("bird/b_body.png");
    bImgFaceLeft.setImageType(OF_IMAGE_COLOR_ALPHA);
    bImgFaceLeft.setAnchorPoint(bImgFaceLeft.getWidth()/2, bImgFaceLeft.getHeight()/2);
    
    bImgFaceRight = bImgFaceLeft;
    bImgFaceRight.mirror(false, true);
    bImgFaceRight.setImageType(OF_IMAGE_COLOR_ALPHA);
    bImgFaceRight.setAnchorPoint(bImgFaceRight.getWidth()/2, bImgFaceRight.getHeight()/2);
    
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
        drawBirdTop(bird.x, bird.y, angleToRotate + 0.10);
        
        //finImg.draw(finAnchor.x, finAnchor.y);
        boxedImg.draw(boxedAnchor.x, boxedAnchor.y);
        inImg.draw(inAnchor.x, inAnchor.y);
//        ofPushMatrix();
//            ofTranslate(boxedAnchor);
//            svgBoxed.draw();
//        ofPopMatrix();
//         ofPushMatrix();
//             ofTranslate(inAnchor);
//             svgIn.draw();
//         ofPopMatrix();
    }
    if (scene == 2) {
        if (sequence == 1) {
            drawBirdTop(bird.x, bird.y, angleToRotate + 0.10);
        }
    }
    if (scene == 6) {
        if (sequence == 9) {
            finImg.draw(finAnchor.x, finAnchor.y);
            inImg.draw(inAnchor.x, inAnchor.y);
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
        drawMan(man.x, man.y);
        
        svgFront.draw();
        
        if (sequence > 1 && sequence <= 5 ) { // 1,2,3,4,5
            drawBirdSide(bird.x, bird.y, true);
        }
        else if (sequence >= 6 && sequence <= 7 ) {
            drawBirdSide(bird.x, bird.y, false);
        }
        else if (sequence == 8) {
            drawBirdSide(bird.x, bird.y, true);
        }
    }
    if (scene == 3) {
        drawMan(man.x, man.y);
        
        svgFront.draw();
        
        drawBirdSide(bird.x, bird.y, false);
    }
    if (scene == 4) {
        drawMan(man.x, man.y);
        
        svgFront.draw();
        
        drawBirdSide(bird.x, bird.y, true);
    }
    if (scene == 5) {
        if (sequence < 3) {
            drawMan(man.x, man.y);
        }
        svgFront.draw();
        
        if (sequence <= 2) {
           drawBirdSide(bird.x, bird.y, true);
       }
       
    }
    if (scene == 6) {
        if (sequence > 2) {
            drawMan(man.x, man.y);
        }
        
        svgFront.draw();
        
        if (sequence > 1 && sequence <=7 ) {
            drawBirdSide(bird.x, bird.y, false);
        }
        if (sequence >= 8) {
            drawBirdSide(bird.x, bird.y, true);
        }
    }
    fboFront.end();
}
void ofApp::updateSideFbo() {
    
   fboSide.begin();
       //similar to Processing clear canvas each draw
       ofClear(255,255,255, 0);
       if (scene == 1) {
           svgSide.draw();
       }
       if (scene == 2) {
           svgSide.draw();
       }
       if (scene == 3) {
           svgSide.draw();
       }
       if (scene == 4) {
           svgSide.draw();
       }
       if (scene == 5) {
           if (sequence > 2) {
               drawMan(man.x, man.y);
           }
           svgSide.draw();
           
           if (sequence > 2 && sequence <= 5) {
               drawBirdSide(bird.x, bird.y, true);
           }
           if (sequence == 6) {
               drawBirdSide(bird.x, bird.y, false);
           }
       }
       if (scene == 6) {
           if (sequence < 3) {
               drawMan(man.x, man.y);
           }
           svgSide.draw();
           
           if (sequence == 1) {
               drawBirdSide(bird.x, bird.y, false);
           }
       }
   fboSide.end();
}

//updates the counter for drawing polylines incrementally
void ofApp::updateStepPolyline() {
    
}
//in draw(), draws the polyline incrementally
void  ofApp::drawPolyline(vector<ofPolyline> outlines) {
    
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
        bTopImg.draw(0,0);
        ofPushStyle();
              ofEnableAlphaBlending();
              ofDisableDepthTest();
              ofSetColor(255, 255, 255, 255);
              bTopImg.draw(0,0);
        ofPopStyle();
    ofPopMatrix();
    
}
void ofApp::drawBirdSide(int x, int y, bool faceLeft) {
   
    ofPushMatrix();
        ofTranslate(x, y);
        ofPushStyle();
            ofEnableAlphaBlending();
            ofDisableDepthTest();
            ofSetColor(255, 255, 255, 255);
            if (!faceLeft) {
               bImgFaceRight.draw(0,0);
            } else {
                bImgFaceLeft.draw(0,0);
            }
        ofPopStyle();
        
    ofPopMatrix();
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
