/*
Code to run three axis acclerometer threshold detector

Written by Benjamin Jones
31/05/20
 
 */
const int BUTTON = 5;
const int LED = 0;
const int x_axis = 2;
const int y_axis = 3;
const int z_axis = 4;

const float t_1 = 2.0; // voltage threshold in +ve direction
const float t_2 = 1.3; // voltage threshold in -ve direction

float x = 1.65; //  value of voltage from accelerometer
float y = 1.65;
float z = 1.65;
int buttonState = 0; // variable to read whether button is pressed

float scale_x;
float scale_y;
float scale_z;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT);
  pinMode(x_axis, INPUT);
  pinMode(y_axis, INPUT);
  pinMode(z_axis, INPUT);
}

void loop() {
   x = analogRead(x_axis);
   y = analogRead(y_axis);
   z = analogRead(z_axis);

   scale_x = scale(x);
   scale_y = scale(y);
   scale_z = scale(z);

   exceed_t(x);
   exceed_t(y);
   exceed_t(z);
   
   buttonState = digitalRead(BUTTON);
   if (buttonState == HIGH) {
      digitalWrite(LED, LOW);
    }
}

float scale(float val) {
  val = val/1024*3.3;
}

void exceed_t(float val) {
  if(val > t_1 || val < t_2) {
    digitalWrite(LED, HIGH);
}
}

/*
  else if (x <= t_2) {
    digitalWrite(LED, HIGH);
    delay(50);
    digitalWrite(LED, LOW);
  }
*/
