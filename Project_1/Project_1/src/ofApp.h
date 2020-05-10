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
    void drawPolyline(vector<ofPolyline> outlines, float pct);
    void drawBirdTop(int x, int y, float angle);
    void drawBirdWingsTop(int x, int y);
    void drawBirdSide(int x, int y, bool faceLeft);
    void drawBirdWingsSide(int x, int y, bool faceLeft);
    void drawMan(int x, int y);
    void drawFace(int x, int y);
    
    float getAngle(ofPoint point1, ofPoint point2);
    
    //Warp variables
    bool                useBeginEnd;
    ofxWarpController   warpController;
    ofTexture           texture;
    vector<ofRectangle> srcAreas;
    int                 areaMode;
    std::string         areaName;
    ofImage             testImage;
    
    //Draw variables
    ofFbo               fboTop, fboFront, fboSide;
    ofPixels            pixelTop, pixelFront, pixelSide;
    ofImage             imgFront, imgSide, imgTop,
                        bTopImg1, bTopImg2, //wing vs no wing
                        bTopWing1, bTopWing2, bTopWing3,
                        bSideWingLeft1, bSideWingLeft2,
                        bSideWingRight1, bSideWingRight2,
                        bLeft1, bLeft2, bRight1, bRight2, cImg,
                        boxedImg, inImg, finImg,
                        angryImg, singImg, curiousImg,
                        faces[6], hands[3];
    
    //SVGs
    ofxSVG              svgFront, svgSide, svgSideBack, svgTop,
                        svgCBody, svgBBody, svgBBodyTop,
                        svgBoxed, svgIn, svgFin;
    //SVG offsets
    ofPoint             cBody, bBody, bBodyTop;
    
    //Scene management
    int                 scene, sequence;
    float               pct;
    float               speed;
    int                 startTime;
    int                 endTime;
    
    
    vector<ofPolyline>  outlines;
    float               step;
    
    //Anchors
    ofPoint             boxedAnchor, inAnchor, finAnchor, //text
                        cBodyAnchor, cFaceAnchor,         //man
                        cLHAnchor,cRHAnchor,
                        bBodyAnchor, bBodyTopAnchor, bSpeechAnchor;      //bird
    
    ofVec2f             birdPos, manPos;
    
    ofPoint             scene1[4],
                        scene2b[6], scene2c[2],
                        scene3b[5], scene3c[3],
                        scene4b[5], scene4c[4],
                        scene5b[5], scene5c[6],
                        scene6b[6], scene6c[7];
    
    //polylines for animation
    ofPolyline          sPoly1[3],
                        sPoly2b[4], sPoly2c[1],
                        sPoly3b[2], sPoly3c[2],
                        sPoly4b[2], sPoly4c[3],
                        sPoly5b[3], sPoly5c[4],
                        sPoly6b[5], sPoly6c[5];
    
    float currPathAngle, prevPathAngle, angleToRotate;
    
    //Box dimensions
    int                 boxL, boxW, boxH;
    int                 topW, topH, frontW, frontH, sideW, sideH;
    
    //testing
    int                 x;
    float               fade;

    //bird variables
    bool                isFlapping;
    
    //face variables --> just replace with 2 pngs and swap out
    ofRectangle         face;
    ofRectangle         faceOutline;
    int                 faceWidth = 170;
    int                 faceHeight = 110;

    int                 strokeThickness = 15;

    int                 eyeDistanceX = 45;
    int                 eyeDistanceY = 2;
    int                 eyeSize = 12;

    int                 eyebrowDistanceX = 33;
    int                 eyebrowDistanceY = 32;
    int                 eyebrowWidth = 30;
    int                 eyebrowHeight = 13;

    int                 noseWidth = 28;
    int                 noseHeight = 20;

    int                 mouthWidth = 26;

        
};

