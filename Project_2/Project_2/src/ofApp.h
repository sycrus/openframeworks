#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxOpenCv.h"
#include "ofxGui.h"
#include "ofxBox2d.h"
#include "ofxSvg.h"
#include "ofxKinect.h"
#include "ofxWarp.h"

#define N_SOUNDS 5

class SoundData {
public:
    int  soundID;
    bool bHit;
};

class Target {
public:
    ofPoint position;
    int rotation;
};


class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    void exit();
    void mousePressed(int x, int y, int button);
    void mouseDragged(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void keyPressed(int key);
    void keyReleased(int key);
    
    void initializeImgs();
    void initializeSvgs();
    void initializeKinect();
    void initializeCV();
    void initializeFlippers();
    
    void updateKinect();
    void getMarkerLocations();
    
    void drawBumpers();
    void drawTargets();
    void drawFlippers();
    void drawContourAreas();
    
    ofPolyline svgToPolyline(ofxSVG svg);
    void polylineToWheels(ofPolyline polyline, ofPoint position);
    void polylineToSeesaws(ofPolyline polyline, ofPoint position);
    void polylineToEnd(ofPolyline polyline, ofPoint position);
    
    void createEdgesContourFinder();
    void createBackground();
    void createBumper(ofPoint position);
    void createTarget(ofPoint position, int rotation);
    void createWheel(ofPoint position);
    void createAxis(ofPoint position);
    
    void setupArduino(const int & version);
    void digitalPinChanged(const int & pinNum);
    void updateArduino();
    
    void contactStart(ofxBox2dContactArgs &e);
    void contactEnd(ofxBox2dContactArgs &e);
    
    ofArduino               ard;
    bool                    bSetupArduino;
    
    ofxKinect               kinect;
    ofxCvGrayscaleImage     grayImage; // grayscale depth image
    ofxCvGrayscaleImage     grayThresh; // the thresholded image
    ofxCv::ContourFinder    contourFinder;
    bool                    bThreshWithOpenCV;
    bool                    bDrawPointCloud;
    int                     minBlobSize;
    int                     maxBlobSize;
    int                     minAreaRadius;
    int                     maxAreaRadius;
    int                     angle; //kinect angle
    int                     blobArea[10];
    bool                    showContours = false;
    bool                    showShapes = true;
    
    ofImage                             ballImg, bumperImg, leftSImg, rightSImg, backgroundImg,
                                        leftSCImg, rightSCImg,
                                        face1, face2, face3, face4,
                                        leftSFace1, rightSFace1,
                                        targetImg, target1, target2, wheel1;
    
    ofxSVG                              backgroundSvg, leftSCSvg, rightSCSvg, leftSSvg, rightSSvg,
                                        wheelSvg;
    
    int                                 wheelWidth, wheelHeight;
    ofPolyline                          wheelPolyline;
    
    ofxBox2d                            box2d; //world
    ofxBox2dCircle                      leftAnchor, rightAnchor;
    ofxBox2dRect                        leftFlipper, rightFlipper, plunger;
    ofxBox2dRevoluteJoint               leftFlipperJoint, rightFlipperJoint;
    
    ofVec2f                             leftFlipperPos, rightFlipperPos, plungerPos;
    ofVec2f                             leftAnchorPos, rightAnchorPos;
    ofVec3f                             leftSlingshotPos, rightSlingshotPos, backgroundPos, leftSCPos, rightSCPos;
    
    vector<ofPolyline>                          outlines, outlinesLeftSlingshot, outlinesRightSlingshot,
                                                outlinesLeftSC, outlinesRightSC ;
    vector <ofPoint>                            wheels, bumpers; //locations of components
    vector <Target>                             targets;
    vector <shared_ptr<ofxBox2dRect>>           targetsRect;
    vector <shared_ptr<ofxBox2dCircle>>         circles, axles, startAxles, ssPins, bumpersCircle; //for balls, axles
    vector <shared_ptr<ofxBox2dPolygon>>        obstaclesWheels; //for polyline polygons
    vector <shared_ptr<ofxBox2dEdge>>           edges, backgroundEdges; //for detected contours
    vector <shared_ptr<ofxBox2dRevoluteJoint>>  axes;
    
    // when the ball hits we play this sound
    ofSoundPlayer           sound[N_SOUNDS];
    
    ofTrueTypeFont          interstateFont;
    int                     score;
    
    ofxPanel                gui;
    ofParameter<float>      threshold;
    ofParameter<bool>       trackHs;
    ofParameter<bool>       holes;
    ofxLabel                fps;
        
};



  

