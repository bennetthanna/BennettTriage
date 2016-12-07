#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    
        void triage();
        void updateQueue();
        void patientEntersER();
            
};
