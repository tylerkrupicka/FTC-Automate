task jointRaise(){

		if(jointStop > 2600){

			wait10Msec(90);

		}

	while(jointTaskRunning == true){

		if(nMotorEncoder[Joint] < jointStop){

			motor[Joint] = 45;
			wait10Msec(1);

		}

		if(nMotorEncoder[Joint] >= jointStop - 25){

			motor[Joint] = 0;
			jointTaskRunning = false;
			jointStop = 0;
			StopTask(jointRaise);

		}

	}

}

/////////////////////////////////////////////////////////////////////////

task jointLower(){

	while(jointTaskRunning == true){

		if(nMotorEncoder[Joint] > jointStop){

			motor[Joint] = -40;
			wait10Msec(2);

		}

		if(nMotorEncoder[Joint] <= jointStop + 50){

			motor[Joint] = 0;
			jointTaskRunning = false;
			jointStop = 0;
			StopTask(jointLower);

		}

	}

}

task jointStow(){

	while(true){

		motor[Joint] = -35;
		if (nButtonsMask & 0x04){
						motor[Joint] = 0;
						nMotorEncoder[Joint] = 0;
						StopTask(jointStow);
		}

	}

}
