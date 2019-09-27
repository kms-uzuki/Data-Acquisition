#ifndef IMU_H
#define IMU_H

#include <Wire.h>
#include <SparkFunLSM9DS1.h>

// SDO_XM and SDO_G are both pulled high, so our addresses are:
#define LSM9DS1_M   0x1E // Would be 0x1C if SDO_M is LOW
#define LSM9DS1_AG  0x6B // Would be 0x6A if SDO_AG is LOW

void initIMU( LSM9DS1 &imu ){
    Serial.println("Beginning IMU initialization.");
    imu.settings.device.commInterface = IMU_MODE_I2C;
    imu.settings.device.mAddress = LSM9DS1_M;
    imu.settings.device.agAddress = LSM9DS1_AG;
    if (!imu.begin())
    {
        Serial.println("Failed to communicate with LSM9DS1.");
        while (1)
            ;
    }
    Serial.println("Finished IMU init");
}

void refresh_IMU(LSM9DS1 &imu) {
    //Begin IMU data collection
    // Update the sensor values whenever new data is available
    if ( imu.accelAvailable() )
    {
        // To read from the accelerometer, first call the
        // readAccel() function. When it exits, it'll update the
        // ax, ay, and az variables with the most current data.
        imu.readAccel();
    }
}

#endif // IMU_H
