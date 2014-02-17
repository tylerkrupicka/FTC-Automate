//each of these routines is accesed by the main autonomous program
//they should be renamed based on what they do.

//The watchdog setup is to stop the robot if the automated drive does not complete,
//which stops the motors in the event of a collision and saves motors.

//sample autonomous to drive straight ten inches
void R1() {
	delay = 300; //set a time of three seconds for watchdog
	StartTask(watchdog); //start watchdog
	AutoDrive(10,100);//drive forward (10) at power (100)
	StopTask(watchdog);//kill watchdog. if autodrive does not complete in 3 seconds watchdog will stop the robot.
}

void R2() {


}

void R3() {


}

void R4() {


}

void R5() {


}

void R6() {


}
