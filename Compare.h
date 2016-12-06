#pragma once
#include "Patient.h"

struct CompareBySeverity {

    Boolean operator()(const Patient& p1, const Patient& p2) {
        return p1.severity < right.severity;
    }
};
