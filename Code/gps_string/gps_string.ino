// Strings are less loved in Arduino, due to heap fragmentation. 
// I personally only used this code as a baseline because it was easier to work with.
// Unsure why, but Strings truncate floats/longs, so they end up being useless for my purpose.

#include <TinyGPS++.h>
#include "SDHelper.h"
#include "IMU.h"
#include <stdlib.h>

#define DEBUG 1
TinyGPSPlus gps;
TinyGPSCustom speed_k(gps, "GPVTG", 7);
LSM9DS1 imu;

void setup() {
  Serial.begin(4800);
  pinMode(cardDetect, INPUT);
  pinMode(chipSelect, OUTPUT);
  initializeCard();
  initIMU(imu);
  String dataString = "UTC Time,Lat,Long,Speed,Sats,Acc X,Acc Y,Acc Z,";
  saveData(dataString);
}

void loop() {
  String dataString;
  while (Serial.available()) { gps.encode(Serial.read()); refresh_IMU(imu); }

  if (gps.location.isUpdated())
  {
    refresh_IMU(imu);
    dataString = String(gps.time.value()); dataString += ",";
    dataString += String(gps.location.lat()); dataString += ",";
    dataString += String(gps.location.lng()); dataString += ",";
    dataString += String(speed_k.value()); dataString += ",";
    dataString += String(gps.satellites.value()); dataString+= ",";
    dataString += String(imu.calcAccel(imu.ax)); dataString += ",";
    dataString += String(imu.calcAccel(imu.ay)); dataString += ",";
    dataString += String(imu.calcAccel(imu.az)); dataString += ",";
    saveData(dataString);

          #if DEBUG
          {
            Serial.print(F("Time:")); Serial.print(gps.time.value());
            Serial.print(F(", LAT:")); Serial.print(gps.location.lat(), 8);
            Serial.print(F(", LON:")); Serial.print(gps.location.lng(), 8);
            Serial.print(F(", SPD:")); Serial.print(speed_k.value());
            Serial.print(F(", SAT:")); Serial.println(gps.satellites.value());
            Serial.print(F("ACX:")); Serial.print(imu.calcAccel(imu.ax));
            Serial.print(F(", ACY:")); Serial.print(imu.calcAccel(imu.ay));
            Serial.print(F(", ACZ:")); Serial.println(imu.calcAccel(imu.az));
          }
          #endif

  }
}
