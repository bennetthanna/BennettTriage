#include "ofApp.h"
#include "Patient.h"
#include "Doctor.h"
#include <queue>
#include <vector>
#include <algorithm>

Doctor dan;
Doctor don;
Doctor dee;

std::priority_queue<Patient> WaitingList;
std::vector<Patient> patients;
std::vector<Doctor> doctors;

int numDead = 0;
int numHealed = 0;

Patient danTopPatient;
Patient donTopPatient;
Patient deeTopPatient;
Patient danFirstPatient;
Patient donFirstPatient;
Patient deeFirstPatient;

void ofApp::setup(){
    ofBackground(255);
    dan = Doctor(ofGetWidth() - 200, 100, "Dan");
    don = Doctor(ofGetWidth() - 500, 100, "Don");
    dee = Doctor(ofGetWidth() - 800, 100, "Dee");
    doctors.push_back(dan);
    doctors.push_back(don);
    doctors.push_back(dee);
}

void ofApp::update(){
    if (ofGetFrameNum() % 300 == 0) {
        float probability = ofRandom(1.0);
        if (probability < 0.5) {
            patientEntersER();
        }
    }
    
    dan.treatPatient();
    don.treatPatient();
    dee.treatPatient();

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

    if (!don.isIdle()) {
        don.currentPatient->update();
        if (don.currentPatient->lifeLeft == 0) {
            numDead += 1;
            don.currentPatient = NULL;
        }
    }
    
    if(!don.isIdle()) {
        if (don.currentPatient->treatementTimeNeeded == 0) {
            numHealed += 1;
            don.currentPatient = NULL;
        }
    }
    
    if (!dee.isIdle()) {
        dee.currentPatient->update();
        if (dee.currentPatient->lifeLeft == 0) {
            numDead += 1;
            dee.currentPatient = NULL;
        }
    }
    
    if(!dee.isIdle()) {
        if (dee.currentPatient->treatementTimeNeeded == 0) {
            numHealed += 1;
            dee.currentPatient = NULL;
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
    don.draw();
    dee.draw();
    
    int waitingRoomX = ofGetWidth() - 100;
    int waitingRoomY = ofGetHeight() - 100;
    
    for (int i = 0; i < patients.size(); ++i) {
        if (patients[i].lifeLeft != 0) {
            patients[i].draw(waitingRoomX, waitingRoomY);
            waitingRoomX -= 100;
        }
    }
    
    if (dan.isIdle()) {
        ofDrawBitmapString("AVAILABLE", dan.x, dan.y);
    } else {
        dan.currentPatient->draw(dan.x + 50, dan.y + 100);
    }
    
    if (don.isIdle()) {
        ofDrawBitmapString("AVAILABLE", don.x, don.y);
    } else {
        don.currentPatient->draw(don.x + 50, don.y + 100);
    }
    
    if (dee.isIdle()) {
        ofDrawBitmapString("AVAILABLE", dee.x, dee.y);
    } else {
        dee.currentPatient->draw(dee.x + 50, dee.y + 100);
    }
}

void ofApp::patientEntersER() {
    Patient *newPatient = new Patient();
    WaitingList.push(*newPatient);
}

void ofApp::triage() {
    if (!WaitingList.empty()) {
        if (dan.isIdle()) {
            danTopPatient = WaitingList.top();
            dan.attendTo(&danTopPatient);
            WaitingList.pop();
        }
    }
    
    if (!WaitingList.empty()) {
        if (don.isIdle()) {
            donTopPatient = WaitingList.top();
            don.attendTo(&donTopPatient);
            WaitingList.pop();
        }
    }
    
    if (!WaitingList.empty()) {
        if (dee.isIdle()) {
            deeTopPatient = WaitingList.top();
            dee.attendTo(&deeTopPatient);
            WaitingList.pop();
        }
    }
    
    if (!WaitingList.empty()) {
        if (!dan.isIdle()) {
            Patient p1 = WaitingList.top();
            if (*dan.currentPatient < p1) {
                WaitingList.push(*dan.currentPatient);
                danFirstPatient = p1;
                dan.attendTo(&danFirstPatient);
                WaitingList.pop();
            }
        }
    }
    
    if (!WaitingList.empty()) {
        if (!don.isIdle()) {
            Patient p2 = WaitingList.top();
            if (*don.currentPatient < p2) {
                WaitingList.push(*don.currentPatient);
                donFirstPatient = p2;
                don.attendTo(&donFirstPatient);
                WaitingList.pop();
            }
        }
    }
    
    if (!WaitingList.empty()) {
        if (!dee.isIdle()) {
            Patient p3 = WaitingList.top();
            if (*dee.currentPatient < p3) {
                WaitingList.push(*dee.currentPatient);
                deeFirstPatient = p3;
                dee.attendTo(&deeFirstPatient);
                WaitingList.pop();
            }
        }
    }
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
//    if (key == ' ') patientEntersER();
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
