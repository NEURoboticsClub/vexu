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
        void driveForward(double speed);
        std::shared_ptr<OdomChassisController> chassisGeneric;
    private:
        MotorGroup motorsFrontLeft = {2, -3};
        MotorGroup motorsFrontRight = {4, -5};
        MotorGroup motorsBackRight = {17, -18};
        MotorGroup motorsBackLeft = {11, -12};
        RotationSensor leftSensor = RotationSensor{7, true};
        RotationSensor rightSensor = RotationSensor{8, true};
        RotationSensor middleSensor = RotationSensor{19};
        std::shared_ptr<XDriveModel> chassisXDrive;
        std::shared_ptr<AsyncMotionProfileController> profileController;

};

#endif