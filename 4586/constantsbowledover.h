//DRIVE SYSTEM
//maximum and minimum motor power capability in teleoperated mode
//scale this down to reduce the maximum speed of the robot
//our drive functions scale all motor outputs to fit within this range
#define MOTOR_MIN_VALUE           -100
#define MOTOR_MAX_VALUE           100
//same as above, but for autonomous mode
#define MOTOR_MIN_VALUE_AUTO      -100
#define MOTOR_MAX_VALUE_AUTO      100
//multiply the motor output by this amount to provide "fine control", or low speed mode
//this is essentially a percentage of MOTOR_MIN_VALUE and MOTOR_MAX_VALUE, so if
//MOTOR_MAX_VALUE is set to 50% and this is set to .25, then maximum power output in
//fine control mode would be 50% * 25% = 12.5% of full mtor power
#define FINE_CONTROL_MODIFIER     .35
#define MEDIUM_CONTROL_MODIFIER     .7
//KP is our arbitrary constant for proportional motor control - look up PID control algorithms to understand this
#define DRIVE_KP                  .03
#define DRIVE_KI                  0
#define DRIVE_KD                  0
//#define WHEEL_RATIO               .75

/*
Set I and D values to zero
Increase P until output of loop oscillates
Set P to half the gain obtained in the previous step. P is now set for a quarter amplitude decay response type
Increase I until steady state offset is correct. Too much will make the system unstable
Increase D to get a faster settling time for the system.
*/

#define TAIL_UP                 245
#define TAIL_MID                155
#define TAIL_DOWN               105
//Our drive tolerance is the number of encoder ticks +/- our target encoder position that we must reach to
//be considered to be at our target, this is basically our allowable encoder error.
//Multiply this by DISTANCE_PER_CLICK to understand how big this range is in inches (hint: 10 clicks is TINY, ie. VERY PRECISE)
#define DRIVE_TOLERANCE           30
#define WHEEL_CIRCUMFERENCE       (3.95*PI)  //in inches
#define CLICKS_PER_REVOLUTION     1440.0
#define DISTANCE_PER_CLICK        (WHEEL_CIRCUMFERENCE/CLICKS_PER_REVOLUTION)

//tolerance for gyro turns, turns are considered complete when +/- this many degrees from target
//this is essentially our allowable turning error.
#define GYRO_TOLERANCE            5

//////////MACROS AND UTILITY FUNCTIONS////////
//////////////////////////////////////////////
//ARRAYSIZE gets the size of an array.
#define ARRAYSIZE(a) (sizeof(a)/sizeof(a[0]))

//NORMALIZE rescales the value of the given inputn.
//Input range for n is between sl and sh
//The output of the function will be n, rescaled to the range tl to th
//This is useful for changing joystick inputs, which are received in the range -127 to +128
#define NORMALIZE(n,sl,sh,tl,th)  (int)(((long)(n) - (sl))*((th) - (tl))/((sh) - (sl)) + (tl))

//NORMALIZE_DRIVE is a shortcut version of normalize that uses the default motor output values
//this is the easiest way to convert a joystick input to a desired motor output.
#define NORMALIZE_DRIVE(x,m,n)    NORMALIZE(x, m, n, MOTOR_MIN_VALUE, MOTOR_MAX_VALUE)

//DEADBAND tests to see if a number (n) is less than a specified range (t).
//It's basicallythe opposite of BOUND.  If the absolute value of n is less than t, return 0.  Otherwise return n.
#define DEADBAND(n,t)             ((abs(n) > (t))? (n): 0)

//This is a shortcut version of DEADBAND that uses the constant that we set up above.
#define DEADBAND_INPUT(n)         DEADBAND(n, DEADBAND_INPUT_THRESHOLD)

//the joystick deadband, joystick inputs smaller than +/- this are ignored
#define DEADBAND_INPUT_THRESHOLD  10


//global variables
//int   btnLastState[11];
//int   btn2LastState[11];
//counter fro button states
//int i;
//int   btnLastState2[11];
bool  fineDriveMode = false;
bool  mediumDriveMode = false;
bool 	armTaskRunning = false;
bool 	jointTaskRunning = false;
bool steven= false;
//bool  ballGrabberOn = true;
//bool  legomotorUp = true;

string autoRoutines[] =  { "StraightMiddleLeft", "StraightMiddleRight", "SideStraightRight", "IRRoutine", "OpHangLeft", "OpHangRight", "Blocking", "SideStraightLeft"};
int   selectedAutoRoutine = -1;

string delayTimes[] =  { "0","5","10","15","20"};
int   selectedDelayTime = -1;

int   btnLastState[11];
int   btn2LastState[11];
