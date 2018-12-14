
#define BLYNK_PRINT Serial
#include <SPI.h>
#include <Ethernet.h>
#include <BlynkSimpleEthernet.h>
#include <LiquidCrystal.h>

char auth[] = "5daa5e9d94764019ae49e72a58e78d2d";
#define W5100_CS  10
#define SDCARD_CS 4

char ch;
int Contrast=15;
// initialize the library with the numbers of the interface pins
WidgetLCD lcdVirtual(V1);
LiquidCrystal lcdReal(12, 11, 5, 4, 3, 2);
const int trigPin = 8;
const int echoPin = 7;
// defines variables
long duration;
int distance;

void setup() 
{
  Serial.begin(9600);

  pinMode(SDCARD_CS, OUTPUT);
  digitalWrite(SDCARD_CS, HIGH); // Deselect the SD card
  Blynk.begin(auth, "blynk-cloud.com", 8442);
  
  Serial.println("LCD test with PWM contrast adjustment");
  pinMode(13,OUTPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  analogWrite(6,Contrast);
  // set up the LCD's number of columns and rows: 
  // Print a message to the LCD.
  lcdReal.setCursor(0, 0);
  lcdReal.print("Distance: ");
  lcdVirtual.print(0, 0, "Distance: ");
}

void loop() 
{
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(1000);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigPin, LOW); 
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance= duration*0.034/2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);

  
   digitalWrite(13,LOW);
   delay(1000);
   digitalWrite(13,HIGH);
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcdReal.setCursor(0, 1);
  lcdReal.print(distance);
  lcdVirtual.clear();
  // print the number of seconds since reset:
  lcdVirtual.print(0, 1,distance);
  lcdVirtual.clear();
  
  Blynk.run();
}

void serialEvent()
{
     if (Serial.available())
      {
        analogWrite(6,"mew");
        Serial.println("Current contrast");
        Serial.println(Contrast);
      }
}
