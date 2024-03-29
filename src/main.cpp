/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here
controller Controller;
brain Brain;
motor driveMotorFL(PORT1, gearSetting::ratio18_1, false);
motor driveMotorFR(PORT10, gearSetting::ratio18_1, true);
motor driveMotorBL(PORT11, gearSetting::ratio18_1, false);
motor driveMotorBR(PORT20, gearSetting::ratio18_1, true);
motor intakeMotorL(PORT2, gearSetting::ratio18_1, false); // TODO real port
motor intakeMotorR(PORT3, gearSetting::ratio18_1, true); // TODO real port

const int intakeSpeed = 100;


/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    double thrust = Controller.Axis3.position();
    double rotate = Controller.Axis1.position();
    driveMotorFL.spin(directionType::fwd, thrust + rotate, velocityUnits::pct);
    driveMotorFR.spin(directionType::fwd, thrust - rotate, velocityUnits::pct);
    driveMotorBL.spin(directionType::fwd, thrust + rotate, velocityUnits::pct);
    driveMotorBR.spin(directionType::fwd, thrust - rotate, velocityUnits::pct);

    int intake_speed = (Controller.ButtonR1.pressing()) ? 0 : intakeSpeed;
    intakeMotorL.spin(directionType::fwd, intake_speed, velocityUnits::pct);
    intakeMotorR.spin(directionType::fwd, intake_speed, velocityUnits::pct);

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
