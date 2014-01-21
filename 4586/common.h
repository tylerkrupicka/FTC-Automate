/*!@addtogroup common
 * @{
 */

/*
 * $Id: common.h 40 2011-01-03 09:37:09Z xander $
 */

/** \file common.h
 * \brief Commonly used functions used by drivers.
 *
 * common.h provides a number of frequently used functions that are useful for writing
 * drivers.
 * License: You may use this code as you wish, provided you give credit where its due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 2.00 AND HIGHER.
 *
 * Changelog:
 * - 0.1: Initial release
 * - 0.2: Added version check to issue error when compiling with RobotC < 1.46
 * - 0.2: Added __COMMON_H_DEBUG__ to enable/disable sounds when an I2C error occurs
 * - 0.2: Removed bool waitForI2CBus(tSensors link, bool silent)
 * - 0.3: clearI2CError() added to make writeI2C more robust, I2C bus errors are now handled
 *        better.
 * - 0.4: Added HiTechnic SMUX functions
 * - 0.5: Added clip function (Tom Roach)
 * - 0.6: clearI2CBus is now conditionally compiled into the FW.  Only RobotC < 1.57 needs it.
 * - 0.7: ubyteToInt(byte byteVal) modified, works better with 1.57+
 * - 0.8: ubyte used for arrays for firmware version 770 and higher<br>
 *        added support for new colour sensor<br>
 *        added better handling for when sensor is not configured properly
 * - 0.9: added bool HTSMUXsetMode(tSensors link, byte channel, byte mode) prototype<br>
 *        added int HTSMUXreadAnalogue(tMUXSensor muxsensor)<br>
 *        added HTSMUXSensorType HTSMUXreadSensorType(tMUXSensor muxsensor)<br>
 *        added bool HTSMUXreadPort(tMUXSensor muxsensor, tByteArray &result, int numbytes, int offset)<br>
 *        added bool HTSMUXreadPort(tMUXSensor muxsensor, tByteArray &result, int numbytes)<br>
 *        added bool HTSMUXsetMode(tMUXSensor muxsensor, byte mode)<br>
 *        added bool HTSMUXsetAnalogueActive(tMUXSensor muxsensor)<br>
 *        added bool HTSMUXsetAnalogueInactive(tMUXSensor muxsensor)<br>
 *        corrected function description for HTSMUXSensorType()
 * - 0.10: Removed unnecessary read from HTSMUXsendCommand()
 * - 0.11: Added long uByteToLong(byte a1, byte a2, byte a3, byte a4);
 * - 0.12: Added HTSMUXreadPowerStatus(tSensors link)<br>
 *         Added int round(float fl)
 * - 0.13: Added motor mux types and data structs
 * - 0.14: Added check for digital sensors to prevent conflict with built-in drivers\n
 *         Changed clearI2CError to take ubyte for address, thanks Aswin
 *
 * \author Xander Soldaat (mightor_at_gmail.com)
 * \date 08 December 2010
 * \version 0.14
 */

#pragma systemFile

#ifndef __COMMON_H__
#define __COMMON_H__

#undef __COMMON_H_DEBUG__
//#define __COMMON_H_DEBUG__

/*!< define this as 0 to remove the check  */
#ifndef __COMMON_H_SENSOR_CHECK__
#define __COMMON_H_SENSOR_CHECK__ 1
#else
#warn "sensor checking disabled, I hope you know what you are doing!"
#endif

#include "firmwareVersion.h"
#if (kFirmwareVersion < 785)
#error "These drivers are only supported on RobotC version 2.0 or higher"
#endif

#define SPORT(X)  X / 4         /*!< Convert tMUXSensor to sensor port number */
#define MPORT(X)  X % 4         /*!< Convert tMUXSensor to MUX port number */

#ifndef MAX_ARR_SIZE
/**
 * Maximum buffer size for byte_array, can be overridden in your own program.
 * It's 17 bytes big because the max I2C buffer size is 16, plus 1 byte to denote
 * packet length.
 */
#define MAX_ARR_SIZE 17
#endif

#define HTSMUX_I2C_ADDR         0x10  /*!< HTSMUX I2C device address */
#define HTSMUX_COMMAND          0x20  /*!< Command register */
#define HTSMUX_STATUS           0x21  /*!< Status register */

// Registers
#define HTSMUX_MODE             0x00  /*!< Sensor mode register */
#define HTSMUX_TYPE             0x01  /*!< Sensor type register */
#define HTSMUX_I2C_COUNT        0x02  /*!< I2C byte count register */
#define HTSMUX_I2C_DADDR        0x03  /*!< I2C device address register */
#define HTSMUX_I2C_MADDR        0x04  /*!< I2C memory address register */
#define HTSMUX_CH_OFFSET        0x22  /*!< Channel register offset */
#define HTSMUX_CH_ENTRY_SIZE    0x05  /*!< Number of registers per sensor channel */

#define HTSMUX_ANALOG           0x36  /*!< Analogue upper 8 bits register */
#define HTSMUX_AN_ENTRY_SIZE    0x02  /*!< Number of registers per analogue channel */

#define HTSMUX_I2C_BUF          0x40  /*!< I2C buffer register offset */
#define HTSMUX_BF_ENTRY_SIZE    0x10  /*!< Number of registers per buffer */


// Command fields
#define HTSMUX_CMD_HALT         0x00  /*!< Halt multiplexer command */
#define HTSMUX_CMD_AUTODETECT   0x01  /*!< Start auto-detect function command */
#define HTSMUX_CMD_RUN          0x02  /*!< Start normal multiplexer operation command */

// Status
#define HTSMUX_STAT_NORMAL      0x00  /*!< Nothing going on, everything's fine */
#define HTSMUX_STAT_BATT        0x01  /*!< No battery voltage detected status */
#define HTSMUX_STAT_BUSY        0x02  /*!< Auto-dected in progress status */
#define HTSMUX_STAT_HALT        0x04  /*!< Multiplexer is halted status */
#define HTSMUX_STAT_ERROR       0x08  /*!< Command error detected status */
#define HTSMUX_STAT_NOTHING     0xFF  /*!< Status hasn't really been set yet */

// Channel modes
#define HTSMUX_CHAN_I2C         0x01  /*!< I2C channel present channel mode */
#define HTSMUX_CHAN_9V          0x02  /*!< Enable 9v supply on analogue pin channel mode */
#define HTSMUX_CHAN_DIG0_HIGH   0x04  /*!< Drive pin 0 high channel mode */
#define HTSMUX_CHAN_DIG1_HIGH   0x08  /*!< Drive pin 1 high channel mode */
#define HTSMUX_CHAN_I2C_SLOW    0x10  /*!< Set slow I2C rate channel mode */

/**
 * Array of bytes as a struct, this is a work around for RobotC's inability to pass an array to
 * a function.  The int has to be there or it won't work.
 */

typedef struct {
  ubyte arr[MAX_ARR_SIZE];
} tByteArray;


typedef struct {
  sbyte arr[MAX_ARR_SIZE];
} tsByteArray;

/**
 * Array of ints as a struct, this is a work around for RobotC's inability to pass an array to
 * a function.  The byte has to be there or it won't work.
 */
typedef struct {
  int arr[MAX_ARR_SIZE];
} tIntArray;

/*!< Sensor types as detected by SMUX */
typedef enum
{
  HTSMUXAnalogue = 0x00,
  HTSMUXLegoUS = 0x01,
  HTSMUXCompass = 0x02,
  HTSMUXColor = 0x03,
  HTSMUXAccel = 0x04,
  HTSMUXIRSeeker = 0x05,
  HTSMUXProto = 0x06,
  HTSMUXColorNew = 0x07,
  HTSMUXAngle = 0x08,
  HTSMUXIRSeekerNew = 0x09,
  HTSMUXSensorNone = 0xFF
} HTSMUXSensorType;

/*!< Sensor and SMUX port combinations */
typedef enum {
  msensor_S1_1 = 0,
  msensor_S1_2 = 1,
  msensor_S1_3 = 2,
  msensor_S1_4 = 3,
  msensor_S2_1 = 4,
  msensor_S2_2 = 5,
  msensor_S2_3 = 6,
  msensor_S2_4 = 7,
  msensor_S3_1 = 8,
  msensor_S3_2 = 9,
  msensor_S3_3 = 10,
  msensor_S3_4 = 11,
  msensor_S4_1 = 12,
  msensor_S4_2 = 13,
  msensor_S4_3 = 14,
  msensor_S4_4 = 15
} tMUXSensor;


/*!< Struct to hold MMUX info */
typedef struct {
  bool initialised;     /*!< Has the MMUX been initialised yet? */
  bool runToTarget[4];  /*!< Indicate whether or not the motor is running to a target */
  long target[4];       /*!< Target we want the motor to run to */
  byte targetUnit[4];   /*!< Type of target we're running to, could be rotation, encoder or seconds */
  bool relTarget[4];    /*!< Whether or not the target is relative to current position */
  bool brake[4];        /*!< Whether or not to use braking or floating to stop motor */
  bool pidcontrol[4];   /*!< Use constant speed or just power control */
  byte ramping[4];      /*!< Ramp the motors, can be up, down, both */
} mmuxDataT;


/*!< MUXmotor type, one for each permutation
 *
 * - mmotor_S1_1 means motor 1 connected to MMUX attached to sensor port 1
 * - mmotor_S4_2 means motor 2 connedted to MMUX attached to sensor port 4
 */
typedef enum {
  mmotor_S1_1 = 0,
  mmotor_S1_2 = 1,
  mmotor_S1_3 = 2,
  mmotor_S1_4 = 3,
  mmotor_S2_1 = 4,
  mmotor_S2_2 = 5,
  mmotor_S2_3 = 6,
  mmotor_S2_4 = 7,
  mmotor_S3_1 = 8,
  mmotor_S3_2 = 9,
  mmotor_S3_3 = 10,
  mmotor_S3_4 = 11,
  mmotor_S4_1 = 12,
  mmotor_S4_2 = 13,
  mmotor_S4_3 = 14,
  mmotor_S4_4 = 15
} tMUXmotor;

/*!< Struct to hold SMUX info */
typedef struct {
  bool initialised;             /*!< Has the MMUX been initialised yet? */
  byte status;                  /*!< SMUX status */
  HTSMUXSensorType sensor[4];   /*!< What kind of sensor is attached to this port */
} smuxDataT;

mmuxDataT mmuxData[4];  /*!< Holds all the MMUX info, one for each sensor port */
smuxDataT smuxData[4];  /*!< Holds all the MMUX info, one for each sensor port */
tByteArray HTSMUX_I2CRequest;    /*!< Array to hold I2C command data */
tByteArray HTSMUX_I2CReply;      /*!< Array to hold I2C reply data */


void clearI2CError(tSensors link, ubyte address);
bool waitForI2CBus(tSensors link);
bool writeI2C(tSensors link, tByteArray &data, int replylen);
bool readI2C(tSensors link, tByteArray &data, int replylen);
byte HTSMUXreadStatus(tSensors link);
HTSMUXSensorType HTSMUXreadSensorType(tSensors link, byte channel);
HTSMUXSensorType HTSMUXreadSensorType(tMUXSensor muxsensor);
bool HTSMUXscanPorts(tSensors link);
bool HTSMUXsendCommand(tSensors link, byte command);
bool HTSMUXreadPort(tSensors link, byte channel, tByteArray &result, int numbytes, int offset);
bool HTSMUXreadPort(tMUXSensor muxsensor, tByteArray &result, int numbytes, int offset);
bool HTSMUXreadPort(tSensors link, byte channel, tByteArray &result, int numbytes);
bool HTSMUXreadPort(tMUXSensor muxsensor, tByteArray &result, int numbytes);
bool HTSMUXsetMode(tSensors link, byte channel, byte mode);
bool HTSMUXsetMode(tMUXSensor muxsensor, byte mode);
bool HTSMUXsetAnalogueActive(tMUXSensor muxsensor);
bool HTSMUXsetAnalogueInactive(tMUXSensor muxsensor);
int HTSMUXreadAnalogue(tSensors link, byte channel);
int HTSMUXreadAnalogue(tMUXSensor muxsensor);
bool HTSMUXreadPowerStatus(tSensors link);
int min(int x1, int x2);
int max(int x1, int x2);
int ubyteToInt(byte byteVal);
long uByteToLong(byte a1, byte a2, byte a3, byte a4);


/**
 * Clear out the error state on I2C bus by sending a bunch of dummy
 * packets.
 * @param link the port number
 * @param address the I2C address we're sending to
 *//*
void clearI2CError(tSensors link, ubyte address) {
  ubyte error_array[2];
  error_array[0] = 1;           // Message size
  error_array[1] = address; // I2C Address

#ifdef __COMMON_H_DEBUG__
  eraseDisplay();
  nxtDisplayTextLine(3, "rxmit: %d", ubyteToInt(error_array[1]));
  wait1Msec(2000);
#endif // __COMMON_H_DEBUG__

/*  for (int i = 0; i < 5; i++) {
    sendI2CMsg(link, error_array[0], 0);
    wait1Msec(5);
  }
}


/**
 * Wait for the I2C bus to be ready for the next message
 * @param link the port number
 * @return true if no error occured, false if it did
 *
bool waitForI2CBus(tSensors link)
{
  //TI2CStatus i2cstatus;
  while (true)
  {
    //i2cstatus = nI2CStatus[link];
    switch (nI2CStatus[link])
    //switch(i2cstatus)
    {
    case NO_ERR:
      return true;

    case STAT_COMM_PENDING:
      break;

    case ERR_COMM_CHAN_NOT_READY:
      break;

    case ERR_COMM_BUS_ERR:
#ifdef __COMMON_H_DEBUG__
      PlaySound(soundLowBuzz);
      while (bSoundActive) {}
#endif // __COMMON_H_DEBUG__
      return false;
    }
  }
}


/**
 * Write to the I2C bus. This function will clear the bus and wait for it be ready
 * before any bytes are sent.
 * @param link the port number
 * @param data the data to be sent
 * @param replylen the number of bytes (if any) expected in reply to this command
 * @return true if no error occured, false if it did
 *
bool writeI2C(tSensors link, tByteArray &data, int replylen) {

#if __COMMON_H_SENSOR_CHECK__ == 1
  TSensorTypes type = SensorType[link];
  if ((type != sensorI2CCustom) &&
      (type != sensorI2CCustom9V) &&
      (type != sensorI2CCustomFast) &&
      (type != sensorI2CCustomFast9V) &&
      (type != sensorI2CCustomFastSkipStates9V) &&
      (type != sensorI2CCustomFastSkipStates)) {
    hogCPU();
    PlaySound(soundException);
    eraseDisplay();
    nxtDisplayCenteredTextLine(0, "3rd Party Driver");
    nxtDisplayCenteredTextLine(1, "ERROR");
    nxtDisplayCenteredTextLine(2, "You have not");
    nxtDisplayCenteredTextLine(3, "setup the sensor");
    nxtDisplayCenteredTextLine(4, "port correctly. ");
    nxtDisplayCenteredTextLine(5, "Please refer to");
    nxtDisplayCenteredTextLine(6, "one of the");
    nxtDisplayCenteredTextLine(7, "examples.");
    wait1Msec(10000);
    StopAllTasks();
  }
#endif

  if (!waitForI2CBus(link)) {
    clearI2CError(link, data.arr[1]);

    // Let's try the bus again, see if the above packets flushed it out
    // clearI2CBus(link);
    if (!waitForI2CBus(link))
      return false;
  }

  sendI2CMsg(link, data.arr[0], replylen);

  if (!waitForI2CBus(link)) {
    clearI2CError(link, data.arr[1]);
    sendI2CMsg(link, data.arr[0], replylen);
    if (!waitForI2CBus(link))
      return false;
  }
  return true;
}


/**
 * Read from the I2C bus.  This function will wait for the bus to be ready before reading
 * from it.
 * @param link the port number
 * @param data holds the data from the reply
 * @param replylen the number of bytes in the reply
 * @return true if no error occured, false if it did
 *
bool readI2C(tSensors link, tByteArray &data, int replylen) {

#if __COMMON_H_SENSOR_CHECK__ == 1
  TSensorTypes type = SensorType[link];
  if ((type != sensorI2CCustom) &&
      (type != sensorI2CCustom9V) &&
      (type != sensorI2CCustomFast) &&
      (type != sensorI2CCustomFast9V) &&
      (type != sensorI2CCustomFastSkipStates9V) &&
      (type != sensorI2CCustomFastSkipStates)) {
    hogCPU();
    PlaySound(soundException);
    eraseDisplay();
    nxtDisplayCenteredTextLine(0, "3rd Party Driver");
    nxtDisplayCenteredTextLine(1, "ERROR");
    nxtDisplayCenteredTextLine(2, "You have not");
    nxtDisplayCenteredTextLine(3, "setup the sensor");
    nxtDisplayCenteredTextLine(4, "port correctly. ");
    nxtDisplayCenteredTextLine(5, "Please refer to");
    nxtDisplayCenteredTextLine(6, "one of the");
    nxtDisplayCenteredTextLine(7, "examples.");
    wait1Msec(10000);
    StopAllTasks();
  }
#endif

  // clear the input data buffer
  memset(data, 0, sizeof(tByteArray));

  // wait for the bus to be done receiving data
  if (!waitForI2CBus(link))
    return false;

  // ask for the input to put into the data array
  readI2CReply(link, data.arr[0], replylen);

  return true;
}


/*
 * Initialise the smuxData array needed for keeping track of sensor settings
 *
void HTSMUXinit(){
  memset(smuxData, 0xFF, sizeof(smuxDataT)*4);
  for (int i = 0; i < 4; i++) {
    // memset(smuxData[i].sensor, 0xFF, sizeof(HTSMUXSensorType)*4);
    smuxData[i].status = HTSMUX_STAT_NOTHING;
    smuxData[i].initialised = true;
  }
}


/**
 * Read the status of the SMUX
 *
 * The status byte is made up of the following bits:
 *
 * | D7 | D6 | D4 | D3 | D2 | D1 | D1 |
 * -D1 - HTSMUX_STAT_BATT: No battery voltage detected
 * -D2 - HTSMUX_STAT_BUSY: Auto-dected in progress status
 * -D3 - HTSMUX_STAT_HALT: Multiplexer is halted
 * -D4 - HTSMUX_STAT_ERROR: Command error detected
 * @param link the SMUX port number
 * @return the status byte
 *
byte HTSMUXreadStatus(tSensors link) {
  memset(HTSMUX_I2CRequest, 0, sizeof(tByteArray));

  HTSMUX_I2CRequest.arr[0] = 2;               // Message size
  HTSMUX_I2CRequest.arr[1] = HTSMUX_I2C_ADDR; // I2C Address
  HTSMUX_I2CRequest.arr[2] = HTSMUX_STATUS;

  if (!writeI2C(link, HTSMUX_I2CRequest, 1))
    return -1;

  if (!readI2C(link, HTSMUX_I2CReply, 1))
    return -1;

  return HTSMUX_I2CReply.arr[0];
}


/**
 * Get the sensor type attached to specified SMUX port
 * @param link the SMUX port number
 * @param channel the SMUX channel number
 * @return the status byte
 *
HTSMUXSensorType HTSMUXreadSensorType(tSensors link, byte channel) {
  return smuxData[link].sensor[channel];
}


/**
 * Get the sensor type attached to specified SMUX port
 * @param muxsensor the SMUX sensor port number
 * @return the status byte
 *
HTSMUXSensorType HTSMUXreadSensorType(tMUXSensor muxsensor) {
  return smuxData[SPORT(muxsensor)].sensor[MPORT(muxsensor)];
}


/**
 * Set the mode of a SMUX channel.
 *
 * Mode can be one or more of the following:
 * -HTSMUX_CHAN_I2C
 * -HTSMUX_CHAN_9V
 * -HTSMUX_CHAN_DIG0_HIGH
 * -HTSMUX_CHAN_DIG1_HIGH
 * -HTSMUX_CHAN_I2C_SLOW
 * @param link the SMUX port number
 * @param channel the SMUX channel number
 * @param mode the mode to set the channel to
 * @return true if no error occured, false if it did
 *
bool HTSMUXsetMode(tSensors link, byte channel, byte mode) {
  // If we're in the middle of a scan, abort this call
  if (smuxData[link].status == HTSMUX_STAT_BUSY) {
    return false;
  } else if (smuxData[link].status != HTSMUX_STAT_HALT) {
	  // Always make sure the SMUX is in the halted state
	  if (!HTSMUXsendCommand(link, HTSMUX_CMD_HALT))
	    return false;
	  wait1Msec(50);
	}

  memset(HTSMUX_I2CRequest, 0, sizeof(tByteArray));

  HTSMUX_I2CRequest.arr[0] = 3;               // Message size
  HTSMUX_I2CRequest.arr[1] = HTSMUX_I2C_ADDR; // I2C Address
  HTSMUX_I2CRequest.arr[2] = HTSMUX_CH_OFFSET + HTSMUX_MODE + (HTSMUX_CH_ENTRY_SIZE * channel);
  HTSMUX_I2CRequest.arr[3] = mode;

  return writeI2C(link, HTSMUX_I2CRequest, 0);
}


/**
 * Set the mode of a SMUX channel.
 *
 * Mode can be one or more of the following:
 * -HTSMUX_CHAN_I2C
 * -HTSMUX_CHAN_9V
 * -HTSMUX_CHAN_DIG0_HIGH
 * -HTSMUX_CHAN_DIG1_HIGH
 * -HTSMUX_CHAN_I2C_SLOW
 * @param muxsensor the SMUX sensor port number
 * @param mode the mode to set the channel to
 * @return true if no error occured, false if it did
 *
bool HTSMUXsetMode(tMUXSensor muxsensor, byte mode) {
  return HTSMUXsetMode((tSensors)SPORT(muxsensor), MPORT(muxsensor), mode);
}


/**
 * Set the mode of an analogue channel to Active (turn the light on)
 * @param muxsensor the SMUX sensor port number
 * @return true if no error occured, false if it did
 *
bool HTSMUXsetAnalogueActive(tMUXSensor muxsensor) {
  if (smuxData[SPORT(muxsensor)].sensor[MPORT(muxsensor)] != HTSMUXAnalogue)
    return false;

  if (!HTSMUXsetMode((tSensors)SPORT(muxsensor), MPORT(muxsensor), HTSMUX_CHAN_DIG0_HIGH))
    return false;

  return HTSMUXsendCommand((tSensors)SPORT(muxsensor), HTSMUX_CMD_RUN);
}


/**
 * Set the mode of an analogue channel to Inactive (turn the light off)
 * @param muxsensor the SMUX sensor port number
 * @return true if no error occured, false if it did
 *
bool HTSMUXsetAnalogueInactive(tMUXSensor muxsensor) {
  if (smuxData[SPORT(muxsensor)].sensor[MPORT(muxsensor)] != HTSMUXAnalogue)
	  return false;

  if (!HTSMUXsetMode((tSensors)SPORT(muxsensor), MPORT(muxsensor), 0))
    return false;

  return HTSMUXsendCommand((tSensors)SPORT(muxsensor), HTSMUX_CMD_RUN);
}


/**
 * Scan the specified SMUX's channels and configure them.
 *
 * Note: this functions takes 500ms to return while the scan is
 * in progress.
 * @param link the SMUX port number
 * @return true if no error occured, false if it did
 *
bool HTSMUXscanPorts(tSensors link) {
  // If we're in the middle of a scan, abort this call
  if (smuxData[link].status == HTSMUX_STAT_BUSY) {
    return false;
  }

  // Always make sure the SMUX is in the halted state
  if (!HTSMUXsendCommand(link, HTSMUX_CMD_HALT))
    return false;
	wait1Msec(100);

  // Commence scanning the ports and allow up to 500ms to complete
  if (!HTSMUXsendCommand(link, HTSMUX_CMD_AUTODETECT))
    return false;
  wait1Msec(500);
  smuxData[link].status = HTSMUX_STAT_HALT;

  for (int i = 0; i < 4; i++) {
    memset(HTSMUX_I2CRequest, 0, sizeof(tByteArray));

    HTSMUX_I2CRequest.arr[0] = 2;                 // Message size
    HTSMUX_I2CRequest.arr[1] = HTSMUX_I2C_ADDR;   // I2C Address
    HTSMUX_I2CRequest.arr[2] = HTSMUX_CH_OFFSET + HTSMUX_TYPE + (HTSMUX_CH_ENTRY_SIZE * i);

    if (!writeI2C(link, HTSMUX_I2CRequest, 1))
      smuxData[link].sensor[i] = HTSMUXSensorNone;

    if (!readI2C(link, HTSMUX_I2CReply, 1))
      smuxData[link].sensor[i] = HTSMUXSensorNone;

    smuxData[link].sensor[i] = (tMUXSensor)ubyteToInt(HTSMUX_I2CReply.arr[0]);
  }

  // Work-around for galloping buffer problem, applies to the HTPBs only.
  for (int i = 0; i < 4; i++) {
    if (smuxData[link].sensor[i] == HTSMUXProto) {
      HTSMUX_I2CRequest.arr[0] = 3;                 // Message size
      HTSMUX_I2CRequest.arr[1] = HTSMUX_I2C_ADDR;   // I2C Address
      HTSMUX_I2CRequest.arr[2] = HTSMUX_CH_OFFSET + HTSMUX_I2C_COUNT + (HTSMUX_CH_ENTRY_SIZE * i);
      HTSMUX_I2CRequest.arr[3] = 14;
      if (!writeI2C(link, HTSMUX_I2CRequest, 0))
        smuxData[link].sensor[i] = HTSMUXSensorNone;
    }
  }
  return true;
}


/**
 * Send a command to the SMUX.
 *
 * command can be one of the following:
 * -HTSMUX_CMD_HALT
 * -HTSMUX_CMD_AUTODETECT
 * -HTSMUX_CMD_RUN
 *
 * in progress.
 * @param link the SMUX port number
 * @param command the command to be sent to the SMUX
 * @return true if no error occured, false if it did
 *
bool HTSMUXsendCommand(tSensors link, byte command) {
  memset(HTSMUX_I2CRequest, 0, sizeof(tByteArray));

  HTSMUX_I2CRequest.arr[0] = 3;               // Message size
  HTSMUX_I2CRequest.arr[1] = HTSMUX_I2C_ADDR; // I2C Address
  HTSMUX_I2CRequest.arr[2] = HTSMUX_COMMAND;
  HTSMUX_I2CRequest.arr[3] = command;

  switch(command) {
    case HTSMUX_CMD_HALT:
        smuxData[link].status = HTSMUX_STAT_HALT;
        break;
    case HTSMUX_CMD_AUTODETECT:
        smuxData[link].status = HTSMUX_STAT_BUSY;
        break;
    case HTSMUX_CMD_RUN:
        smuxData[link].status = HTSMUX_STAT_NORMAL;
        break;
  }

  return writeI2C(link, HTSMUX_I2CRequest, 0);
}


/**
 * Read the value returned by the sensor attached the SMUX. This function
 * is for I2C sensors.
 *
 * @param link the SMUX port number
 * @param channel the SMUX channel number
 * @param result array to hold values returned from SMUX
 * @param numbytes the size of the I2C reply
 * @param offset the offset used to start reading from
 * @return true if no error occured, false if it did
 *
bool HTSMUXreadPort(tSensors link, byte channel, tByteArray &result, int numbytes, int offset) {
  memset(HTSMUX_I2CRequest, 0, sizeof(tByteArray));
  if (smuxData[link].status != HTSMUX_STAT_NORMAL)
    HTSMUXsendCommand(link, HTSMUX_CMD_RUN);

  HTSMUX_I2CRequest.arr[0] = 2;                 // Message size
  HTSMUX_I2CRequest.arr[1] = HTSMUX_I2C_ADDR;   // I2C Address
  HTSMUX_I2CRequest.arr[2] = HTSMUX_I2C_BUF + (HTSMUX_BF_ENTRY_SIZE * channel) + offset;

  if (!writeI2C(link, HTSMUX_I2CRequest, numbytes))
    return false;

  if (!readI2C(link, HTSMUX_I2CReply, numbytes))
    return false;

  memcpy(result, HTSMUX_I2CReply, sizeof(tByteArray));

  return true;
}


/**
 * Read the value returned by the sensor attached the SMUX. This function
 * is for I2C sensors.
 * @param muxsensor the SMUX sensor port number
 * @param result array to hold values returned from SMUX
 * @param numbytes the size of the I2C reply
 * @param offset the offset used to start reading from
 * @return true if no error occured, false if it did
 *
bool HTSMUXreadPort(tMUXSensor muxsensor, tByteArray &result, int numbytes, int offset) {
  return HTSMUXreadPort((tSensors)SPORT(muxsensor), MPORT(muxsensor), result, numbytes, offset);
}


/**
 * Read the value returned by the sensor attached the SMUX. This function
 * is for I2C sensors.
 * @param link the SMUX port number
 * @param channel the SMUX channel number
 * @param result array to hold values returned from SMUX
 * @param numbytes the size of the I2C reply
 * @return true if no error occured, false if it did
 *
bool HTSMUXreadPort(tSensors link, byte channel, tByteArray &result, int numbytes) {
  return HTSMUXreadPort(link, channel, result, numbytes, 0);
}


/**
 * Read the value returned by the sensor attached the SMUX. This function
 * is for I2C sensors.
 * @param muxsensor the SMUX sensor port number
 * @param result array to hold values returned from SMUX
 * @param numbytes the size of the I2C reply
 * @return true if no error occured, false if it did
 *
bool HTSMUXreadPort(tMUXSensor muxsensor, tByteArray &result, int numbytes) {
  return HTSMUXreadPort((tSensors)SPORT(muxsensor), MPORT(muxsensor), result, numbytes, 0);
}


/**
 * Read the value returned by the sensor attached the SMUX. This function
 * is for analogue sensors.
 * @param link the SMUX port number
 * @param channel the SMUX channel number
 * @return the value of the sensor or -1 if an error occurred.
 *
int HTSMUXreadAnalogue(tSensors link, byte channel) {
  memset(HTSMUX_I2CRequest, 0, sizeof(tByteArray));
  if (smuxData[link].status != HTSMUX_STAT_NORMAL)
    HTSMUXsendCommand(link, HTSMUX_CMD_RUN);

  if (smuxData[link].sensor[channel] != HTSMUXAnalogue)
    return -1;

  HTSMUX_I2CRequest.arr[0] = 2;               // Message size
  HTSMUX_I2CRequest.arr[1] = HTSMUX_I2C_ADDR;   // I2C Address
  HTSMUX_I2CRequest.arr[2] = HTSMUX_ANALOG + (HTSMUX_AN_ENTRY_SIZE * channel);

  if (!writeI2C(link, HTSMUX_I2CRequest, 2))
    return -1;

  if (!readI2C(link, HTSMUX_I2CReply, 2))
    return -1;

  return (ubyteToInt(HTSMUX_I2CReply.arr[0]) * 4) + ubyteToInt(HTSMUX_I2CReply.arr[1]);
}


/**
 * Read the value returned by the sensor attached the SMUX. This function
 * is for analogue sensors.
 * @param muxsensor the SMUX sensor port number
 * @return the value of the sensor or -1 if an error occurred.
 *
int HTSMUXreadAnalogue(tMUXSensor muxsensor) {
  if (smuxData[SPORT(muxsensor)].sensor[MPORT(muxsensor)] != HTSMUXAnalogue)
    return -1;

  return HTSMUXreadAnalogue((tSensors)SPORT(muxsensor), MPORT(muxsensor));
}


/**
 * Return a string for the sensor type.
 *
 * @param muxsensor the SMUX sensor port number
 * @param sensorName the string to hold the name of the sensor.
 *
void HTSMUXsensorTypeToString(HTSMUXSensorType muxsensor, string &sensorName) {
  switch(muxsensor) {
    case HTSMUXAnalogue:    sensorName = "Analogue";      break;
    case HTSMUXLegoUS:      sensorName = "Ultra Sonic";   break;
    case HTSMUXCompass:     sensorName = "Compass";       break;
    case HTSMUXColor:       sensorName = "Colour";        break;
    case HTSMUXColorNew:    sensorName = "Colour New";    break;
    case HTSMUXAccel:       sensorName = "Accel";         break;
    case HTSMUXIRSeeker:    sensorName = "IR Seeker";     break;
    case HTSMUXProto:       sensorName = "Proto Board";   break;
    case HTSMUXIRSeekerNew: sensorName = "IR Seeker V2";  break;
    case HTSMUXSensorNone : sensorName = "No sensor";     break;
  }
}


/**
 * Check if the battery is low
 *
 * @param link the SMUX port number
 * @return true if there is a power source problem
 *
bool HTSMUXreadPowerStatus(tSensors link) {
  if ((HTSMUXreadStatus(link) & HTSMUX_STAT_BATT) == HTSMUX_STAT_BATT)
    return true;
  else
    return false;
}


/**
 * This function returns the smaller of the two numbers
 * @param x1 the first number
 * @param x2 the second number
 * @return the smaller number
 */
int min(int x1, int x2) {
  return (x1 < x2) ? x1 : x2;
}


/**
 * This function returns the bigger of the two numbers
 * @param x1 the first number
 * @param x2 the second number
 * @return the bigger number
 */
int max(int x1, int x2) {
  return (x1 > x2) ? x1 : x2;
}


/**
 * This function returns an int equivalent of an unsigned byte
 * @param byteVal the byte to be converted
 * @return the integer equivalent
 */
int ubyteToInt(byte byteVal) {
  return 0x00FF & byteVal;
}


/**
 * Returns x if it is between min and max. If outside the range,
 * it returns min or max.
 * @param x the number to clip
 * @param min the minimum value x can have
 * @param max the maximum value x can have
 * @return x if it is between min and max. If outside the range,
 * it returns min or max.
 */
int clip(int x, int min, int max) {
   if (x < min)
      return min;
   else if (x > max)
      return max;
   else
      return x;
}


/**
 * Returns a long value by assembling the bytes passed to it.
 * @param a1 bits 24-31
 * @param a2 bits 16-23
 * @param a3 bits  8-15
 * @param a4 bits  0- 7
 * @return a long value.
 */
long uByteToLong(byte a1, byte a2, byte a3, byte a4) {
  long result;
  result = ((long)a1 << 24) +
           ((long)a2 << 16) +
           ((long)a3 <<  8) +
            (long)a4;
  return result;
}


/**
 * Returns a rounded int from a float.
 * @param fl a float
 * @return the rounded int value
 */
int round(float fl) {
  return (int)(fl + 0.5);
}

#endif // __COMMON_H__

/*
 * $Id: common.h 40 2011-01-03 09:37:09Z xander $
 */
/* @} */
