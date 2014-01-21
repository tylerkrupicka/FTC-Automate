task Gyro() {
    while(true) {
      GyroTask();
      wait10Msec(1);
    }
  }

 task SideDrive() {

 AutoDrive(32,97);

}

task StartIR() {
	while(true) {
		 	IR = SensorValue[IRSeeker];
			nxtDisplayBigTextLine(0, "%i", IR);
		}
	}

	task turnLeft(){

	motor[FrontLeft] = -80;
		motor[FrontRight] = 80;
	motor[MidLeft] = -80;
		motor[MidRight] = 80;
	motor[BackLeft] = -80;
		motor[BackRight] = 80;


	}

		task turnRight(){

	motor[FrontLeft] = 80;
		motor[FrontRight] = -80;
	motor[MidLeft] = 80;
		motor[MidRight] = -80;
	motor[BackLeft] = 80;
		motor[BackRight] = -80;


	}

			task driveStraight(){

	motor[FrontLeft] = 100;
		motor[FrontRight] = 100;
	motor[MidLeft] = 100;
		motor[MidRight] = 100;
	motor[BackLeft] = 100;
		motor[BackRight] = 100;


	}


	task watchdog3() {

		wait10Msec(300);
		StopAllTasks();

	}

	task watchdog2() {

		wait10Msec(200);
		StopAllTasks();

	}

		task watchdog5() {

		wait10Msec(500);
		StopAllTasks();

	}

////////////////////////////////////ROUTINES//////////////////////


void StraightMiddleLeft() {

					//Raise Arm Middle
					StartTask(watchdog2);
					armTaskRunning = true;
					jointTaskRunning = true;
					armStop = 4200;
					jointStop = 2300;
					runArm();
					wait10Msec(50);
					StopTask(watchdog2);
					//Drive straight
					StartTask(watchdog3);
					//GyroInit(gyroSensor);
					AutoDrive(50,95);
					StopTask(watchdog3);

					wait10Msec(50);

					StartTask(watchdog2);
					//lower arm
					armTaskRunning = true;
					armStop = 3550;
					jointStop = 2450;
					runArm();
					wait10Msec(100);
					StopTask(watchdog2);
					//wait10Msec(250);

					//Drive back
					//AutoDrive(-14,95);
					//Raise again
					//armTaskRunning = true;
					//jointTaskRunning = true;
					//armStop = 3950;
				//	jointStop = 2300;
					//runArm();

					//drive forward
					//StartTask(turnRight);
					//wait10Msec(10);
					//StopTask(turnRight);
					//AutoDrive(12,95);
					//wait10Msec(100);

					//lower
					//armTaskRunning = true;
					//armStop = 3200;
					//runArm();
					//wait10Msec(200);
					//drive back
					StartTask(watchdog3);
					AutoDrive(-35,100);
					StopTask(watchdog3);

					StartTask(jointStow);
					wait10Msec(150);
					StopTask(jointStow);

					StartTask(armStow);
					wait10Msec(100);
					motor[Arm] = 0;
					motor[Joint] = 0;
					StopTask(armStow);

					//turn and drive
					StartTask(watchdog3);
					turnDegrees(-40);
					wait10Msec(100);
					AutoDrive(28,98);
					StopTask(watchdog3);

}

void StraightMiddleRight() {

//Raise Arm Middle
					StartTask(watchdog2);
					armTaskRunning = true;
					jointTaskRunning = true;
					armStop = 4200;
					jointStop = 2300;
					runArm();
					wait10Msec(50);
					StopTask(watchdog2);
					//Drive straight
					StartTask(watchdog3);
					//GyroInit(gyroSensor);
					AutoDrive(50,95);
					StopTask(watchdog3);

					wait10Msec(50);

					StartTask(watchdog2);
					//lower arm
					armTaskRunning = true;
					armStop = 3550;
					jointStop = 2450;
					runArm();
					wait10Msec(100);
					StopTask(watchdog2);
					//wait10Msec(250);

					//Drive back
					//AutoDrive(-14,95);
					//Raise again
					//armTaskRunning = true;
					//jointTaskRunning = true;
					//armStop = 3950;
				//	jointStop = 2300;
					//runArm();

					//drive forward
					//StartTask(turnRight);
					//wait10Msec(10);
					//StopTask(turnRight);
					//AutoDrive(12,95);
					//wait10Msec(100);

					//lower
					//armTaskRunning = true;
					//armStop = 3200;
					//runArm();
					//wait10Msec(200);
					//drive back
					StartTask(watchdog3);
					AutoDrive(-35,100);
					StopTask(watchdog3);

					StartTask(jointStow);
					wait10Msec(150);
					StopTask(jointStow);

					StartTask(armStow);
					wait10Msec(100);
					motor[Arm] = 0;
					motor[Joint] = 0;
					StopTask(armStow);

					//turn and drive
					StartTask(watchdog3);
					turnDegrees(40);
					wait10Msec(100);
					AutoDrive(28,98);
					StopTask(watchdog3);


}


void SideStraightRight(){

					//Raise Arm low
					StartTask(watchdog5);
					armTaskRunning = true;
					jointTaskRunning = true;
					armStop = 2075;
					jointStop = 1900;
					runArm();
					//wait10Msec(0);

					StartTask(SideDrive);
					wait10Msec(250);
					StopTask(SideDrive);

					StopTask(watchdog5);

					wait10Msec(50);

					StartTask(watchdog2);
					armTaskRunning = true;
					armStop = 1400;
					jointStop = 2150;
					runArm();

					wait10Msec(75);
					StopTask(watchdog2);

					StartTask(watchdog3);
					StartTask(jointStow);
					AutoDrive(-12,95);
					StopTask(jointStow);
					StopTask(watchdog3);

					StartTask(watchdog3);
					turnDegrees(40);
					StopTask(watchdog3);

					StartTask(watchdog3);
					StartTask(jointStow);
					AutoDrive(42,95);
					StopTask(jointStow);
					StopTask(watchdog3);

					StartTask(armStow);
					wait10Msec(40);
					motor[Arm] = 0;
					motor[Joint] = 0;
					StopTask(armStow);




}

void SideStraightLeft(){

					//Raise Arm low
					StartTask(watchdog5);
					armTaskRunning = true;
					jointTaskRunning = true;
					armStop = 2075;
					jointStop = 1900;
					runArm();
					//wait10Msec(0);

					StartTask(SideDrive);
					wait10Msec(250);
					StopTask(SideDrive);

					StopTask(watchdog5);

					wait10Msec(50);

					StartTask(watchdog2);
					armTaskRunning = true;
					armStop = 1400;
					jointStop = 2150;
					runArm();

					wait10Msec(75);
					StopTask(watchdog2);

					StartTask(watchdog3);
					StartTask(jointStow);
					AutoDrive(-12,95);
					StopTask(jointStow);
					StopTask(watchdog3);

					StartTask(watchdog3);
					turnDegrees(-40);
					StopTask(watchdog3);

					StartTask(watchdog3);
					StartTask(jointStow);
					AutoDrive(42,95);
					StopTask(jointStow);
					StopTask(watchdog3);

					//StartTask(jointStow);
					//wait10Msec(150);
					//StopTask(jointStow);

					StartTask(armStow);
					wait10Msec(40);
					motor[Arm] = 0;
					motor[Joint] = 0;
					StopTask(armStow);




}

void IRRoutine() {

					StartTask(StartIR);

					StartTask(watchdog5);

					while (IR != 8){

					motor[BackLeft] = 90;
					motor[MidLeft] = 90;
					motor[FrontLeft] = 90;
					motor[BackRight] = 90;
					motor[MidRight] = 90;
					motor[FrontRight] = 90;



					}

					StopTask(watchdog5);

					StartTask(watchdog3);
					turnDegrees(88);
					StopTask(watchdog3);

					wait10Msec(100);

					StartTask(watchdog5);
					armTaskRunning = true;
					jointTaskRunning = true;
					armStop = 2700;
					jointStop = 2400;
					runArm();
					wait10Msec(200);
					StopTask(watchdog5);

					//StartTask(watchdog2);
					//AutoDrive(2,100);
					//StopTask(watchdog2);

					StartTask(watchdog2);
					armTaskRunning = true;
					armStop = 2000;
					jointStop = 2450;
					runArm();

					wait10Msec(75);
					StopTask(watchdog2);

					StartTask(watchdog2);
					//GyroInit(gyroSensor);
					AutoDrive(-10,100);
					StopTask(watchdog2);

					StartTask(jointStow);
					wait10Msec(150);
					StopTask(jointStow);

					StartTask(armStow);
					wait10Msec(60);
					motor[Arm] = 0;
					motor[Joint] = 0;
					StopTask(armStow);

					/*StartTask(StartIR);

					StartTask(watchdog2);
					armTaskRunning = true;
					jointTaskRunning = true;
					armStop = 4300;
					jointStop = 2300;
					runArm();
					wait10Msec(50);
					StopTask(watchdog2);
					//Drive straight
					StartTask(watchdog3);
					AutoDrive(30,95);
					StopTask(watchdog3);

					//straight
					if(IR == 3){

							StartTask(watchdog3);
							AutoDrive(22,95);
							StopTask(watchdog3);

							StartTask(watchdog2);
							//lower arm
							armTaskRunning = true;
							armStop = 3550;
							runArm();
							wait10Msec(100);
							StopTask(watchdog2);

							StartTask(watchdog3);
							AutoDrive(-40,100);
							StopTask(watchdog3);

							StartTask(jointStow);
							wait10Msec(150);
							StopTask(jointStow);

							StartTask(armStow);
							wait10Msec(150);
							StopTask(armStow);


					}

					//right
					if(IR > 3){

					//positive turn degrees
					StartTask(watchdog2);
					turnDegrees(55);
					StopTask(watchdog2);

					StartTask(watchdog3);
					AutoDrive(24,90);
					StopTask(watchdog3);

					StartTask(watchdog2);
					turnDegrees(6);
					StopTask(watchdog2);

					StartTask(watchdog2);
					AutoDrive(14,90);
					StopTask(watchdog2);

					StartTask(watchdog2);
					//lower arm
					armTaskRunning = true;
					armStop = 3550;
					runArm();
					wait10Msec(100);
					StopTask(watchdog2);

					StartTask(watchdog2);
					AutoDrive(-15,90);
					StopTask(watchdog2);

					StartTask(watchdog2);
					armTaskRunning = true;
					jointTaskRunning = true;
					armStop = 4350;
					jointStop = 2400;
					runArm();
					wait10Msec(50);
					StopTask(watchdog2);

					wait10Msec(100);

					StartTask(turnLeft);
					wait10Msec(10);
					StopTask(turnLeft);

					StartTask(watchdog2);
					AutoDrive(19,90);
					StopTask(watchdog2);

					StartTask(watchdog2);
					//lower arm
					armTaskRunning = true;
					armStop = 3550;
					runArm();
					wait10Msec(100);
					StopTask(watchdog2);

					StartTask(watchdog2);
					AutoDrive(-14,90);
					StopTask(watchdog2);




					}

					//left
					if(IR < 3){




					}*/



}


void Blocking() {

					StartTask(watchdog5);
					//GyroInit(gyroSensor);
					AutoDrive(-106,100);
					StopTask(watchdog5);

					wait10Msec(1500);

					StartTask(watchdog3);
					//GyroInit(gyroSensor);
					AutoDrive(52,100);
					StopTask(watchdog3);




}

void OpHangLeft() {

StartTask(watchdog5);
					//GyroInit(gyroSensor);
					AutoDrive(-67,100);
					StopTask(watchdog5);

					GyroInit(gyroSensor);
					wait10Msec(75);

					StartTask(watchdog3);
					turnDegrees(-46);
					StopTask(watchdog3);

					wait10Msec(25);

					StartTask(watchdog5);
					armTaskRunning = true;
					jointTaskRunning = true;
					armStop = 2900;
					jointStop = 2025;
					runArm();
					wait10Msec(300);
					StopTask(watchdog5);

				//	StartTask(watchdog2);
					//GyroInit(gyroSensor);
				//	AutoDrive(4,75);
				//	StopTask(watchdog2);

					StartTask(watchdog2);
					armTaskRunning = true;
					armStop = 900;
					jointStop = 2050;
					runArm();

					wait10Msec(75);
					StopTask(watchdog2);

					StartTask(watchdog3);
					AutoDrive(-10,95);
					StopTask(watchdog3);

					StartTask(jointStow);
					wait10Msec(150);
					StopTask(jointStow);

					StartTask(armStow);
					wait10Msec(30);
					motor[Arm] = 0;
					motor[Joint] = 0;
					StopTask(armStow);


}

void OpHangRight() {

					StartTask(watchdog5);
					//GyroInit(gyroSensor);
					AutoDrive(-67,100);
					StopTask(watchdog5);

					GyroInit(gyroSensor);
					wait10Msec(75);

					StartTask(watchdog3);
					turnDegrees(46);
					StopTask(watchdog3);

					wait10Msec(25);

					StartTask(watchdog5);
					armTaskRunning = true;
					jointTaskRunning = true;
					armStop = 2900;
					jointStop = 2025;
					runArm();
					wait10Msec(300);
					StopTask(watchdog5);


					//StartTask(watchdog2);
					//GyroInit(gyroSensor);
					//AutoDrive(5,95);
					//StopTask(watchdog2);

					StartTask(watchdog2);
					armTaskRunning = true;
					armStop = 900;
					jointStop = 2050;
					runArm();

					wait10Msec(75);
					StopTask(watchdog2);

					StartTask(watchdog3);
					AutoDrive(-10,95);
					StopTask(watchdog3);

					StartTask(jointStow);
					wait10Msec(150);
					StopTask(jointStow);

					StartTask(armStow);
					wait10Msec(30);
					motor[Arm] = 0;
					motor[Joint] = 0;
					StopTask(armStow);

}
