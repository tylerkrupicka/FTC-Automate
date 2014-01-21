/*task ResetArm ()
{
	 while(SensorValue[Touch] == 0) {   // While the Touch Sensor is inactive (hasn't been pressed):
    motor[Arm] = 20;
  }
  motor[Arm] = 0;
  nMotorEncoder[Arm] = 0;
  return;
}
*/

task RingTouch()
{
/////LOWER//////
	if(nMotorEncoder[Arm] < armStop)
		{
			motor[Arm] = 15;
			wait10Msec(2);
				while(nMotorEncoder[Arm] < armStop)  // while Motor Arm is still running (hasn't reached target yet):
	{
			   /* if( nMotorEncoder[Arm] > -1300 && nMotorEncoder[Arm] < 0 ) {

					servo[ClawLeft] = 210; //previously 230
					servo[ClawRight] = 40;

				}

				//Low Peg
				if( nMotorEncoder[Arm] < -1300 && nMotorEncoder[Arm] > -3000 ) {

						servo[ClawLeft] = 200; //previously 220
						servo[ClawRight] = 50; //previously 35

				}

				//Middle Peg
				if( nMotorEncoder[Arm] < -3000 && nMotorEncoder[Arm] > -7000 ) {

						servo[ClawLeft] = 140; //previously 150
						servo[ClawRight] = 95; //previously 105

				}

				//Top Peg
				if( nMotorEncoder[Arm] < -7000 && nMotorEncoder[Arm] > -9500 ) {

						servo[ClawLeft] = 170; //previously 220
						servo[ClawRight] = 80; //previously 35

				}

				//Backwards
				if( nMotorEncoder[Arm] < -9500 ) {

						servo[ClawLeft] = 44; //previously 54
						servo[ClawRight] = 211; //previously 201

				}*/

	}
		}
////////RAISE////////

	if(nMotorEncoder[Arm] > armStop)
		{
			motor[Arm] = -50;
			wait10Msec(2);
				while(nMotorEncoder[Arm] > armStop)  // while Motor Arm is still running (hasn't reached target yet):
	{

		/*if( nMotorEncoder[Arm] > -1300 && nMotorEncoder[Arm] < 0 ) {

					servo[ClawLeft] = 210; //previously 230
					servo[ClawRight] = 40;

				}

				//Low Peg
				if( nMotorEncoder[Arm] < -1300 && nMotorEncoder[Arm] > -3000 ) {

						servo[ClawLeft] = 200; //previously 220
						servo[ClawRight] = 50; //previously 35

				}

				//Middle Peg
				if( nMotorEncoder[Arm] < -3000 && nMotorEncoder[Arm] > -7000 ) {

						servo[ClawLeft] = 140; //previously 150
						servo[ClawRight] = 95; //previously 105

				}

				//Top Peg
				if( nMotorEncoder[Arm] < -7000 && nMotorEncoder[Arm] > -9500 ) {

						servo[ClawLeft] = 97; //previously 77
						servo[ClawRight] = 158; //previously 178

				}

				//Backwards
				if( nMotorEncoder[Arm] < -9500 ) {

						servo[ClawLeft] = 44; //previously 54
						servo[ClawRight] = 211; //previously 201

				}*/

	}
		}

	//////////////////////////////////////////////END/////////////////////////////////////////
	if(armStop + 10 > nMotorEncoder[Arm] > armStop - 10) {

		motor[Arm] = 0;
		armStop = 0;
		armTaskRunning = false;
		StopTask(RingTouch);

	}
}
