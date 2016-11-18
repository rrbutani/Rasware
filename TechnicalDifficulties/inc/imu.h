#ifndef TD_IMU   /* Include guard */
#define TD_IMU

#ifdef __cplusplus
extern "C" {
#endif

// Necessary includes:
#include <RASLib/inc/gpio.h>

// Register mappings for the MPU-6050:
#define MPU6050_PWR_MGMT_1 0x6B
#define MPU6050_ACCEL_XOUT_H 0x3B

#define MPU6050_I2C_ADDR 0x68 //MPU-6050's I2C address

#define MPU6050_WHO_AM_I 0x75


// Struct with internal IMU Object data
typedef struct IMU tIMU;

//Functions:
tIMU *InitializeIMUObject(tPin SDA, tPin SCL);
tBoolean InitializeSensor(tIMU *imu);
void RawRead(tIMU *imu);
void ProcessReading(tIMU *imu);
void GetSensorReading(tIMU *imu);
void PrintReadings(tIMU *imu);


#ifdef __cplusplus
}
#endif

#endif // TD_IMU