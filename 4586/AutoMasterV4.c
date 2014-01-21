#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Sensor, S2,     gyroSensor,     sensorI2CHiTechnicGyro)
#pragma config(Sensor, S3,     IRSeeker,       sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S4,     ,               sensorHiTechnicTouchMux)
#pragma config(Motor,  mtr_S1_C1_1,     FrontLeft,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     MidLeft,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     FrontRight,    tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     MidRight,      tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_1,     BackLeft,      tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     Arm,           tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C4_1,     BackRight,     tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C4_2,     Joint,         tmotorTetrix, openLoop, encoder)

int a;
//int IR;
int armStop;
int jointStop;
int lastJoint;
int lastArm;
int currentHeight;
int nButtonsMask;

#include "JoystickDriver.c"
#include "constantsbowledover.h"
#include "menu.h"
#include "gyro.h"
#include "drivesystem.h"
#include "tasksJoint.h"
#include "tasksArm.h"
#include "AutoRoutinesWorlds.h"


void initializeRobot() {
  disableDiagnosticsDisplay();
  //Choose an auto routine.
  selectedAutoRoutine = getRouteChoice();
  eraseDisplay();
  selectedDelayTime = getDelayChoice();
  nMotorEncoder[Arm] = 0;
  nMotorEncoder[Joint] = 0;
  GyroInit(gyroSensor);
  resetEncoders();

}


task main()
{

  initializeRobot();

  eraseDisplay();
  nxtDisplayCenteredBigTextLine(2,"WAITING...");
  nxtDisplayTextLine(4,"Autonomous Mode");
  nxtDisplayTextLine(5,"Choice: %s", autoRoutines[selectedAutoRoutine]);
  nxtDisplayTextLine(6,"Delay: %i", atoi(delayTimes[selectedDelayTime]));

  waitForStart();

 // GyroInit(gyroSensor);
 // wait10Msec(100);
    nxtDisplayCenteredBigTextLine(2,"Delaying: %i sec", atoi(delayTimes[selectedDelayTime]));
  wait10Msec(atoi(delayTimes[selectedDelayTime]) * 100);

  eraseDisplay();
  nxtDisplayCenteredBigTextLine(1,"RUNNING!");
  nxtDisplayTextLine(4,"Autonomous Mode");
  nxtDisplayTextLine(5,"Choice: %s", autoRoutines[selectedAutoRoutine]);
  StartTask(Gyro);
  //START AN AUTO ROUTINE!!!!
  switch (selectedAutoRoutine + 1) {  //array index starts at 0, normalize to 1 for clarity
    case 1:
      StraightMiddleLeft();
      break;
    case 2:
      StraightMiddleRight();
      break;
    case 3:
			SideStraightRight();
     	break;
    case 4:
      IRRoutine();
      break;
     case 5:
      OpHangLeft();
      break;
     case 6:
      OpHangRight();
     break;
     case 7:
      Blocking();
     break;
     case 8:
     SideStraightLeft();
     break;
    default:
      //no autonomous routine was chosen, run a default one.
      break;
    }
}
