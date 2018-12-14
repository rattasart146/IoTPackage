
#include <LiquidCrystal.h>

char ch;
int Contrast=15;
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int trigPin = 8;
const int echoPin = 7;
// defines variables
long duration;
int distance;

void setup() 
{
  Serial.begin(9600);
  
  Serial.println("LCD test with PWM contrast adjustment");
  pinMode(13,OUTPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  analogWrite(6,Contrast);
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Distance: ");
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
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(distance);
  lcd.print("                ");
}
