/* 
 * Code to run 3 axis accelerometer NFC threshold detector
 * 
 * Written by Benjamin Jones 
 * 12/06/20
 *  
 *  Merged and edited SparkFun ADXL377 Hookup Guide
 *  (https://learn.sparkfun.com/tutorials/adxl337-and-adxl377-accelerometer-hookup-guide)
 *  and RF430CL example code from Spirilis RF430CL energia library 
 *  (https://github.com/spirilis/RF430CL)
 *  
 */

#include <NDEF.h>
#include <NDEF_TXT.h>
#include <RF430CL.h>
#include <Wire.h>

#define RF430CL330H_BOOSTERPACK_RESET_PIN  8
#define RF430CL330H_BOOSTERPACK_IRQ_PIN    12

RF430 nfc(RF430CL330H_BOOSTERPACK_RESET_PIN, RF430CL330H_BOOSTERPACK_IRQ_PIN);

const int x_axis = A0;
const int y_axis = A1;
const int z_axis = A2;

int rawX;
int rawY;
int rawZ;
int scale = 3;

float X_accel;
float Y_accel;
float Z_accel;

void setup() {
  pinMode(x_axis, INPUT);
  pinMode(y_axis, INPUT);
  pinMode(z_axis, INPUT);

  Serial.begin(115200);
  Wire.begin();
  nfc.begin();
  NDEF_TXT t("en", "Concussion risk threshold exceeded. Seek medical advice.");
  int ndef_size = t.sendTo(nfc);
  nfc.setDataLength(ndef_size);
}

void loop() {
  //Read raw accelerometer values
  rawX = analogRead(x_axis);
  rawY = analogRead(y_axis);
  rawZ = analogRead(z_axis);
  
  // Take the raw values from the accelerometer and scale them
  X_accel = mapf(rawX, 0, 1023, -scale, scale);
  Y_accel = mapf(rawY, 0, 1023, -scale, scale);
  Z_accel = mapf(rawZ, 0, 1023, -scale, scale);

  if(abs(X_accel) > 15 || abs(Y_accel) > 15 || abs(Z_accel) > 15) {
    nfc.enable();
    if (nfc.loop()) {
      if (nfc.wasRead()) {
        Serial.println("NDEF tag was read!");
      }
      if (nfc.available()) {
        Serial.print("NFC master has written a new tag! ");
        uint16_t len = nfc.getDataLength();
        Serial.print(len);
        Serial.println(" bytes");
        nfc.flush();  // prevent nfc.available() from returning true again
      }
      nfc.enable();
    }
  }
}

// Same functionality as Arduino's standard map function, except using floats
float mapf(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
