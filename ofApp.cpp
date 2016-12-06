#include "ofApp.h"
#include "Patient.h"
#include "Doctor.h"
#include <queue>
#include <vector>
#include <algorithm>

Doctor dan;

std::priority_queue<Patient> WaitingList;
std::vector<Patient> patients;

int numDead = 0;
int numHealed = 0;

Patient topPatient;

void ofApp::setup(){
    ofBackground(255);
    dan = Doctor(ofGetWidth() - 200, 100, "Dan");
}

void ofApp::update(){
    //    if (ofGetFrameNum() % 300 == 0) {
    //        float probability = ofRandom(1.0);
    //        if (probability < 0.5) {
    //            patientEntersER();
    //        }
    //    }
        dan.treatPatient();
    
    
        if (!dan.isIdle()) {
            dan.currentPatient->update();
            if (dan.currentPatient->lifeLeft == 0) {
                numDead += 1;
                dan.currentPatient = NULL;
            }
        }
    
        if(!dan.isIdle()) {
            if (dan.currentPatient->treatementTimeNeeded == 0) {
                numHealed += 1;
                dan.currentPatient = NULL;
            }
        }
    
    updateQueue();
    triage();
}

void ofApp::updateQueue() {
    patients.clear();
    while (!WaitingList.empty()) {
        Patient p = WaitingList.top();
        p.update();
        if (p.lifeLeft == 0) {
            numDead += 1;
            WaitingList.pop();
        } else{
            patients.push_back(p);
            WaitingList.pop();
        }
    }
    for (int i = 0; i < patients.size(); ++i) {
        WaitingList.push(patients.at(i));
    }
}

void ofApp::draw(){
    
    ofDrawBitmapString("Number of Patients that Died: " + std::to_string(numDead), 10, 10);
    ofDrawBitmapString("Number of Patients that Were Healed: " + std::to_string(numHealed), 10, 20);
    
    dan.draw();

    int waitingRoomX = ofGetWidth() - 100;
    int waitingRoomY = ofGetHeight() - 100;
    
    for (int i = 0; i < patients.size(); ++i) {
        if (patients[i].lifeLeft != 0) {
            patients[i].draw(waitingRoomX, waitingRoomY);
            waitingRoomX -= 100;
        }
    }

    if(dan.isIdle()) {
        ofDrawBitmapString("AVAILABLE", dan.x, dan.y);
    } else {
        dan.currentPatient->draw(dan.x + 50, dan.y + 100);
    }
}

void ofApp::patientEntersER() {
    Patient *newPatient = new Patient();
    WaitingList.push(*newPatient);
}

void ofApp::triage() {
    if (!WaitingList.empty()) {
        if (dan.isIdle()) {
            topPatient = WaitingList.top();
            dan.attendTo(&topPatient);
            WaitingList.pop();
        } else {
            Patient p = WaitingList.top();
            if (*dan.currentPatient < p) {
                WaitingList.push(*dan.currentPatient);
                topPatient = p;
                dan.attendTo(&topPatient);
                WaitingList.pop();
            }
        }
    }
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == ' ') patientEntersER();
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
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
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
