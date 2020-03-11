#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

    public:
        void setup();
        void update();
        void draw();
    
        void initializePerson();
        void initializeWorld();
        void initializeFace();
    
        void drawText(ofVec2f position);
        void drawWorld(ofVec2f position);
    
        void drawFace(ofVec2f position);
        void drawEyebrows(ofVec2f position, int angle);
    
        void drawHappyParts(ofVec2f position, int intensity);
        void drawSadParts(ofVec2f position, int intensity);
        void drawAngryParts(ofVec2f position, int intensity);
        void drawSurprisedParts(ofVec2f position, int intensity);
    

        void drawTorso(ofVec2f position);
        void drawLegs(ofVec2f position);

        void drawStar(ofVec2f position, float r1, float r2, int vertices);
    
        void keyPressed(int key);
        void keyReleased(int key);
        void mouseMoved(int x, int y );
        void mouseDragged(int x, int y, int button);
        void mousePressed(int x, int y, int button);
        void mouseReleased(int x, int y, int button);
        void mouseEntered(int x, int y);
        void mouseExited(int x, int y);
        void windowResized(int w, int h);
        void dragEvent(ofDragInfo dragInfo);
        void gotMessage(ofMessage msg);
        
        //gui
        void volumeFloatSliderChanged(float & volumeFloatSlider) ;
        void changeExpressionButtonPressed();
        
        //face variables
        ofColor faceColor;
        ofColor faceOutlineColor;
    
        ofRectangle face;
        ofRectangle faceOutline;
        
        //position vectors of face, offset relative to HEAD ANCHOR
        ofVec2f headAnchor,
                    facePosition, //head anchor
                    leftEyebrowOffset, rightEyebrowOffset,
                    leftEyeOffset, rightEyeOffset,
                    topNoseOffset, leftNoseOffset, rightNoseOffset,
                    sadMouthOffset,happyMouthOffset, angryMouthOffset,surprisedMouthOffset,
                    neckPosition,
        //position vectors of body, offset relative to TORSO ANCHOR
                torsoAnchor,
                    topTorsoOffset, leftTorsoOffset, rightTorsoOffset,
                    leftHandOffset, rightHandOffset,
                    bodyPosition,
        //position vectors of legs, offset relative to HIP ANCHOR
                hipAnchor, hipOffset,
                    leftFootOffset, rightFootOffset,
                    leftFrontFootOffset, rightFrontFootOffset,
                    
                worldPosition;

    
        //face variables
        int strokeThickness = 15;
        int faceWidth = 170;
        int faceHeight = 110;
    
        int eyeDistanceX = 45;
        int eyeDistanceY = 2;
        int eyeSize = 12;

        int eyebrowDistanceX = 33;
        int eyebrowDistanceY = 20;
        int eyebrowWidth = 30;
        int eyebrowHeight = 13;
        int eyebrowRotateAngle = 0;

        int noseWidth = 28;
        int noseHeight = 20;

        int mouthWidth = 26;

        //body variables
        int torsoWidth = 112;
        int torsoHeight = 80;
    
        //hand variables
        int handRadius = 20;
        int handArcRadius = 90;
    
        //leg variables
        int frontFootRadius = 18;
        int footWidth = 30;
        int footArcRadius = 60;
        
        //movement variables
        float vertMoveAngle = 0; //body bobbing
        float thetaLeft = 0; //left hand
        float thetaRight = 0; //right hand
        float leftDirection = 1; //left hand direction
        float rightDirection = -1; //right hand direction
        int handSpeed = 10;
        int bobOffset = 10;
        float worldAngle = 0;
        
        //control variables
        ofPoint myMouse;
        ofVec2f currVec;
        ofVec2f targetVec;
        bool moveRight = false;
        bool moveLeft = false;
        int emotionCounter = 0;

        ofSoundPlayer bgm;
        float bgmVolume = 0.2f;
    
        ofxPanel gui;

        ofxFloatSlider volumeFloatSlider;
        ofxButton changeExpressionButton;
        ofxVec2Slider sunVecSlider;
        ofxColorSlider backgroundColorSlider;
        ofxIntSlider emotionalIntSlider;
    
        ofxLabel screenSize;
        

    
};
