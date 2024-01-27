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
        void xDrive(Controller& controller);
    private:
        std::shared_ptr<OdomChassisController> chassisGeneric;
        std::shared_ptr<XDriveModel> chassisXDrive;

};

Drivebase drivebase;


#endif