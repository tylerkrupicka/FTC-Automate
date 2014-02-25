#define WHEEL_CIRCUMFERENCE       (3.95*PI)  //in inches
#define CLICKS_PER_REVOLUTION     1440.0
#define DISTANCE_PER_CLICK        (WHEEL_CIRCUMFERENCE/CLICKS_PER_REVOLUTION)
#define ARRAYSIZE(a) (sizeof(a)/sizeof(a[0]))

//This task continuously updates the IR sensor, allowing you
//to access the IR variable in other functions.
task StartIR() {
	while(true) {
		IR = SensorValue[IRSeeker];
		nxtDisplayBigTextLine(0, "%i", IR);
	}
}

//Watchdog will kill all tasks operating after a certain amount of time
//when partnered with autoDrive it allows you to stop the robot if it does not
//reach its destination in time
task watchdog(){
	wait10Msec(delay);
	StopAllTasks();
}

//stops all of the motors from running once another function is complete
void Stop(){
	motor[FL] = 0;
	motor[ML] = 0;
	motor[BL] = 0;
	motor[FR] = 0;
	motor[MR] = 0;
	motor[BR] = 0;

}

//Autodrive uses an encoder to set a goal distance in inches and move the robot
void AutoDrive(float inches, float speed){

	float clicks = (CLICKS_PER_REVOLUTION/WHEEL_CIRCUMFERENCE)*inches;
	float goal = nMotorEncoder[ML] + clicks;
	bool complete = false;

	if(nMotorEncoder[ML] > goal && complete == false){
		while(nMotorEncoder[ML] > goal){ // run motors until goal is reached
			motor[FL] = -speed;
			motor[ML] = -speed;
			motor[BL] = -speed;
			motor[FR] = -speed;
			motor[MR] = -speed;
			motor[BR] = -speed;
		}
		complete = true;
	}
	if(nMotorEncoder[ML] < goal && complete == false){
		while(nMotorEncoder[ML] < goal){
			motor[FL] = speed;
			motor[ML] = speed;
			motor[BL] = speed;
			motor[FR] = speed;
			motor[MR] = speed;
			motor[BR] = speed;
		}
		complete = true;
	}
	Stop(); // uses the stop function to set motors to 0
}
