

#define BLYNK_PRINT Serial

#include <LiquidCrystal.h>
#include <SPI.h>
#include <Ethernet.h>
#include <BlynkSimpleEthernet.h>


char auth[] = "5daa5e9d94764019ae49e72a58e78d2d";
char ch;
int Contrast=15;
// initialize the library with the numbers of the interface pins

LiquidCrystal lcdReal(12, 11, 5, 4, 3, 2);
WidgetLCD lcdVirtual(V1);

const int trigPin = 8;
const int echoPin = 7;
// defines variables
long duration;
int distance;

void setup() 
{
  Serial.begin(9600);
  
  Blynk.begin(auth, "blynk-cloud.com", 8442);
  Serial.println("LCD test with PWM contrast adjustment");
  pinMode(13,OUTPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  analogWrite(6,Contrast);
  // set up the LCD's number of columns and rows: 
  // Print a message to the LCD.

  lcdReal.begin(16, 2);
  lcdReal.setCursor(0, 0);
  lcdReal.print("Distance: ");
  
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
  Serial.print(distance);
  Serial.println(" CM");

  
  // set the cursor to column 0, line 1
  lcdReal.setCursor(0, 0);
  lcdReal.print("Distance: ");
  lcdReal.println(distance);
  lcdReal.setCursor(14, 0);
  lcdReal.print("Cm");

  lcdVirtual.print(0, 0, "Distance: ");
  lcdVirtual.print(10, 0, "    ");
  lcdVirtual.print(10, 0, distance);
  lcdVirtual.print(14, 0, "Cm");

  delay(500);
  // print the number of seconds since reset:
  Blynk.run();
  
}
