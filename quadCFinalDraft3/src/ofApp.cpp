//source: ofxFluid and ofxFx by patriciogonzalezvivo https://github.com/patriciogonzalezvivo/ofxFluid

#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFullscreen(true);
    kinect.setRegistration(true);
    kinect.init();
    kinect.open();
    
     kpt.loadCalibration("/Users/kristinslater/Desktop/of_v0.8.4_osx_release/addons/ofxKinectProjectorToolkit/calibration/bin/data/calibration.xml");
    
    fluid.allocate(640, 480, 0.5);
    
    fluid.dissipation = 0.99;
    fluid.velocityDissipation = 0.99;
    
    fluid.setGravity(ofVec2f(0.0,0.0));
    
    //    fluid.setGravity(ofVec2f(0.0,0.0098));
    fluid.begin();
    ofSetColor(0,0);
    ofSetColor(255);
    ofCircle(640*0.5, 480*0.45, 100);
    fluid.end();
    fluid.setUseObstacles(false);
    
    
    // Adding constant forces
    //
    fluid.addConstantForce(ofPoint(640*0.5,480*0.85), ofPoint(0,-2), ofFloatColor(0.1,0.1,0.1), 5.0);
    //10.f if you want to explicitly say that a number is a float
}

void ofApp::exit(){
    kinect.close();
}
//--------------------------------------------------------------
void ofApp::update(){
    
    kinect.update();
    
    if (kinect.isFrameNew()) {
        contourFinder.setThreshold(ofMap(mouseX, 0, ofGetWidth(), 0, 255));
        contourFinder.findContours(kinect.getDepthPixelsRef());
    }
    skip = 20;
    magnitude = 5;
    
    vector<vector<cv::Point> > newPrevPoints;
    
    int numContours = contourFinder.size();
    for (int i=0; i<numContours; i++) {
        vector<cv::Point> points = contourFinder.getContour(i);
        newPrevPoints.push_back(points);
        
        for (int j=0; j<points.size(); j+=skip)
        {
            if (i < prevPoints.size() && j < prevPoints[i].size()) {
                ofPoint m = ofPoint(points[j].x, points[j].y);
                ofPoint d = ofPoint(points[j].x - prevPoints[i][j].x, points[j].y - prevPoints[i][j].y) * magnitude;
                ofFloatColor color = ofFloatColor(10,10,10) * sin(0.1*ofGetFrameNum());
                fluid.addTemporalForce(m, d, color, 2.0f);
            }
        }
    }
    
    prevPoints = newPrevPoints;
    
    
    fluid.update();
}

//
//    // m is the position of the mouse
//    //d is the vector of the mouse's direction
//    // color is the initial color of the force
//    //a temporal forc acting on the flame instantaneously
//
//    // Adding temporal Force
//    //
//    ofPoint m = ofPoint(ofGetMouseX(),ofGetMouseY()); //position of mouse
//    ofPoint d = ofPoint(ofGetMouseX() -ofGetPreviousMouseX(), ofGetMouseY() - ofGetPreviousMouseY()) * 10.0; //direction of mouse
//    ofFloatColor color = ofFloatColor(1.0, 1.0, 1.0)*sin(ofGetElapsedTimef()); //color
//    fluid.addTemporalForce(m,d, color, 3.0f); //magnitude
//
//
//    //temporal force is an instantaneous force that lasts for one frame on each instance of update (works well for the position of a thing, such as a mouse position). a constant force will remain until you make a change.
//



//--------------------------------------------------------------
void ofApp::draw(){
    ofScale(ofGetWidth() / 640.0, ofGetHeight() / 480.0);
    
    fluid.draw();
    
    ofSetColor(200,200,200);
    ofNoFill();
    ofSetLineWidth(.25);
    
    int numContours = contourFinder.size();
    for (int i=0; i<numContours; i++) {
        vector<cv::Point> points = contourFinder.getContour(i/2);
        ofBeginShape();
        for (int j=0; j<points.size(); j++) {
            ofVertex(points[j].x, points[j].y);
        }
        ofEndShape();
    }
    
    ofSetColor(0);
    
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
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
