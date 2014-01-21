#define WHEEL_CIRCUMFERENCE       (3.95*PI)  //in inches
#define CLICKS_PER_REVOLUTION     1440.0
#define DISTANCE_PER_CLICK        (WHEEL_CIRCUMFERENCE/CLICKS_PER_REVOLUTION)
#define ARRAYSIZE(a) (sizeof(a)/sizeof(a[0]))

task StartIR() {
	while(true) {
		IR = SensorValue[IRSeeker];
		nxtDisplayBigTextLine(0, "%i", IR);
	}
}

task watchdog(){
	wait10Msec(delay);
	StopAllTasks();
}

void AutoDrive(float inches, float speed){

	float clicks = (CLICKS_PER_REVOLUTION/WHEEL_CIRCUMFERENCE)*inches;
	float goal = nMotorEncoder[ML] + clicks;

	while(nMotorEncoder[ML] < goal-15 || nMotorEncoder[ML] > goal+15){

		if(nMotorEncoder[ML] > goal){
			motor[FL] = -speed;
			motor[ML] = -speed;
			motor[BL] = -speed;
			motor[FR] = -speed;
			motor[MR] = -speed;
			motor[BR] = -speed;
			{
				if(nMotorEncoder[ML] < goal){
					motor[FL] = speed;
					motor[ML] = speed;
					motor[BL] = speed;
					motor[FR] = speed;
					motor[MR] = speed;
					motor[BR] = speed;
				}

			}

		}
	}
}
