#include <stdio.h>
#include "ofMain.h"
#include "Doctor.h"

Doctor::Doctor() {
    x = 0;
    y = 0;
    color = ofColor(0, 255, 0);
    name = " ";
    currentPatient = NULL;
}

Doctor::Doctor(int x, int y, std::string name) {
    this->x = x;
    this->y = y;
    this->name = name;
    color = ofColor(0, 255, 0);
    currentPatient = NULL;
}

void Doctor::draw() {
    ofSetColor(color);
    ofDrawRectangle(x, y, 100, 50);
    ofSetColor(0);
    ofDrawBitmapString("Doctor: " + this->name, x, y + 25);
}

void Doctor::treatPatient() {
    if (!isIdle()) {
        currentPatient->treatementTimeReceived += 1;
        currentPatient->treatementTimeNeeded -= 1;
    }
}

void Doctor::attendTo(Patient *p) {
    currentPatient = p;
}

bool Doctor::isIdle() {
    return currentPatient == NULL;
}
