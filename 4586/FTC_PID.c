#ifndef FTC_PID_h
#define FTC_PID_h

typedef struct
{
	long target;
	long current;

	float Kp;
	float Ki;
 	float Kd;

	long previousError;
	long errorSum;
  long maxIncrement;

  float d;

	bool enabled;

	long acceptedRange;
	long maxOutput;
	long output;

	int error;

	long lastDUpdate;
	bool isFirstCycle;
} PID;

void initPID(PID &pid, float Kp = 0, float Ki = 0, float Kd = 0)
{
	pid.target = 0;
	pid.current = 0;

	pid.Kp = Kp;
	pid.Ki = Ki;
	pid.Kd = Kd;

	pid.previousError = 0;
	pid.errorSum = 0;
  pid.maxIncrement = 1;
  pid.d = 0;

	pid.enabled = true;
  pid.error = 0;

	pid.acceptedRange = 5;
	pid.maxOutput = 100;
	pid.output = 0;
  pid.lastDUpdate = time1[T1];
	pid.isFirstCycle = true;
}

int calcPID(PID &pid, int input)
{
  pid.current = input;
  // P
  float error = pid.target - pid.current;

  // I
  if ( error >= pid.acceptedRange )
  {
    if ( pid.errorSum < 0 )
      pid.errorSum = 0;

    if ( error < pid.maxIncrement )
      pid.errorSum += error;
    else
      pid.errorSum += pid.maxIncrement;
  }
  else if ( error <= pid.acceptedRange )
  {
    if ( pid.errorSum > 0 )
      pid.errorSum = 0;

    if ( error > -pid.maxIncrement )
      pid.errorSum += error;
    else
      pid.errorSum -= pid.maxIncrement;
  }
  else
    pid.errorSum = 0;

	// D - update every 20ms
  if ( (pid.lastDUpdate+20) < time1[T1] && !pid.isFirstCycle )
  {
	  pid.d = error-pid.previousError;
    pid.previousError = error;
    pid.lastDUpdate = time1[T1];
  }

	pid.output = (int)((pid.Kp*error) + (pid.Ki*pid.errorSum) + (int)(pid.Kd*pid.d));
  pid.isFirstCycle = false;
  pid.error = error;
 // pid.output = ( abs(pid.output) > pid.maxOutput ? 0 : pid.output );
	return (pid.enabled ? pid.output : 0);
}

void setPIDConstants(float Kp, float Ki, float Kd, PID &pid)
{
	pid.Kp = Kp;
	pid.Ki = Ki;
	pid.Kd = Kd;
}

bool atPIDTarget(PID &pid)
{
	return (abs(pid.error) <= pid.acceptedRange);
}

void setPIDTarget(PID &pid, int target)
{
  pid.target = target;
  pid.errorSum = 0;
  pid.d = 0;
  pid.previousError = 0;
  pid.error = 0;
}

#endif
