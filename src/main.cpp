#include "main.h"

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	drivebase.init();
	intake.stop();
	intake.in();
	drivebase.moveDistance({12_in});
	pros::delay(300);
	drivebase.moveDistance({38_in});
	drivebase.turnAngle(-95_deg);
	drivebase.driveForward(-50);
	intake.stop();
	pros::delay(750);
	drivebase.moveDistance({46_in});
	
	intake.in();
	drivebase.turnAngle(100_deg);
	intake.out();

	drivebase.moveDistance(3_in);
	intake.out();
	drivebase.driveForward(200);
	pros::delay(400);
	intake.stop();

	drivebase.moveDistance({-17_in});
	drivebase.turnAngle({-95_deg});
	intake.in();
	drivebase.moveDistance({12_in});
	pros::delay(100);
	drivebase.moveDistance({-11_in});
	drivebase.turnAngle(95_deg);
	drivebase.moveDistance({12_in});
	intake.out();
	drivebase.driveForward(250);
	pros::delay(400);
	

	drivebase.moveDistance({-12_in});
	drivebase.turnAngle({-195_deg});
	intake.in();
	drivebase.moveDistance({18_in});
	intake.stop();
	drivebase.moveDistance({-18_in});
	drivebase.turnAngle({197_deg});
	drivebase.moveDistance({10_in});
	intake.out();
	drivebase.driveForward(250);
	pros::delay(400);
	intake.stop();
	drivebase.driveForward(0);
	drivebase.turnAngle({143_deg});
	drivebase.moveDistance({45_in});

	
	
	


}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	drivebase.init();
	Controller controller;


	while (true) {
		drivebase.xDrive(controller);
		intake.toggleIntake(controller);
	}
}