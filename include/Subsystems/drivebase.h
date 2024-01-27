#ifndef SUBSYSTEMS_DRIVEBASE_H
#define SUBSYSTEMS_DRIVEBASE_H

#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS

#include "api.h"
#include "okapi/api.hpp"

using namespace okapi;

class Drivebase
{
    public:
        Drivebase();
        void xDrive(double irightSpeed, double iforwardSpeed, double iyaw, double ithreshold = 0);
    private:
        std::shared_ptr<OdomChassisController> chassis;

};

Drivebase drivebase;


#endif