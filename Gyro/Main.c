#include <stdint.h>

#include <RASLib/inc/common.h>
#include <RASLib/inc/gpio.h>
#include <RASLib/inc/time.h>

#include <RASLib/inc/i2c.h>

#include <TechnicalDifficulties/inc/params.h>
#include <TechnicalDifficulties/inc/shared.h>

#define MPU6050_PWR_MGMT_1 0x6B
#define MPU6050_ACCEL_XOUT_H 0x3B

#define MPU6050_I2C_ADDR 0x68 //MPU-6050's I2C address


tI2C *i2c;

// static const tPin SDA = PIN_B3; //A7 and A6 DO NOT WORK!!!!
// static const tPin SCL = PIN_B2;

static char rawData[14]; //7 values (3 Accel, 3 Gyro, 1 Temp), 2b's per
static char *rawDataPtr = rawData;

tBoolean InitializeSensor(void)
{
  char send[2] =  { MPU6050_PWR_MGMT_1, //Address of power management register
                    0                   //Disable sleep
                  };

  return I2CSend(
    i2c,              //Pointer to initialized I2C module
    MPU6050_I2C_ADDR, //I2C Address of sensor
    send,
    2          );
}

void GetData(unsigned char *out)
{
  char send = MPU6050_ACCEL_XOUT_H;

  I2CRequest(
    i2c,
    MPU6050_I2C_ADDR,
    &send,
    1,
    out,
    14
    );
}

void PrintData(const unsigned char *raw)
{
  int16_t data[7];

  for(int i = 0; i < 7; i++)
  {
    data[i] = (raw[2*i] << 8) | (raw[2*i + 1]);
  }

  float temp = (data[3]/340.00) + 36.53;

  // Printf("Acc X, Y, Z = { %d, %d, %d }\n", data[0], data[1], data[2]);
  // Printf("Gyr X, Y, Z = { %d, %d, %d }\n", data[4], data[5], data[6]);
  // Printf("Temp        = { %d         }\n", data[3]);

  Printf("Acc X, Y, Z = { 0x%02x + 0x%02x -> %d, 0x%02x + 0x%02x -> %d, 0x%02x + 0x%02x -> %d }\n", raw[0], raw[1], data[0], raw[2], raw[3], data[1], raw[4], raw[5], data[2]);
  Printf("Gyr X, Y, Z = { 0x%02x + 0x%02x -> %d, 0x%02x + 0x%02x -> %d, 0x%02x + 0x%02x -> %d }\n", raw[6], raw[7], data[3], raw[8], raw[9], data[4], raw[10], raw[11], data[5]);
  Printf("Temp        = { 0x%02x + 0x%02x -> %f                                 }\n", raw[12], raw[13], temp);

}

int main(void)
{
  Printf("Starting...\n");

  // throw_error();

  i2c = InitializeI2C(MPU_SDA, MPU_SCL);

  Printf("Initializing Sensor...\n");
  InitializeSensor();

  Printf("Done Initializing!\n\n");

  while(true)
  {
    Printf("Grabbing New Data...\n");
    GetData(rawDataPtr);

    PrintData(rawDataPtr);

    Wait(5.0);
  }

}