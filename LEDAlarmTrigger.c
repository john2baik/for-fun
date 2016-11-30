/*This arduino project is a candybowl alerter that uses sonar pings to detect movement and relays a signal to 
light up the LED lights when a person is within a certain distance to the object. */


#include <NewPing.h>//library for sonar 
#include <NewTone.h>//library for alarm

 
#define TRIGGER_PIN  6 //in pin6
#define ECHO_PIN     7  //in pin7
#define MAX_DISTANCE 200 //max distance in cm that sonar can detect

#define REDPIN 9 //in pin9
#define BLUEPIN 10 //in pin 10
#define GREENPIN 11 //in pin11

#define FADE .5   // speed of light color changes
boolean triggered = false; 
void flashLights(void);
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void setup() {
  //open serial moniter w/ baud - 115200 (our particular sonar sensor) baud = a unit of transmission speed equal to the number of times a signal changes state per second. For one baud is equivalent to one bit per second.
  Serial.begin(115200);//
  //connecting pins to the led lights
  pinMode(REDPIN, OUTPUT); // connects to pin9
  pinMode(BLUEPIN, OUTPUT);//connects to pin10
  pinMode(GREENPIN, OUTPUT);//connects to pin11
}

void loop() {//waits for trigger to get triggered
    if (triggered == true){//if triggered
      flashLights();      
      }
    else{
      delay(50);// Wait .5s between pings (about 2 pings/sec). 29ms should be the shortest delay between pings.
      unsigned int uS = sonar.ping(); //sends ping and returns an int measured in miliseconds
      Serial.print("Ping: ");
      unsigned int distance = uS / US_ROUNDTRIP_CM; //converts miliseconds to distance in cms
      Serial.print(distance);//logs to the Serial moniter the distance in cm
      Serial.println("cm");
      if(distance < 40){//TRIGGERED if within 40 cm of sonar
         triggered = true;
      }
}
}
void flashLights(){//function to flash different hues of lights and change lights
//changed fade speed for our own needs
   int r, g, b;
   int possible_seizure = 2000;
 
  // fade from blue to violet
  for (r = 0; r < possible_seizure; r++) {
    analogWrite(REDPIN, r);
    delay(FADE);
  }
  // fade from violet to red
  for (b = possible_seizure; b > 0; b--) {
    analogWrite(BLUEPIN, b);
    delay(FADE);
  }
  // fade from red to yellow
  for (g = 0; g < possible_seizure; g++) {
    analogWrite(GREENPIN, g);
    delay(FADE);
  }
  // fade from yellow to green
  for (r = possible_seizure; r > 0; r--) {
    analogWrite(REDPIN, r);
    delay(FADE);
  }
  // fade from green to teal
  for (b = 0; b < possible_seizure; b++) {
    analogWrite(BLUEPIN, b);
    delay(FADE);
  }
  // fade from teal to blue
  for (g = possible_seizure; g > 0; g--) {
    analogWrite(GREENPIN, g);
    delay(FADE);
  }

}
