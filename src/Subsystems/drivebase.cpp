#include "Subsystems/drivebase.h"

Drivebase::Drivebase(){
    motorsFrontLeft.setBrakeMode(AbstractMotor::brakeMode::brake);
    motorsFrontRight.setBrakeMode(AbstractMotor::brakeMode::brake);
    motorsBackRight.setBrakeMode(AbstractMotor::brakeMode::brake);
    motorsBackLeft.setBrakeMode(AbstractMotor::brakeMode::brake);

    chassisGeneric = 
        ChassisControllerBuilder()
            .withMotors(motorsFrontLeft, motorsFrontRight, motorsBackRight, motorsBackLeft)
            .withSensors(
                leftSensor,
                rightSensor,
                middleSensor
                )
            .withGains(
				{0.0015, 0.000175, 0.0001}, // NOBODY TOUCHES THE PID VALUES
				{0.003, 0.0001, 0.0001}, // NOBODY TOUCHES THE PID VALUES
				{0.0015, 0.0001, 0.00005}  // NOBODY TOUCHES THE PID VALUES
				)
            .withDimensions(AbstractMotor::gearset::blue, ChassisScales{{2.75_in, 10.5_in, 5.46_in, 2.75_in}, imev5BlueTPR})
            .withOdometry({{2.75_in, 10.5_in, 5.46_in, 2.75_in}, 360})
            .buildOdometry();
    
    chassisXDrive = std::dynamic_pointer_cast<XDriveModel>(chassisGeneric->getModel());

    profileController =
        okapi::AsyncMotionProfileControllerBuilder()
            .withLimits({1.0*0.5, 2.0*0.5, 10.0*0.5})
            .withOutput(chassisGeneric)
            .buildMotionProfileController();
    
}

void Drivebase::xDrive(Controller& controller){
    chassisXDrive->xArcade(controller.getAnalog(ControllerAnalog::leftX), controller.getAnalog(ControllerAnalog::leftY),controller.getAnalog(ControllerAnalog::rightX), 0.01);
}

void Drivebase::init() {
    chassisXDrive->setMaxVelocity(400);
    chassisGeneric->setMaxVelocity(100);
    chassisGeneric->setState({0_m, 0_m, 0_deg});
    profileController->reset();
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

void Drivebase::turnToAngle(okapi::QAngle angle){
    chassisGeneric->turnToAngle(angle);
}

void Drivebase::turnAngle(okapi::QAngle angle){
    chassisGeneric->turnAngle(angle);
}

void Drivebase::moveDistance(okapi::QLength distance){
    chassisGeneric->moveDistance(distance);
}

void Drivebase::driveForward(double speed){
    chassisXDrive->forward(speed);
}