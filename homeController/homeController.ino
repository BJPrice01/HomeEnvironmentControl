#include <Servo.h>
#include <Stepper.h>
#include "dht_nonblocking.h"

//  TESTING CONTROLS
#define TESTING 1
#define TEST_NUM 0

//      GLOBAL VARIABLES

//  Stepper
//if motor doesn't reverse direction, try switching IN2 and IN3
#define STEPPER_IN1 2
#define STEPPER_IN2 4
#define STEPPER_IN3 3
#define STEPPER_IN4 5 
#define STEPS  2038   // Number of steps per revolution
// Was having issues getting this to line up correctly
// Found this resource that cleared things up
// https://lastminuteengineers.com/28byj48-stepper-motor-arduino-tutorial/
Stepper stepper(STEPS, STEPPER_IN1, STEPPER_IN2, STEPPER_IN3, STEPPER_IN4);

//  DC Motor
#define MOTORENABLE 6
#define MOTORDIRA 7
#define MOTORDIRB 8

//  Servo
#define SERVO_PIN 9
Servo servo;

//  PhotoResistor
#define LIGHT_PIN 0// analog pin
int lightLevel;

//  ThermoResistor
#define HEAT_PIN 11
#define DHT_TYPE DHT_TYPE_11
float* temp;
float* humidity;
DHT_nonblocking dht(HEAT_PIN, DHT_TYPE);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  servo.attach(SERVOPIN);
  servo.write(90);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  //   UNIT TESTING
  if (TESTING == 1){
      
    if (TEST_NUM == 0){
      // light
      lightLevel = normalizeLightReading(analogRead(LIGHT_PIN)); //Returns a value between 0 and 1023 for the UNO
    } else if (TEST_NUM == 1){
      // temp
      if (dht.measure(temp, humidity)){
      Serial.print("The temperature is :");
      Serial.println(*temp);
     }
    } else if (TEST_NUM == 2){
      // stepper
      stepper.setSpeed(10);
      Serial.println("CounterClockwise");
      stepper.step(-3 * STEPS);
      delay(100);
      Serial.println("Clockwise");
      stepper.step(3 * STEPS);
      delay(100);
    } else if (TEST_NUM == 3){
      // servo
      servo.write(0);
      delay(500);
      servo.write(90);
      delay(500);
      servo.write(180);
      delay(500)
      servo.write(90);
      delay(500);
    } else if (TEST_NUM == 4){
      // dc motor
    }
  } else {
    //    MAIN
  }
  
   
}
//  Returns a value for the light reading between 0 (dark) and 100 (bright)
int normalizeLightReading(int value) {
  return map(value, 0, 1023, 0, 100);
}

// Returns a position for the blind to turn to based on intensity of light
int lightToBlindPos(){
  
}

// Returns the desired speed of the fan based on heat in the room
int tempToFanSpeed(float f){
  return map(f, 70, 100, 0, 255);
}

// Returns temp in farenheight
float tempConversion(int c){
  return (c*1.8) + 32;
}