/*  Created by Benjamin Jones
 *  22/05/20
 *  
 *  Developed using SparkFun ADXL377 Hookup Guide as starting point (https://learn.sparkfun.com/tutorials/adxl337-and-adxl377-accelerometer-hookup-guide/hardware-overview)
 */

int scale = 200;
int t = 40;
float scale_x;
float scale_y;
flaot scale_z;

void setup(){
  pinMode(LED_BUILTIN, OUTPUT);  // Initialize digital pin LED_BUILTIN as an output
 
}

void loop(){
  // Get raw accelerometer data for each axis
  int rawX = analogRead(A0);
  int rawY = analogRead(A1);
  int rawZ = analogRead(A2);

  // scale the raw values to the acceleration scale
  scale_x = mapf(rawX, 0, 675, -scale, scale); // 3.3/5 * 1023 =~ 675
  scale_y = mapf(rawY, 0, 675, -scale, scale);
  scale_z = mapf(rawZ, 0, 675, -scale, scale);

  // If the acceleration threshold has been exceeded turn on LED_BUILTIN
  exceed_t(scale_x);
  exceed_t(scale_y);
  exceed_t(scale_z);

  // The system can be reset using the Arduino's built in reset button
}

float mapf(double val, double in_min, double in_max, double out_min, double out_max)
{
   return (val - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void exceed_t(float val) {
  if(abs(val) > t) {
    digitalWrite(LED_BUILTIN, HIGH);
  }
}
