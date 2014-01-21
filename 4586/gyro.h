#define GYRO_SAMPLING_INTERVAL  5

#define GYRO_NUM_CAL_SAMPLES    50
#define GYRO_CAL_INTERVAL       10

tSensors    GYROsensorID;
int         GYROzeroOffset;
int         GYROdeadBand;
long        GYROtimestamp;
long        GYROnextTime;
int         GYROturnRate;
float       GYROheading;

//float prev4;
//float prev3;
//float prev2;
//float prev;

int max_raw = 600;
int min_raw = 600;

#define GyroGetRawValue()       SensorValue[GYROsensorID]
#define GyroGetTurnRate()      (GYROturnRate)

/**
 *  This function calibrates the gyro for zero offset and deadband.
 *
 *  @param numSamples Specifies the number of calibration samples.
 *  @param calInterval Specifies the calibration interval in msec.
 */
void GyroCal(int numSamples, int calInterval)  {
    int i;
    int turnRate;
    int minValue, maxValue;

    GYROzeroOffset = 0;
    GYROdeadBand = 0;
    minValue = 1023;
    maxValue = 0;

    for (i = 0; i < numSamples; i++)
    {
        turnRate = GyroGetRawValue();
        GYROzeroOffset += turnRate;

        if (turnRate < minValue)
        {
            minValue = turnRate;
        }
        else if (turnRate > maxValue)
        {
            maxValue = turnRate;
        }

        wait1Msec(calInterval);
    }

    GYROzeroOffset /= numSamples;
    GYROdeadBand = maxValue - minValue;

    return;
}   //GyroCal

/**
 *  This function performs the gyro task where it integrates the turn rate
 *  into a heading value.
 */
void
GyroTask()
{
    long currTime;

    currTime = nPgmTime;
    if (currTime >= GYROnextTime)
    {
        GYROturnRate = GyroGetRawValue();
        currTime = nPgmTime;
        if (GYROturnRate > max_raw) { max_raw = GYROturnRate; }
        if (GYROturnRate < min_raw) { min_raw = GYROturnRate; }

        GYROturnRate -= GYROzeroOffset;
        GYROturnRate = DEADBAND(GYROturnRate, GYROdeadBand);

        //the old way, standard 1st integral
        GYROheading += (float)GYROturnRate*(currTime - GYROtimestamp)/1000;

        //the new way, Runge-Kutta 4th Order
        //prev = prev + 0.16667 * (prev4 + 2*prev3 + 2*prev2 + GYROturnRate);
        //prev4 = prev3;
        //prev3 = prev2;
        //prev2 = GYROturnRate;
        //GYROheading =prev;
        //GYROheading = (float)prev*(currTime - GYROtimestamp)/1000;
        GYROtimestamp = currTime;
        GYROnextTime = currTime + GYRO_SAMPLING_INTERVAL;
    }
    return;
}   //GyroTask

/**
 *  This function resets the gyro heading.
 */
void
GyroReset()
{

    GyroTask();
    GYROheading = 0;

    return;
}   //GyroReset

/**
 *  This function initializes the gyro sensor.
 *
 *  @param sensorID Specifies the ID of the gyro sensor.
 *  @param gyroFlags Specifies the gyro flags.
 *  @param errAdj Specifies the error adjustment factor.
 */
void GyroInit(tSensors sensorID)
{

    GYROsensorID = sensorID;
    SetSensorType(sensorID, sensorAnalogInactive);
    wait1Msec(100);

    GyroCal(GYRO_NUM_CAL_SAMPLES, GYRO_CAL_INTERVAL);
    GYROtimestamp = nPgmTime;
    GYROnextTime = GYROtimestamp;
    GyroReset();

    return;
}   //GyroInit
