//source: ofxFluid and ofxFx by patriciogonzalezvivo https://github.com/patriciogonzalezvivo/ofxFluid

#pragma once

#include "ofMain.h"
#include "ofxFluid.h"
#include "ofxCv.h"
#include "ofxKinect.h"
#include "ofxKinectProjectorToolkit.h"
#include "ofxSecondWindow.h"
//#include "ofxOpenNI.h"


using namespace ofxCv;
using namespace cv;

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void exit();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    ofxFluid fluid;
    
    ofxKinect kinect;
    ofxCv::ContourFinder contourFinder;
    
    ofxKinectProjectorToolkit kpt;
    
    ofxSecondWindow projector;
    
    
//    ofxKinect                   kinect;
//    
//    ofxCvGrayscaleImage         bgImage;
//    ofxCvGrayscaleImage         grayImage;
//    ofxCvGrayscaleImage         grayThreshNear;
//    ofxCvGrayscaleImage         grayThreshFar;
//
    
    
    ofParameter<float>          nearThreshold;
    ofParameter<float>          farThreshold;
    ofParameter<float>          minArea;
    ofParameter<float>          maxArea;
    ofParameter<float>          threshold;
    ofParameter<float>          persistence;
    ofParameter<float>          maxDistance;
       vector<vector<cv::Point> > prevPoints;
    
    int skip;
    float magnitude;
};
