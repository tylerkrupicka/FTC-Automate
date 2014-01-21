task armRaise(){

	while(armTaskRunning == true){

		if(nMotorEncoder[Arm] < armStop){

			motor[Arm] = 80;
			wait10Msec(1);

		}

		if(nMotorEncoder[Arm] >= armStop - 25){

			motor[Arm] = 0;
			armTaskRunning = false;
			armStop = 0;
			StopTask(armRaise);

		}

	}

}

///////////////////////////////////////////////////////////////////////////

task armLower(){

	while(armTaskRunning == true){

		if(nMotorEncoder[Arm] > armStop){

			motor[Arm] = -40;
			wait10Msec(1);

		}

		if(nMotorEncoder[Arm] <= armStop + 50){

			motor[Arm] = 0;
			armTaskRunning = false;
			armStop = 0;
			StopTask(armLower);

		}

	}

}

void runArm(){

	if(nMotorEncoder[Arm] < armStop){

		StartTask(armRaise);

	}

	if(nMotorEncoder[Arm] > armStop){

		StartTask(armLower);

	}

	if(nMotorEncoder[Joint] < jointStop){

		//if(jointStop > 2600){

		//	wait10Msec(125);

	//	}

		StartTask(jointRaise);

	}

	if(nMotorEncoder[Joint] > jointStop){

		StartTask(jointLower);

	}

}

task armStow(){

	while(true){

		motor[Arm] = -25;
		if (nButtonsMask & 0x02){
						motor[Arm] = 0;
						nMotorEncoder[Arm] = 0;
						StopTask(armStow);
		}

	}

}
