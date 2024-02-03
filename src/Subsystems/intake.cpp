#include "Subsystems/intake.h"

Intake::Intake(){
    previousStateIn = false;
    previousStateOut = false;
    currentStateIn = false;
    currentStateOut = false;
    intakeIn = false;
    intakeOut = false;
    intakeMotor.setBrakeMode(AbstractMotor::brakeMode::hold);
}

void Intake::toggleIntake(Controller& controller){
    currentStateIn = controller.getDigital(ControllerDigital::R1);
    currentStateOut = controller.getDigital(ControllerDigital::L1);
    
    if(currentStateIn != previousStateIn){
        if(currentStateIn){
            intakeIn = !intakeIn;
            intakeOut = false;
        }
        previousStateIn = currentStateIn;
    }

    if(currentStateOut != previousStateOut){
        if(currentStateOut){
            intakeOut = !intakeOut;
            intakeIn = false;
        }
        previousStateOut = currentStateOut;
    }

   spinIntake();
}


void Intake::in(){
    intakeIn = true;
    intakeOut = false;
    spinIntake();
}

void Intake::out(){
    intakeIn = false;
    intakeOut = true;
    spinIntake();
}

void Intake::stop(){
    intakeIn = false;
    intakeOut = false;
    spinIntake();
}

void Intake::spinIntake(){
     if(intakeIn){
        intakeMotor.moveVelocity(300);
    }
    else if(intakeOut){
        intakeMotor.moveVelocity(-300);
    }
    else{
        intakeMotor.moveVelocity(0);
    }
}