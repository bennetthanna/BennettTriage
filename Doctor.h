#pragma once
#include <string>
#include "Patient.h"

class Doctor {
    public:
        int x;
        int y;
    
        Doctor();
        Doctor(int x, int y, std::string name);
    
        Patient* currentPatient;
    
        ofColor color;
        std::string name;
    
        void draw();
        void treatPatient();
        void attendTo(Patient *p);
        bool isIdle();
};
