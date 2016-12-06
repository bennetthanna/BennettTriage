#include <stdio.h>
#include "ofMain.h"
#include "Patient.h"

Patient::Patient() {
    x = 0;
    y = 0;
    radius = 50.0;
    color = ofColor(ofRandom(255), ofRandom(255), ofRandom(255));
    severity = ofRandom(1, 100);
    if (severity > 50) {
        treatementTimeNeeded = ofRandom(1000, 15000);
        lifeLeft = ofRandom(500, 10000);
    } else {
        treatementTimeNeeded = ofRandom(100, 7000);
        lifeLeft = ofRandom(1000, 20000);
    }
    treatementTimeReceived = 0;
    initialLifeLeft = lifeLeft;
}

bool Patient::operator < (const Patient right) const {
    return this->severity < right.severity;
}

void Patient::draw(int x, int y) {
    ofSetColor(color);
    ofDrawCircle(x, y, radius);
    ofSetColor(0);
    ofDrawBitmapString("S: " + std::to_string(severity), x - 35, y - 10);
    ofDrawBitmapString("TN: " + std::to_string(treatementTimeNeeded), x - 35, y);
    ofDrawBitmapString("TR: " + std::to_string(treatementTimeReceived), x - 35, y + 10);
    ofDrawBitmapString("LL: " + std::to_string(lifeLeft), x - 35, y + 20);
}

void Patient::update() {
    if (lifeLeft > 0) {
        --lifeLeft;
        radius = ((float(lifeLeft) / float(initialLifeLeft)) * (50.0));
    }
}
