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

task watchdog() {
	wait10Msec(delay);
	StopAllTasks();
}
