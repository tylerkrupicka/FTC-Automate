#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     IRSeeker,       sensorHiTechnicIRSeeker1200)
#pragma config(Motor,  mtr_S1_C1_1,     FL,            tmotorNormal, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     ML,            tmotorNormal, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     BL,            tmotorNormal, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     FR,            tmotorNone, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     MR,            tmotorNone, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     BR,            tmotorNone, openLoop)
#pragma config(Servo,  srvo_S1_C4_1,    servo1,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//Local Variables////////////////////////////////////////////

int delay;
int IR;
string autoRoutines[] =  { "R1", "R2", "R3", "R4", "R5", "R6"};
int   selectedAutoRoutine = -1;
string delayTimes[] =  { "0","5","10","15","20"};
int   selectedDelayTime = -1;

//Includes///////////////////////////////////////////////////

#include "JoystickDriver.c"
#include "drive.h"
#include "autoHelper.h"
#include "menu.h"
#include "autoRoutines.h"

//Initialize/////////////////////////////////////////////////

void initializeRobot() {
  disableDiagnosticsDisplay();
  //Choose an auto routine.
  selectedAutoRoutine = getRouteChoice();
  eraseDisplay();
  selectedDelayTime = getDelayChoice();
	nMotorEncoder[ML] = 0;
}

//Main Task/////////////////////////////////////////////////

task main()
{
  initializeRobot();

  eraseDisplay();
  nxtDisplayCenteredBigTextLine(2,"WAITING...");
  nxtDisplayTextLine(4,"Autonomous Mode");
  nxtDisplayTextLine(5,"Choice: %s", autoRoutines[selectedAutoRoutine]);
  nxtDisplayTextLine(6,"Delay: %i", atoi(delayTimes[selectedDelayTime]));

  waitForStart();

  nxtDisplayCenteredBigTextLine(2,"Delaying: %i sec", atoi(delayTimes[selectedDelayTime]));
  wait10Msec(atoi(delayTimes[selectedDelayTime]) * 100);

  eraseDisplay();
  nxtDisplayCenteredBigTextLine(1,"RUNNING!");
  nxtDisplayTextLine(4,"Autonomous Mode");
  nxtDisplayTextLine(5,"Choice: %s", autoRoutines[selectedAutoRoutine]);

  //START AN AUTO ROUTINE!!!!
  switch (selectedAutoRoutine + 1) {  //array index starts at 0, normalize to 1 for clarity
    case 1:
      R1();
      break;
    case 2:
      R2();
      break;
    case 3:
			R3();
     	break;
    case 4:
      R4();
      break;
     case 5:
      R5();
      break;
     case 6:
      R6();
     break;
    default:
      //no autonomous routine was chosen, run a default one.
      break;
    }
}
