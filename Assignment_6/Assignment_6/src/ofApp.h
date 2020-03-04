#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    
        void initializePerson();
        void initializeWorld();
    
        void drawText(ofVec3f position);
        void drawWorld(ofVec3f position);
        void drawFace(ofVec3f position);
        void drawTorso(ofVec3f position);
        void drawLegs(ofVec3f position);

        void drawStar(ofVec3f position, float r1, float r2, int vertices);
    
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
		
        

        //face variables
        ofColor faceColor;
        ofColor faceOutlineColor;
    
        ofRectangle face;
        ofRectangle faceOutline;
        
        //position vectors of face, offset relative to HEAD ANCHOR
        ofVec3f headAnchor,
                    facePosition, //head anchor
                    leftEyebrowOffset, rightEyebrowOffset,
                    leftEyeOffset, rightEyeOffset,
                    topNoseOffset, leftNoseOffset, rightNoseOffset,
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
        ofVec3f currVec;
        ofVec3f targetVec;
        bool moveRight = false;
        bool moveLeft = false;
        bool useFbo = false;

        ofTrueTypeFont futura;

        ofFbo fbo;
};
