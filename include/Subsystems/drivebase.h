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
        void init();
        void generatePath(std::initializer_list<okapi::PathfinderPoint> wayPoints, std::string pathID);
        void setTarget(std::string pathID);
        void removePath(std::string pathID);
        void waitUntilSettled();
        void driveToPoint(okapi::Point point);
        void turnToAngle(okapi::QAngle angle);
        void turnAngle(okapi::QAngle angle);
        void moveDistance(okapi::QLength distance);
        std::shared_ptr<OdomChassisController> chassisGeneric;
    private:
        std::shared_ptr<XDriveModel> chassisXDrive;
        std::shared_ptr<AsyncMotionProfileController> profileController;

};

#endif