#include "Subsystems/intake.h"

Intake::Intake(){
    previousStateIn = false;
    previousStateOut = false;
    currentStateIn = false;
    currentStateOut = false;
    intakeIn = false;
    intakeOut = false;
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

    if(intakeIn){
        intakeMotor.moveVelocity(600);
    }
    else if(intakeOut){
        intakeMotor.moveVelocity(-600);
    }
    else{
        intakeMotor.moveVelocity(0);
    }
}