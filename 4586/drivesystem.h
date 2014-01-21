#include "FTC_PID.c"
//#include "FTC_Gyro.c"
#include "common.h"
#include "FTC_ValueUtils.h"

//DriveArcade: arcade drive, power range -100 to 100
void DriveArcade(float moveValue, float rotateValue) {

  if (fineDriveMode) {
	  moveValue = moveValue*FINE_CONTROL_MODIFIER;
	  rotateValue = rotateValue*FINE_CONTROL_MODIFIER;
  } else if (mediumDriveMode) {
     moveValue = moveValue*MEDIUM_CONTROL_MODIFIER;
	  rotateValue = rotateValue*MEDIUM_CONTROL_MODIFIER;
   }
	float leftMotorSpeed;
  float rightMotorSpeed;

	if (moveValue > 0) {  //if we have a fwd component
	  if (rotateValue > 0) {  //turn right
	    rightMotorSpeed = moveValue - rotateValue;
      leftMotorSpeed = max(moveValue, rotateValue);
    } else {                //turn left
      rightMotorSpeed = max(moveValue, -rotateValue);
      leftMotorSpeed = moveValue + rotateValue;
    }
  } else {  // no forward component, only rotate
    if (rotateValue > 0) {   //turn right
      rightMotorSpeed = - max(-moveValue, rotateValue);
      leftMotorSpeed = moveValue + rotateValue;
    } else {                //turn left
      rightMotorSpeed = moveValue - rotateValue;
      leftMotorSpeed = - max(-moveValue, -rotateValue);
    }
  }

	motor[FrontLeft] = leftMotorSpeed;
	motor[MidLeft] = leftMotorSpeed;
	motor[BackLeft] = leftMotorSpeed;

	motor[BackRight] = rightMotorSpeed;
	motor[MidRight] = rightMotorSpeed;
	motor[FrontRight] = rightMotorSpeed;

	return;
}// end DriveArcade

void turnDegrees(int deg)
{
  PID turn;
  initPID(turn, 0.4, 0.5); // .2 .3
  turn.acceptedRange = 1;
  turn.target = deg;
  int cyclesStable = 0;
  while ( cyclesStable < 10 )
  {
    if ( abs(turn.error) < 5 )
       cyclesStable++;
    else
      cyclesStable = 0;
    //nxtDisplayString(0, "%i", turn.error);
    int output = calcPID(turn, -GYROheading);
    motor[FrontLeft] = limitVar(output, 85);
    motor[MidLeft] = limitVar(output, 85);
    motor[BackLeft] = limitVar(output, 85);
    motor[FrontRight] = -limitVar(output, 85);
    motor[MidRight] = -limitVar(output, 85);
    motor[BackRight] = -limitVar(output, 85);
  }
  motor[BackLeft] = 0;
  motor[MidRight] = 0;
  motor[MidLeft] = 0;
  motor[BackRight] = 0;
  motor[FrontLeft] = 0;
  motor[FrontRight] = 0;
  return;
}

void resetEncoders ()
{
  nMotorEncoder[BackRight] = 0;
  wait10Msec(2);
}

void Drive (int MotorPower)
{
  motor[FrontLeft] = MotorPower;
  motor[FrontRight] = MotorPower;
  motor[BackLeft] = MotorPower;
  motor[BackRight] = MotorPower;
  motor[MidLeft] = MotorPower;
  motor[MidRight] = MotorPower;
}

void AutoDrive(float targetPosition, int powerAsked) {
  int highlimit = min(MOTOR_MAX_VALUE_AUTO, powerAsked);
  int lowlimit = max(MOTOR_MIN_VALUE_AUTO, -powerAsked);
  float errorR;
  float previous_errorR = 0;
  float integralR = 0;
  float derivativeR = 0;
  int motorPowerR = 0;
  nMotorEncoder[BackRight] = 0;
  errorR = (targetPosition / DISTANCE_PER_CLICK) - nMotorEncoder[BackRight];
  ClearTimer(T3);
  while ((time10[T3] < 800) &&  (abs(errorR) > DRIVE_TOLERANCE)) {  //watchdog 8 seconds
	  while (abs(errorR) > DRIVE_TOLERANCE) {  //we're not there!
	    errorR = (targetPosition / DISTANCE_PER_CLICK) - nMotorEncoder[BackRight];
	    integralR += errorR;
	    derivativeR = (errorR - previous_errorR);
	    motorPowerR = (int)((DRIVE_KP*errorR)+(DRIVE_KI*integralR)+(DRIVE_KD*derivativeR));
	    nxtDisplayTextLine(6, "PID:%5d E:%5f", motorPowerR, errorR*DISTANCE_PER_CLICK);

	  	if (motorPowerR >= 0) {
	      motorPowerR = min(motorPowerR, highlimit);
	      motorPowerR = max(motorPowerR, 15);
	    } else {
	      motorPowerR = max(motorPowerR, lowlimit);
	      motorPowerR = min(motorPowerR, -15);
	    }

	    nxtDisplayTextLine(7, "out:%5d", motorPowerR);
	   Drive(motorPowerR);
	    previous_errorR = errorR;
	  }
	}
  Drive(0);

} //End AutoDrive

//GyroTurn: turn target degrees at "power" motor percentage, while moving forward at drivePower
/*void GyroTurn(int turnDegrees, int turnPower, int drivePower) {
  updateGyroOffset(S2);
  wait10Msec(50);
  float turnRatio = (float)drivePower /(float)turnPower;
  ClearTimer(T2);
  float targetHeading = -Pgyro.cum_turn + (float)turnDegrees; //add target to current heading
  while (time10[T2] < 1000 ) {  //5 second timeout = 500 centiseconds
	  float heading = -Pgyro.cum_turn;
	  float degreesLeftToTurn = abs(targetHeading - heading);
    nxtDisplayTextLine(6,"H:%3.1f T:%3.1f", heading, targetHeading);

    int highlimit = (int)degreesLeftToTurn;
    turnPower = min(turnPower, highlimit);
    turnPower = max(turnPower,  30);///////////...........
    drivePower = (int)(turnRatio * turnPower);
    nxtDisplayTextLine(7,"TP:%3d DP:%3d", turnPower, drivePower);

	  if (heading < (targetHeading - GYRO_TOLERANCE)) { //we are right of target, turn left
	    DriveArcade(drivePower, turnPower);
	  } else if ( heading > (targetHeading + GYRO_TOLERANCE)) {  //we are left of target, turn right
	    DriveArcade(drivePower, turnPower * -1);
	  } else if ( heading < (targetHeading + GYRO_TOLERANCE) && heading > (targetHeading - GYRO_TOLERANCE)) {  //within buffer zone
	    DriveArcade(0,0);
	    break;
	  }
	  //while ((nPgmTime - currTime) < 25) {
	  //    wait1Msec(1);
	  //  }
  }
  DriveArcade(0,0);
  return;
}//end GyroTurn

//GyroTurnToHeading: Turns to a compass heding between 0-359 degrees.
void GyroTurnToHeading(int targetCompassHeading, int turnPower, int drivePower) {
  int currHeading = -Pgyro.cum_turn + initialHeadingOffset;
  int degreesToTurn = targetCompassHeading - (currHeading%360);
  if (degreesToTurn > 180) {
    degreesToTurn -= 360;
  }
  if (degreesToTurn < -180) {
    degreesToTurn += 360;
  }
  GyroTurn(degreesToTurn, turnPower, drivePower);
}

//AutoDrive: drive distance (inches) at power
void AutoDrive(float targetPosition, int powerAsked) {
  int highlimit = min(MOTOR_MAX_VALUE_AUTO, powerAsked);
  int lowlimit = max(MOTOR_MIN_VALUE_AUTO, -powerAsked);
  float errorL;
  float errorR;
  float previous_errorL = 0;
  float previous_errorR = 0;
  float integralL = 0;
  float integralR = 0;
  float derivativeL = 0;
  float derivativeR = 0;
  int motorPowerL = 0;
  int motorPowerR = 0;
//  nMotorEncoder[motorLeft] = 0;
//  nMotorEncoder[motorRight] = 0;

//  errorL = (targetPosition / DISTANCE_PER_CLICK) - nMotorEncoder[motorLeft];
//  errorR = (targetPosition / DISTANCE_PER_CLICK) - nMotorEncoder[motorRight];
  ClearTimer(T3);
  while ((time10[T3] < 800) && ((abs(errorL) > DRIVE_TOLERANCE) || (abs(errorR) > DRIVE_TOLERANCE))) {  //watchdog 8 seconds
	  while ((abs(errorL) > DRIVE_TOLERANCE) || (abs(errorR) > DRIVE_TOLERANCE)) {  //we're not there!
//	    errorL = (targetPosition / DISTANCE_PER_CLICK) - nMotorEncoder[motorLeft];
//	    errorR = (targetPosition / DISTANCE_PER_CLICK) - nMotorEncoder[motorRight];
	    integralL += errorL;
	    integralR += errorR;
	    derivativeL = (errorL - previous_errorL);
	    derivativeR = (errorR - previous_errorR);
	    motorPowerL = (int)((DRIVE_KP*errorL)+(DRIVE_KI*integralL)+(DRIVE_KD*derivativeL));
	    motorPowerR = (int)((DRIVE_KP*errorR)+(DRIVE_KI*integralR)+(DRIVE_KD*derivativeR));
	    nxtDisplayTextLine(6, "PID:%5d E:%5f", motorPowerL, errorL*DISTANCE_PER_CLICK);
	    if (motorPowerL >= 0) {
	      motorPowerL = min(motorPowerL, highlimit);  //don't be faster than requested speed
	      motorPowerL = max(motorPowerL, 15);         //don't be slower than 10% or we stall
	    } else {
	      motorPowerL = max(motorPowerL, lowlimit);
	      motorPowerL = min(motorPowerL, -15);
	    }
	  	if (motorPowerR >= 0) {
	      motorPowerR = min(motorPowerR, highlimit);
	      motorPowerR = max(motorPowerR, 15);
	    } else {
	      motorPowerR = max(motorPowerR, lowlimit);
	      motorPowerR = min(motorPowerR, -15);
	    }

	    nxtDisplayTextLine(7, "out:%5d", motorPowerL);
//	    motor[motorLeft] = motorPowerL;
//	    motor[motorRight] = motorPowerR;
	    previous_errorL = errorL;
	    previous_errorR = errorR;
	  }
	}
//  motor[motorLeft] = 0;
// motor[motorRight] = 0;

}// end AutoDrive

/*void FollowLine(int distance) {
  nMotorEncoder[motorLeft] = 0;
  int offLinePos = -1;
  bool offTheLine;
  float targetDistance = distance / DISTANCE_PER_CLICK;
  while (abs(targetDistance) > DRIVE_TOLERANCE) {
    nxtDisplayTextLine(7, "Dist:%5.3d", targetDistance);
    if (SensorValue[sensorLight] <= LIGHT_SENSOR_CUTOFF) {
      //if (!offTheLine) { //this is the first time that we've left the line
       // offTheLine = true;
       // offLinePos = nMotorEncoder[motorLeft];
      //} else {
      //  if ((nMotorEncoder[motorLeft] - offLinePos) > 3 / DISTANCE_PER_CLICK) {
          //return;
       // }
      //}
      DriveArcade(15, -4);
    } else {
      offTheLine = false;
      offLinePos = -1;
      DriveArcade(15, 4);
    }
    targetDistance = (distance / DISTANCE_PER_CLICK) - nMotorEncoder[motorLeft];
  }
  DriveArcade(0,0);
}

//AutoDriveToLine: drive distance (inches) at power
bool AutoDriveToLine(float targetPosition, int powerAsked) {
  int highlimit = min(MOTOR_MAX_VALUE_AUTO, powerAsked);
  int lowlimit = max(MOTOR_MIN_VALUE_AUTO, -powerAsked);
  float errorL;
  float errorR;
  float previous_errorL = 0;
  float previous_errorR = 0;
  float integralL = 0;
  float integralR = 0;
  float derivativeL = 0;
  float derivativeR = 0;
  int motorPowerL = 0;
  int motorPowerR = 0;
  nMotorEncoder[motorLeft] = 0;
  nMotorEncoder[motorRight] = 0;

  errorL = (targetPosition / DISTANCE_PER_CLICK) - nMotorEncoder[motorLeft];
  errorR = (targetPosition / DISTANCE_PER_CLICK) - nMotorEncoder[motorRight];
  ClearTimer(T3);
  while ((time10[T3] < 800) && ((abs(errorL) > DRIVE_TOLERANCE) || (abs(errorR) > DRIVE_TOLERANCE))) {  //watchdog 8 seconds
    while ((abs(errorL) > DRIVE_TOLERANCE) || (abs(errorR) > DRIVE_TOLERANCE)) {  //we're not there!
      if (SensorValue[sensorLight] >= LIGHT_SENSOR_CUTOFF) {
        motor[motorLeft] = 0;
        motor[motorRight] = 0;
        return true;
      }
	    errorL = (targetPosition / DISTANCE_PER_CLICK) - nMotorEncoder[motorLeft];
	    errorR = (targetPosition / DISTANCE_PER_CLICK) - nMotorEncoder[motorRight];
	    integralL += errorL;
	    integralR += errorR;
	    derivativeL = (errorL - previous_errorL);
	    derivativeR = (errorR - previous_errorR);
	    motorPowerL = (int)((DRIVE_KP*errorL)+(DRIVE_KI*integralL)+(DRIVE_KD*derivativeL));
	    motorPowerR = (int)((DRIVE_KP*errorR)+(DRIVE_KI*integralR)+(DRIVE_KD*derivativeR));
	    nxtDisplayTextLine(6, "PID:%5d E:%5f", motorPowerL, errorL*DISTANCE_PER_CLICK);
	    if (motorPowerL >= 0) {
	      motorPowerL = min(motorPowerL, highlimit);  //don't be faster than requested speed
	      motorPowerL = max(motorPowerL, 15);         //don't be slower than 10% or we stall
	    } else {
	      motorPowerL = max(motorPowerL, lowlimit);
	      motorPowerL = min(motorPowerL, -15);
	    }
	  	if (motorPowerR >= 0) {
	      motorPowerR = min(motorPowerR, highlimit);
	      motorPowerR = max(motorPowerR, 15);
	    } else {
	      motorPowerR = max(motorPowerR, lowlimit);
	      motorPowerR = min(motorPowerR, -15);
	    }

	    nxtDisplayTextLine(7, "out:%5d", motorPowerL);
	    motor[motorLeft] = motorPowerL;
	    motor[motorRight] = motorPowerR;
	    previous_errorL = errorL;
	    previous_errorR = errorR;
	  } //end of the driving loop
	}
  motor[motorLeft] = 0;
  motor[motorRight] = 0;
  return false;

}// end AutoDriveToLine
*/
