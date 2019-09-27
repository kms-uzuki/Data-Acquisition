#include "IMU.h"
#include "SDHelper.h"
#include <stdlib.h>
#define DEBUG 1

LSM9DS1 imu;
unsigned long time;
void setup() {
  Serial.begin(115200);
  pinMode(8, OUTPUT);
  initializeCard();
  initIMU(imu);
  char dataString[4][16] = { "Time,", "Acc X,", "Acc Y,", "Acc Z," };
  saveData(dataString);
  for (uint8_t i = 0; i < 10; i++)
  {
    digitalWrite(8, HIGH);
    delay(500);
    digitalWrite(8, LOW);
    delay(500);
  }
}

void loop() {
  char _ax[8]; char _ay[8]; char _az[8]; char _time[8]; char dataString[4][16];
  refresh_IMU(imu);
  
  time = millis();
  strncpy(dataString[0], dtostrf(time, 7, 0, _time), 8); strcat(dataString[0], ",");
  strncpy(dataString[1], dtostrf(imu.calcAccel(imu.ax), 6, 3, _ax), 8); strcat(dataString[1], ",");
  strncpy(dataString[2], dtostrf(imu.calcAccel(imu.ay), 6, 3, _ay), 8); strcat(dataString[2], ",");
  strncpy(dataString[3], dtostrf(imu.calcAccel(imu.az), 6, 3, _az), 8); strcat(dataString[3], ",");

  saveData(dataString);
 
  #if (DEBUG == 0)
  {
    Serial.print(F("Time:")); Serial.print(_time);
    Serial.print(F(", ACX:")); Serial.print(_ax);
    Serial.print(F(", ACY:")); Serial.print(_ay);
    Serial.print(F(", ACZ:")); Serial.println(_az);
  }
  #endif
}
