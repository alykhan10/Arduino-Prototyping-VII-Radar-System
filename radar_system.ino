/*******************************************************************************************************************
 * 
 * Author:    Aly Khan Nuruddin
 * Date:      May 15, 2021
 * Purpose:   This program permits the user to ascertain the distance and angle of incidence for a foreign object 
 *            using a radar-system, by actuating the rotary motion of an ultrasonic sensor mounted on a servo-motor.
 *            
 *******************************************************************************************************************/          

#include <Servo.h>                                // Enable communication between the microcontroller and the servo motors.

Servo myServo;                                    // Define an object that actuates the rotation of the servo motor. 

int servoPin = 9;                                 // Define the Digital PWM Pin connection for the servo motor.
int groundPin = 10;                               // Define the Digital Pin connection that "returns" the output voltage.
int echoPin = 11;                                 // Define the Digital Pin connection that "produces" the ultrasonic pulses.
int trigPin = 12;                                 // Define the Digital Pin connection that "triggers" the ultrasonic pulses.
int vccPin = 13;                                  // Define the Digital Pin connection that "senses" the output voltage.

int distance;                                     // Define the length to be measured by the ultrasonic sensor.
long duration;                                    // Define the time taken to generate the ultrasonic pulses.

void setup() {
  Serial.begin(9600);                             // Initialize communication with the Serial Monitor at 9600 baud.
  
  pinMode(trigPin, OUTPUT);                       // Configure the Digital 'Trigger' Pin to be recognized as an Output.
  pinMode(echoPin, INPUT);                        // Configure the Digital 'Echo' Pin to be recognized as an Input.
  pinMode(groundPin, OUTPUT);                     // Configure the Digital 'Ground' Pin to be recognized as an Output.
  pinMode(vccPin, OUTPUT);                        // Configure the Digital 'VCC' Pin to be recognized as an Output.
  
  digitalWrite(groundPin,LOW);                    // Set the ouput voltage value at the Digital 'Ground' Pin to 0 V.
  digitalWrite(vccPin, HIGH) ;                    // Set the ouput voltage value at the Digital 'VCC' Pin to 5 V.
  
  myServo.attach(servoPin);                       // Establish a connection between the object and the servo motor.
}

void loop() {
  for (servoPosition = 0; servoPosition <= 180; servoPosition++)         // Define the condition when the servo motor rotates from 0 to 180 degrees.
  {
    myServo.write(servoPosition);                                        // Direct the servo motor to orient itself according to the defined angle.
    delay(30);                                                           // Delay the execution of the program by 30 millisecond.
    distance = calculateDistance();                                      // Assign the length to be measured by the ultrasonic sensor to the function.

    Serial.print("Position = ")                   // Define the character string for the servo motor's position in degrees (°)
    Serial.print(servoPosition);                  // Print the value of the position on the Serial Monitor.
    Serial.print("°")                             // Define the character string for the unit of the servo motor's position.
    Serial.print(",");                            // Print a 'space' on the Serial Monitor.
    Serial.print("Distance = ")                   // Define the character string for the distance measured by the ultrasonic sensor in centimeters (cm).
    Serial.print(distance);                       // Print the value of the distance on the Serial Monitor.
    Serial.print("cm")                            // Define the character string for the unit of the servo motor's position.
    Serial.print(".");                            // Print a 'space' on the Serial Monitor.
  }
  
  for (servoPosition = 0; servoPosition >= 0; servoPosition--)           // Define the condition when the servo motor rotates from 0 to 180 degrees.
  
    myServo.write(servoPosition);                                        // Direct the servo motor to orient itself according to the defined angle.
    delay(30);                                                           // Delay the execution of the program by 30 millisecond.
    distance = calculateDistance();                                      // Assign the length to be measured by the ultrasonic sensor to the function.

    Serial.print("Position = ")                   // Define the character string for the servo motor's position in degrees (°)
    Serial.print(servoPosition);                  // Print the value of the position on the Serial Monitor.
    Serial.print("°")                             // Define the character string for the unit of the servo motor's position.
    Serial.print(",");                            // Print a 'space' on the Serial Monitor.
    Serial.print("Distance = ")                   // Define the character string for the distance measured by the ultrasonic sensor in centimeters (cm).
    Serial.print(distance);                       // Print the value of the distance on the Serial Monitor.
    Serial.print("cm")                            // Define the character string for the unit of the servo motor's position.
    Serial.print(".");                            // Print a 'space' on the Serial Monitor.
  }
}

int calculateDistance(void)                       // Implement a function to calculate the distance measured by the ultrasonic sensor.
{ 
  int buffer;                                     // Define a placeholder for calculations.
  
  int constVal = 2;                               // Initialize the value of the constant for calculating the distance.
  float soundSpeed = 0.034;                       // Initialize the speed of sound in cm/µs.
   
  digitalWrite(trigPin, LOW);                     // Set the ouput voltage value at the Digital 'Trigger' Pin to 0 V.
  delayMicroseconds(2);                           // Delay the execution of the program by 2 milliseconds.
  digitalWrite(trigPin, HIGH);                    // Set the ouput voltage value at the Digital 'Trigger' Pin to 5 V.
  delayMicroseconds(10);                          // Delay the execution of the program by 10 milliseconds.
  digitalWrite(trigPin, LOW);                     // Set the ouput voltage value at the Digital 'Trigger' Pin to 0 V.

  duration = pulseIn(echoPin, HIGH);              // Read the ultrasonic pulse length "produced" at the Digital 'Echo' Pin.

  buffer = soundSpeed/constVal;                   // Compute the value of the placeholder in meters per second squared (ms^2).
  distance = duration * buffer;                   // Compute the distance measured by the ultrasonic sensor.
  
  return distance;                                // Return the distance measured by the ultrasonic sensor.
}
