#pragma once

#include "ofMain.h"
#include "ofxWarp.h"
#include "ofxSvg.h"

class ofApp : public ofBaseApp{

    public:
        void setup();
        void update();
        void draw();
        void exit();

        void keyPressed(int key);
    
    void initializeAnchors();
    void initializeFbos();
    void initializeWarps();
    void initializeSvgs();
    void initializePngs();
    void initializeAnimationPolylines();
    
    //all draws go here!
    void updateTopFbo();
    void updateFrontFbo();
    void updateSideFbo();
    
    void svgToPolyline(ofxSVG svg);
    void updateStepPolyline();
    void drawPolyline(vector<ofPolyline> outlines);
    void drawFace(int x, int y);
    
    //Draw variables
    ofFbo fboTop, fboFront, fboSide;
    ofPixels pixelTop, pixelFront, pixelSide;
    ofImage imgFront, imgSide, imgTop;  //for loading
    
    //SVGs
    ofxSVG svgFront, svgSide, svgTop,
            svgCBody, svgBBody, svgBBodyTop,
            svgBoxed, svgIn;
    
    //Warp variables
    bool useBeginEnd;
    ofxWarpController warpController;
    ofTexture texture;
    vector<ofRectangle> srcAreas;
    int areaMode;
    std::string areaName;
    ofImage testImage;
    
    vector<ofPolyline> outlines;
    float step;
    
    //Scene management
    int scene = 1;
    
    //Anchors
    ofPoint boxedAnchor, inAnchor,
            cBodyAnchor, cFaceAnchor,
            cLHAnchor,cRHAnchor,
            bBodyAnchor, bBodyTopAnchor;
    
    ofPoint scene1[4],
            scene2b[6], scene2c[2],
            scene3b[5], scene3c[3],
            scene4b[5], scene4c[4],
            scene5b[5], scene5c[6],
            scene6b[6], scene6c[7];
    
    //polylines for animation
    ofPolyline sPoly1[3],
                sPoly2b[4], sPoly2c[1],
                sPoly3b[2], sPoly3c[2],
                sPoly4b[2], sPoly4c[3],
                sPoly5b[3], sPoly5c[4],
                sPoly6b[5], sPoly6c[5];
    
    //Box dimensions
    int boxL, boxW, boxH;
    int topW, topH, frontW, frontH, sideW, sideH;
    
    //testing
    int x;
    
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

        
};

