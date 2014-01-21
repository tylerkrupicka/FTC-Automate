task StartGyro() {
    while(true) {
      GyroTask();
    }
  }

task StartIR() {
	while(true) {
		 	IR = SensorValue[IRSeeker];
			nxtDisplayBigTextLine(0, "%i", IR);
		}
	}

	task checkTouch() {

		while(true){
		nButtonsMask = SensorValue[S4];
		}
	}
/*
task TurnLeftStart(){
	AutoDrive(11,75);
  turnDegrees(35);
  AutoDrive(50,75);
  a = a + 1;
}

task TurnRightStart(){
	AutoDrive(11,85);
  turnDegrees(-36);
  AutoDrive(50,90);
  a = a + 1;
}

task StraightMiddleStart(){
		AutoDrive(58,90);
		a = a + 1;
	}


task HangRing(){
				motor[FrontRight] = 60;
      	motor[BackRight] = 60;
      	motor[FrontLeft] = 60;
      	motor[BackLeft] = 60;
      	wait10Msec(15);
      	motor[FrontRight] = 0;
      	motor[BackRight] = 0;
      	motor[FrontLeft] = 0;
      	motor[BackLeft] = 0;
      	servo[ClawLeft] = 120; //previously 150
				servo[ClawRight] = 115; //previously 105
				wait10Msec(100);
      	motor[FrontRight] = -60;
      	motor[BackRight] = -60;
      	motor[FrontLeft] = -60;
      	motor[BackLeft] = -60;
      	wait10Msec(40);
      	motor[FrontRight] = 0;
      	motor[BackRight] = 0;
      	motor[FrontLeft] = 0;
      	motor[BackLeft] = 0;
      	a = a + 1;
}

task StraightHang(){
			motor[FrontRight] = -40;
      motor[BackRight] = -40;
      motor[FrontLeft] = 40;
      motor[BackLeft] = 40;
      wait10Msec(10);
      motor[FrontRight] = 40;
      motor[BackRight] = 40;
      motor[FrontLeft] = -40;
      motor[BackLeft] = -40;
			wait10Msec(10);
			a = a + 1;
		}

      //After hanging the ring
task DriveBack(){
  AutoDrive(-22,85);
	servo[ClawLeft] = 245;
	servo[ClawRight] = 10;
	a = a + 1;
}

task TurnLeftEnd(){
	turnDegrees(-10);
	AutoDrive(27,90);
  a = a + 1;
}

task TurnRightEnd(){
	turnDegrees(10);
	AutoDrive(27,90);
  a = a + 1;
}

task StraightMiddleEndLeft(){
	turnDegrees(30);
	AutoDrive(27,90);
	servo[ClawLeft] = 255;
	servo[ClawRight] = 0;
	a = a + 1;
}

task StraightMiddleEndRight(){
	turnDegrees(-30);
	AutoDrive(27,90);
	servo[ClawLeft] = 255;
	servo[ClawRight] = 0;
	a = a + 1;
}

task IRZero(){
	AutoDrive(30,100);
	wait10Msec(2);
	a = a + 1;
}

task IROneLeft(){
	turnDegrees(45);
	AutoDrive(21,90);
	turnDegrees(0);
	AutoDrive(16,90);
	a = a + 1;
}

task IROneRight(){
	turnDegrees(-45);
	AutoDrive(23,90);
	turnDegrees(-10);
	AutoDrive(12,90);
	a = a + 1;
}

task IROneMiddle(){
	AutoDrive(20,90);
	a = a + 1;
}

task Block(){
	AutoDrive(-95,100);
}
//////////////////////////////////////////////////////////////////
*/
void TurnLeftMiddlePeg() {
			a = 0;
			StartTask(RaiseArmMiddle);
	if(a == 0)				//If tasks never complete, integer "a" will never raise in value
		{
			StartTask(TurnLeftStart);
			wait10Msec(500);
			StopTask(TurnLeftStart);
		}
		  StopTask(RaiseArmMiddle);
	if(a == 1)
		{
		  steven = false; //Arm can be lowered if false
		  motor[Arm] = 0;
			servo[ClawLeft] = 140;
			servo[ClawRight] = 95;
			wait10Msec(100);

		}
	if(a == 2)
		{
			StartTask(DriveBack);
			wait10Msec(275);
			StopTask(DriveBack);
		}
	if(a == 3)
		{
			StartTask(RaiseArmMiddle);
			wait10Msec(300);
			StopTask(RaiseArmMiddle);
			servo[ClawLeft] = 255;
			servo[ClawRight] = 0;
			wait10Msec(2);
			StartTask(TurnLeftEnd);
			wait10Msec(500);
			StopTask(TurnLeftEnd);
		}
}

//////////////////////////////////////////////////////////////////////////////////////


	void StraightMiddleLeft() {
			a = 0;
			StartTask(RaiseArmMiddle);
		if(a == 0)
		{
			StartTask(StraightMiddleStart);
			wait10Msec(300);
			StopTask(StraightMiddleStart);
		}
		if(a == 1)
		{
			servo[ClawLeft] = 100; //previously 150
			servo[ClawRight] = 135; //previously 105
			StopTask(RaiseArmMiddle);
			StartTask(StraightHang);
			wait10Msec(200);
			StopTask(StraightHang);
		}
		if(a == 2)
		{
			StartTask(DriveBack);
			wait10Msec(275);
			StopTask(DriveBack);
		}
		if(a == 3)
		{
			GyroInit(gyroSensor);
			servo[ClawLeft] = 255;
			servo[ClawRight] = 0;
			steven = false;
			StartTask(RaiseArmMiddle);
			wait10Msec(200);
			StopTask(RaiseArmMiddle);
			StartTask(StraightMiddleEndLeft);
			wait10Msec(200);
			StopTask(StraightMiddleEndLeft);
			servo[ClawLeft] = 255;
			servo[ClawRight] = 0;
			wait10Msec(100);
		}
	}

////////////////////////////////////////////////////////////////

		void StraightMiddleRight() {
			a = 0;
			StartTask(RaiseArmMiddle);
		if(a == 0)
		{
			StartTask(StraightMiddleStart);
			wait10Msec(300);
			StopTask(StraightMiddleStart);
		}
		if(a == 1)
		{
			servo[ClawLeft] = 100; //previously 150
			servo[ClawRight] = 135; //previously 105
			StopTask(RaiseArmMiddle);
			StartTask(StraightHang);
			wait10Msec(200);
			StopTask(StraightHang);
		}
		if(a == 2)
		{
			StartTask(DriveBack);
			wait10Msec(275);
			StopTask(DriveBack);
		}
		if(a == 3)
		{
			GyroInit(gyroSensor);
			servo[ClawLeft] = 255;
			servo[ClawRight] = 0;
			steven = false;
			StartTask(RaiseArmMiddle);
			wait10Msec(200);
			StopTask(RaiseArmMiddle);
			StartTask(StraightMiddleEndRight);
			wait10Msec(200);
			StopTask(StraightMiddleEndRight);
		}
	}

/////////////////////////////////////////////////////////////////


void Blocking()	{
			StartTask(Block);
			wait10Msec(1000);
			StopTask(Block);
	}
	////////////////////////////////////////////////////////////

void IRRoutine() {
			a = 0;
			GyroInit(gyroSensor);
			StartTask(StartIR);
			StartTask(RaiseArmMiddle);
				if(a == 0){
					StartTask(IRZero);
					wait10Msec(275);
					StopTask(IRZero);
				}
		if(IR == 3) //Left Peg
			{
				if(a == 1){
					StartTask(IROneLeft);
					wait10Msec(600);
					StopTask(IROneLeft);
				}
				//
				if(a == 2){
					servo[ClawLeft] = 100;
					servo[ClawRight] = 135;
					StopTask(RaiseArmMiddle);
					StartTask(StraightHang);
					wait10Msec(200);
					StopTask(StraightHang);
				}
				//
							StopTask(RaiseArmMiddle);
				//
				//
				if(a == 3){
					GyroInit(gyroSensor);
					servo[ClawLeft] = 255;
					servo[ClawRight] = 0;
					steven = false;
					StartTask(RaiseArmMiddle);
					wait10Msec(200);
					StopTask(RaiseArmMiddle);
				}
/*				StartTask(StraightMiddleEndRight);
				wait10Msec(200);
				StopTask(StraightMiddleEndRight);*/
			}
		else if(IR == 5) //Right Peg
			{
				if(a == 1){
					StartTask(IROneRight);
					wait10Msec(600);
					StopTask(IROneRight);
				}
				//
				if(a == 2){
					servo[ClawLeft] = 100;
					servo[ClawRight] = 135;
					StopTask(RaiseArmMiddle);
					StartTask(StraightHang);
					wait10Msec(200);
					StopTask(StraightHang);
				}
				//
							StopTask(RaiseArmMiddle);
				//
				//
				if(a == 3){
					GyroInit(gyroSensor);
					servo[ClawLeft] = 255;
					servo[ClawRight] = 0;
					steven = false;
					StartTask(RaiseArmMiddle);
					wait10Msec(200);
					StopTask(RaiseArmMiddle);
				}
	/*			StartTask(StraightMiddleEndRight);
				wait10Msec(200);
				StopTask(StraightMiddleEndRight);*/
			}
		else //Middle Peg
			{
				if(a == 1){
					StartTask(IROneMiddle);
					wait10Msec(150);
					StopTask(IROneMiddle);
				}
				//
				if(a == 2){
					servo[ClawLeft] = 100; //previously 150
					servo[ClawRight] = 135; //previously 105
					StopTask(RaiseArmMiddle);
					StartTask(StraightHang);
					wait10Msec(200);
					StopTask(StraightHang);
				}
				//
								StopTask(RaiseArmMiddle);
				//
				if(a == 3){
					StartTask(DriveBack);
					wait10Msec(275);
					StopTask(DriveBack);
				}
				//
				if(a == 4){
					GyroInit(gyroSensor);
					servo[ClawLeft] = 255;
					servo[ClawRight] = 0;
					steven = false;
					StartTask(RaiseArmMiddle);
					wait10Msec(200);
					StopTask(RaiseArmMiddle);
				}
				/*StartTask(StraightMiddleEndRight);
				wait10Msec(200);
				StopTask(StraightMiddleEndRight);*/
			}




}
