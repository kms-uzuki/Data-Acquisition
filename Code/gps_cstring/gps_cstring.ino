// This code is bugged, but the GPS is more accurate when using Cstring-style arrays rather than Arduino Strings.
// Cannot use the IMU at the same time as the GPS, likely due to baudrate limitations and Cstring overhead.

#include <TinyGPS++.h>
#include "SDHelper.h"
//#include "IMU.h"
#include <stdlib.h>

#define DEBUG 1
TinyGPSPlus gps;
TinyGPSCustom speed_k(gps, "GPVTG", 7);
//LSM9DS1 imu;

void setup() {
  Serial.begin(4800);
  pinMode(cardDetect, INPUT);
  pinMode(chipSelect, OUTPUT);
  initializeCard();
//  initIMU(imu);
  char dataString[][20] = { "UTC Time,", "Lat,", "Long,", "Speed,", "Sats,",; } // "Acc X,", "Acc Y,", "Acc Z," };
  saveData(dataString);
}

void loop() {
  char _lat[13]; char _lon[13]; char _tme[10]; char _sat[4]; char dataString[][20];
//  char _ax[8]; char _ay[8]; char _az[8];
  while (Serial.available()) { gps.encode(Serial.read()); } //refresh_IMU(imu); }

  if (gps.location.isUpdated())
  {
//    refresh_IMU(imu);

    strncpy(dataString[0], dtostrf(gps.time.value(), 8, 0, _tme), 10); strcat(dataString[0], ",");
    strncpy(dataString[1], dtostrf(gps.location.lat(), 12, 7, _lat), 13); strcat(dataString[1], ",");
    strncpy(dataString[2], dtostrf(gps.location.lng(), 12, 7, _lon), 13); strcat(dataString[2], ",");
    strncpy(dataString[3], speed_k.value(), 5); strcat(dataString[3], ",");
    strncpy(dataString[4], dtostrf(gps.satellites.value(), 2, 0, _sat), 4); strcat(dataString[4], ",");
//    strncpy(dataString[5], dtostrf(imu.calcAccel(imu.ax), 6, 3, _ax), 8); strcat(dataString[5], ",");
//    strncpy(dataString[6], dtostrf(imu.calcAccel(imu.ay), 6, 3, _ax), 8); strcat(dataString[6], ",");
//    strncpy(dataString[7], dtostrf(imu.calcAccel(imu.az), 6, 3, _ax), 8); strcat(dataString[7], ",");
    saveData(dataString);

          #if DEBUG
          {
            Serial.print(F("Time:")); Serial.print(gps.time.value());
            Serial.print(F(", LAT:")); Serial.print(gps.location.lat(), 8);
            Serial.print(F(", LON:")); Serial.print(gps.location.lng(), 8);
            Serial.print(F(", SPD:")); Serial.print(speed_k.value());
            Serial.print(F(", SAT:")); Serial.println(gps.satellites.value());
//            Serial.print(F("ACX:")); Serial.print(_ax);
//            Serial.print(F(", ACY:")); Serial.print(_ay);
//            Serial.print(F(", ACZ:")); Serial.println(_az);
          }
          #endif

  }
}
