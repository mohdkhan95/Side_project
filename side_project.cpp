#include <Wire.h>
#include <LiquidCrystal.h>
#include <Adafruit_INA219.h>
Adafruit_INA219 sensor219;
LiquidCrystal lcd(7, 8, 9, 10, 11, 12); //lcd pins
const int buttonPin = 2;
const int buttonPin1 = 4;
const int buttonPin2 = 3;
const int LEDOutput = 13;
int buttonPushCounter = 0;
int buttonState = 0;
int buttonState1 = 0;
int buttonState2 = 0;
int counter = 0;
//declare pins
//int relayPin0 = 13; // Relay 0
//int relayPin1 = 15; // Relay 1
//end of declare pins
void setup(void)
{
Serial.begin(250000);
sensor219.begin();
lcd.begin(16, 2);
pinMode(buttonPin, INPUT);
pinMode(buttonPin1, INPUT);
pinMode(buttonPin2, INPUT);
pinMode(LEDOutput, OUTPUT);
}
void loop(void)
{
//relay code
digitalWrite(relayPin0, HIGH); // sets the relay 0 on
delay(1000); // waits for a second
digitalWrite(relayPin1, HIGH); // sets the relay 1 on
delay(1000); // waits for a second
//end of relay code
25
buttonState = digitalRead(buttonPin);
Serial.println(buttonState);
buttonState1 = digitalRead(buttonPin1);
buttonState2 = digitalRead(buttonPin2);
if (buttonState == 1)
{
counter = counter + 5;
}
else if (buttonState1 == 1)
{
counter=counter - 5;
}
/*else if (buttonState2 == 1)
{
counter = 0;
}*/
Serial.println("Counter " + (String) counter);
float busVoltage = 0;
float current = 0; // Measure in milli amps
float power = 0;
char outstr[15];
//read sensor
busVoltage = sensor219.getBusVoltage_V(); //voltage in V
current = sensor219.getCurrent_mA(); //current in mA
power = busVoltage * (current/1000); // power in W
//end of read sensor
String msg1 = "";
String msg2 = "";
//lcd refresh
lcd.setCursor(0, 0);
lcd.print("");
lcd.setCursor(0,1);
lcd.print("");
//end of lcd refresh
//lcd 1st line
lcd.setCursor(0,0); //16x1
msg1 = "";
//dtostrf(busVoltage,4, 1, outstr); //converts the value to one value
after decimal
msg1 = (String) busVoltage;
Serial.println(busVoltage);
lcd.print("");
//lcd.print(msg1+" "+counter);
26
//end of lcd 1st line
Serial.println(counter);
//lcd 2nd line
lcd.setCursor(0, 0); //16x2
msg2 = "";
msg2 = (String) (current);
lcd.print("");
lcd.print(msg1+" "+msg2);
//end of lcd 2nd line
lcd.setCursor(0, 1);
lcd.print("");
lcd.print("C= " + (String) counter);
Serial.println("Current " + (String) current);
Serial.println("Counter " + (String) counter);
if(current>counter)
{
digitalWrite(LEDOutput, HIGH);
}
else
{
digitalWrite(LEDOutput, LOW);
}
//serial print
Serial.println(msg1);
Serial.println(msg2);
Serial.println("");
//end of serial print
delay(2000);
/*
for (int i = 256; i >= 0; i--)
{
digitalPotWrite(i);
delay(10);
}
delay(500);
*/
/*
delay(10);
digitalPotWrite(8);
delay(10);
