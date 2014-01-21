/*!@addtogroup HiTechnic
 * @{
 * @defgroup htgyro Gyroscopic Sensor
 * HiTechnic Gyroscopic Sensor
 * @{
 */

/*
 * $Id: HTGYRO-driver.h 36 2010-11-11 10:20:54Z xander $
 */

#ifndef __HTGYRO_H__
#define __HTGYRO_H__
/** \file HTGYRO-driver.h
 * \brief HiTechnic Gyroscopic Sensor driver
 *
 * HTGYRO-driver.h provides an API for the HiTechnic Gyroscopic Sensor.
 *
 * Changelog:
 * - 0.1: Initial release
 * - 0.2: Renamed HTGYROgetCalibration to HTGYROreadCal<br>
 *        Renamed HTGYROsetCalibration to HTGYROsetCal<br>
 *        Renamed HTGYROcalibrate to HTGYROstartCal<br>
 *        Added SMUX functions
 * - 0.3: Removed some of the functions requiring SPORT/MPORT macros
 *
 * Credits:
 * - Big thanks to HiTechnic for providing me with the hardware necessary to write and test this.
 *
 * License: You may use this code as you wish, provided you give credit where its due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 2.00 AND HIGHER.
 * \author Xander Soldaat (mightor_at_gmail.com)
 * \date 29 November 2009
 * \version 0.3
 * \example HTGYRO-test1.c
 * \example HTGYRO-SMUX-test1.c
 */

#pragma systemFile

#ifndef __COMMON_H__
#include "common.h"
#endif

int HTGYROreadRot(tSensors link);
int HTGYROreadRot(tMUXSensor muxsensor);
int HTGYROstartCal(tSensors link);
int HTGYROstartCal(tMUXSensor muxsensor);
int HTGYROreadCal(tSensors link);
int HTGYROreadCal(tMUXSensor muxsensor);
void HTGYROsetCal(tSensors link, int offset);
void HTGYROsetCal(tMUXSensor muxsensor, int offset);

int HTGYRO_offsets[][] = {{620, 620, 620, 620}, /*!< Array for offset values.  Default is 620 */
                          {620, 620, 620, 620},
                          {620, 620, 620, 620},
                          {620, 620, 620, 620}};

/**
 * Read the value of the gyro
 * @param link the HTGYRO port number
 * @return the value of the gyro
 */
int HTGYROreadRot(tSensors link) {
  // Make sure the sensor is configured as type sensorRawValue
  if (SensorType[link] != sensorRawValue) {
    SetSensorType(link, sensorRawValue);
    wait1Msec(100);
  }

  return (SensorValue[link] - HTGYRO_offsets[link][0]);
}


/**
 * Read the value of the gyro
 * @param muxsensor the SMUX sensor port number
 * @return the value of the gyro
 */
int HTGYROreadRot(tMUXSensor muxsensor) {
  return HTSMUXreadAnalogue(muxsensor) - HTGYRO_offsets[SPORT(muxsensor)][MPORT(muxsensor)];
}


/**
 * Calibrate the gyro by calculating the average offset of 5 raw readings.
 * @param link the HTGYRO port number
 * @return the new offset value for the gyro
 */
int HTGYROstartCal(tSensors link) {
  long _avgdata = 0;

  // Make sure the sensor is configured as type sensorRawValue
  if (SensorType[link] != sensorRawValue) {
    SetSensorType(link, sensorRawValue);
    wait1Msec(100);
  }

  // Take 50 readings and average them out
  for (int i = 0; i < 50; i++) {
    _avgdata += SensorValue[link];
    wait1Msec(5);
  }

  // Store new offset
  HTGYRO_offsets[link][0] = (_avgdata / 50);

  // Return new offset value
  return HTGYRO_offsets[link][0];
}


/**
 * Calibrate the gyro by calculating the average offset of 5 raw readings.
 * @param muxsensor the SMUX sensor port number
 * @return the new offset value for the gyro
 */
int HTGYROstartCal(tMUXSensor muxsensor) {
  int _avgdata = 0;

  // Take 5 readings and average them out
  for (int i = 0; i < 5; i++) {
    _avgdata += HTSMUXreadAnalogue(muxsensor);
    wait1Msec(50);
  }

  // Store new offset
  HTGYRO_offsets[SPORT(muxsensor)][MPORT(muxsensor)] = (_avgdata / 5);

  // Return new offset value
  return HTGYRO_offsets[SPORT(muxsensor)][MPORT(muxsensor)];
}


/**
 * Override the current offset for the gyro manually
 * @param link the HTGYRO port number
 * @param offset the new offset to be used
 */
void HTGYROsetCal(tSensors link, int offset) {
  HTGYRO_offsets[link][0] = offset;
}


/**
 * Override the current offset for the gyro manually
 * @param muxsensor the SMUX sensor port number
 * @param offset the new offset to be used
 */
void HTGYROsetCal(tMUXSensor muxsensor, int offset) {
  HTGYRO_offsets[SPORT(muxsensor)][MPORT(muxsensor)] = offset;
}


/**
 * Retrieve the current offset for the gyro
 * @param link the HTGYRO port number
 * @return the offset value for the gyro
 */
int HTGYROreadCal(tSensors link) {
  return HTGYRO_offsets[link][0];
}


/**
 * Retrieve the current offset for the gyro
 * @param muxsensor the SMUX sensor port number
 * @return the offset value for the gyro
 */
int HTGYROreadCal(tMUXSensor muxsensor) {
  return HTGYRO_offsets[SPORT(muxsensor)][MPORT(muxsensor)];
}


#endif // __HTGYRO_H__

/*
 * $Id: HTGYRO-driver.h 36 2010-11-11 10:20:54Z xander $
 */
/* @} */
/* @} */
