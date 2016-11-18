/*****************************************************************************
 *
 * imu.c - for I2C based IMUs.
 * Currently written specifically for the MPU-6050; a 6DOF accel + gyro chip.
 * 
 * Author: Rahul Butani
 * Date:   11/18/16
 *
 *****************************************************************************/

#include <imu.h>

#include <stdint.h>

#include <TechnicalDifficulties/inc/shared.h>


#include <RASLib/inc/common.h>
#include <RASLib/inc/gpio.h>
#include <RASLib/inc/i2c.h>

// Struct for an IMU object (connection with an IMU chip)
typedef struct IMU
{
    // Pointer to an I2C Object
    tI2C *i2c;

    tPin SDA, SCL;

    char rawData[14];
    // char *rawDataPtr = rawData;

    int16_t data[7];

    float acc_x, acc_y, acc_z;
    float gyr_x, gyr_y, gyr_z;
    float temp;

} tIMU;


tIMU *InitializeIMUObject(tPin SDA, tPin SCL)
{
    tIMU *imu;

    imu->SDA = SDA;
    imu->SCL = SCL;

    imu->i2c = InitializeI2C(SDA, SCL);

    return imu;
}

tBoolean InitializeSensor(tIMU *imu)
{
    return true;

    //Check if sensor is properly connected:
    char test = MPU6050_WHO_AM_I, output;

    I2CRequest(
        imu->i2c,
        MPU6050_I2C_ADDR,
        &test,
        1,
        &output,
        1
        );

    Printf("Got 0x%02x", output);

    if(output != 0x68)
    {
        Printf("Error!");
        // throw_error();
        return false;
    }

    //Now wake the sensor up:
    char send[2] =  {   
                        MPU6050_PWR_MGMT_1, //Address of power management register
                        0                   //Disable sleep
                    };

    return I2CSend(
        imu->i2c,         //Pointer to initialized I2C module
        MPU6050_I2C_ADDR, //I2C Address of sensor
        send,
        2         );
}

void RawRead(tIMU *imu)
{
    char send = MPU6050_ACCEL_XOUT_H;

    I2CRequest(
        imu->i2c,
        MPU6050_I2C_ADDR,
        &send,
        1,
        imu->rawData,
        14
        );
}

void ProcessReading(tIMU *imu)
{
    for(int i = 0; i < 7; i++)
    {
        imu->data[i] = (imu->rawData[2*i] << 8) | (imu->rawData[2*i + 1]);
    }

    imu->temp = (imu->data[3]/340.00) + 35.00;

    imu->acc_x = imu->data[0];
    imu->acc_y = imu->data[1];
    imu->acc_z = imu->data[2];

    imu->gyr_x = imu->data[4];
    imu->gyr_y = imu->data[5];
    imu->gyr_z = imu->data[6];
}

void GetSensorReading(tIMU *imu)
{
    RawRead(imu);
    ProcessReading(imu);
}

void PrintReadings(tIMU *imu)
{
    Printf("Acc X, Y, Z = { %d, %d, %d }\n", imu->acc_x, imu->acc_y, imu->acc_z);
    Printf("Gyr X, Y, Z = { %d, %d, %d }\n", imu->gyr_x, imu->gyr_y, imu->gyr_z);
    Printf("Temp        = { %d         }\n", imu->temp);
}
