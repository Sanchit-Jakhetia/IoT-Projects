#include <L298N.h>

// Define motor control pins
#define AIN1 17  
#define BIN1 18  
#define AIN2 16  
#define BIN2 19  
#define PWMA 21  
#define PWMB 4   
#define STBY 22  

// Initialize motor control objects (swapped)
L298N motor1(PWMB, BIN1, BIN2);  // Left motor
L298N motor2(PWMA, AIN1, AIN2);  // Right motor

// Define sensor pins
int a1 = 27;  
int a2 = 26;  
int a3 = 25;  
int a4 = 33;  
int a5 = 32;  

void setup() {
  // Set motor standby pin as output and enable it
  pinMode(STBY, OUTPUT);
  digitalWrite(STBY, HIGH);

  // Set IR sensor pins as input
  pinMode(a1, INPUT);
  pinMode(a2, INPUT);
  pinMode(a3, INPUT);
  pinMode(a4, INPUT);
  pinMode(a5, INPUT);

  Serial.begin(9600);
}

void loop() {
  // Read sensor values
  int s1 = digitalRead(a1);
  int s2 = digitalRead(a2);
  int s3 = digitalRead(a3);
  int s4 = digitalRead(a4);
  int s5 = digitalRead(a5);

  // Move forward if the center sensor detects the line
  if (s3 == 1) {
    motor1.forward();
    motor2.forward();
    delay(500);  // Delay of 0.5 seconds
  }
  // Move forward if the center three sensors detect the line
  else if (s2 == 1 && s3 == 1 && s4 == 1) {
    motor1.forward();
    motor2.forward();
    delay(500);  // Delay of 0.5 seconds
  }
  // Turn right if any of the left sensors detect the line
  else if (s1 == 1 || s2 == 1) {
    motor1.stop();
    motor2.forward();
    delay(100);

    if (s1 == 1 && s2 ==1 && s3 == 1){
      motor1.stop();
      motor2.forward();
      delay(200);
    }
  }
  // Turn left if any of the right sensors detect the line
  else if (s4 == 1 || s5 == 1) {
    motor1.forward();
    motor2.stop();
    delay(100);

    if (s3 == 1 && s4 ==1 && s5 == 1){
      motor1.forward();
      motor2.stop();
      delay(200);
    }
  }

  else if (s1 == 0 && s2 == 0 && s3 == 0 && s4 == 0 && s5 == 0) {
    // Rotate 15 degrees to the right
    motor1.backward();
    motor2.backward();
    delay(300);
    
    motor1.forward();
    motor2.backward();
    delay(200);  // Adjust delay as needed for 15 degrees

    // Rotate 15 degrees to the left
    motor1.backward();
    motor2.forward();
    delay(200);  // Adjust delay as needed for 15 degrees

    // Stop the motors after the rotation
    motor1.stop();
    motor2.stop();
  }
  // Stop if no sensors detect the line
  else {
    motor1.stop();
    motor2.stop();
  }

  delay(20);
}
