#include <Servo.h>

#define LDR1 A0
#define LDR2 A1
#define error 20

int Spoint = 90;  // Starting at the midpoint (90°) for 0° to 180° range
Servo servo;

void setup() {
  servo.attach(11);
  servo.write(Spoint);  // Start at 90°
  delay(1000);
}

void loop() {
  int ldr1 = analogRead(LDR1);
  int ldr2 = analogRead(LDR2);

  int value = abs(ldr1 - ldr2);

  if (value > error) {
    if (ldr1 > ldr2 && Spoint > 0) {
      Spoint--;  // Move toward 0° if LDR1 detects more light
    } else if (ldr1 < ldr2 && Spoint < 180) {  // Move toward 180° if LDR2 detects more light
      Spoint++;
    }
  }

  servo.write(Spoint);  // Move the servo to the updated position
  delay(80);
}
