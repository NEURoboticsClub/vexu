#ifndef SUBSYSTEMS_INTAKE_H
#define SUBSYSTEMS_INTAKE_H

#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS

#include "api.h"
#include "okapi/api.hpp"

using namespace okapi;

class Intake
{
    public:
        Intake();
        void toggleIntake(Controller& controller);
        void in();
        void out();
        void stop();
        void spinIntake();
    private:
        Motor intakeMotor = Motor(13, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::rotations);;
        bool previousStateIn;
        bool currentStateIn;
        bool previousStateOut;
        bool currentStateOut;
        bool intakeIn;
        bool intakeOut;
};

#endif
