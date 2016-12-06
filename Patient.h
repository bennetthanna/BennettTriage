#pragma once
#include "ofMain.h"

class Patient {
    public:
        int x;
        int y;
        float radius;
        int initialLifeLeft;

        int severity;
        int treatementTimeNeeded;
        int treatementTimeReceived;
        int lifeLeft;
    
        ofColor color;
    
        Patient();
    
        bool operator < (const Patient right) const;

        void draw(int x, int y);
        void update();
};
