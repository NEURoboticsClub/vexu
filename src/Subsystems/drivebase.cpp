#include "Subsystems/drivebase.h"

Drivebase::Drivebase(){
    MotorGroup motorsFrontLeft = {2, -3};
    MotorGroup motorsFrontRight = {4, -5};
    MotorGroup motorsBackRight = {17, -18};
    MotorGroup motorsBackLeft = {11, -12};


    chassisGeneric = 
        ChassisControllerBuilder()
            .withMotors(motorsFrontLeft, motorsFrontRight, motorsBackRight, motorsBackLeft)
            .withSensors(
                RotationSensor{7, true}, // left encoder in ADI ports A & B
				RotationSensor{8, true},  // right encoder in ADI ports C & D (reversed)
				RotationSensor{19}  // middle encoder in ADI ports E & F
                )
            .withGains(
				{0.0005, 0.0002, 0}, // Distance controller gains
				{0.0006, 0.0000, 0}, // Turn controller gains
				{0.0005, 0.0001, 0.00000}  // Angle controller gains (helps drive straight)
				)
            .withDimensions(AbstractMotor::gearset::blue, ChassisScales{{2.75_in, 10.5_in, 5.46_in, 2.75_in}, imev5BlueTPR})
            .withOdometry({{2.75_in, 10.5_in, 5.46_in, 2.75_in}, 360})
            .buildOdometry();
    
    chassisXDrive = std::dynamic_pointer_cast<XDriveModel>(chassisGeneric->getModel());

    profileController =
        okapi::AsyncMotionProfileControllerBuilder()
            .withLimits({1.0*0.1, 2.0*0.1, 10.0*0.1})
            .withOutput(chassisGeneric)
            .buildMotionProfileController();

    chassisXDrive->setMaxVelocity(400);
    chassisGeneric->setMaxVelocity(200);
    chassisGeneric->setState({0_m, 0_m, 0_deg});
    
}

void Drivebase::xDrive(Controller& controller){
    chassisXDrive->xArcade(controller.getAnalog(ControllerAnalog::leftX), controller.getAnalog(ControllerAnalog::leftY),controller.getAnalog(ControllerAnalog::rightX), 0.01);
}

void Drivebase::generatePath(std::initializer_list<okapi::PathfinderPoint> wayPoints, std::string pathID){
    profileController->generatePath(wayPoints, pathID);
}

void Drivebase::setTarget(std::string pathID){
    profileController->setTarget(pathID);
}

void Drivebase::removePath(std::string pathID){
    profileController->removePath(pathID);
}

void Drivebase::waitUntilSettled(){
    profileController->waitUntilSettled();
}

void Drivebase::driveToPoint(okapi::Point point){
    chassisGeneric->driveToPoint(point);
}

void Drivebase::turnAngle(okapi::QAngle angle){
    chassisGeneric->turnAngle(angle);
}

void Drivebase::moveDistance(okapi::QLength distance){
    chassisGeneric->moveDistance(distance);
}