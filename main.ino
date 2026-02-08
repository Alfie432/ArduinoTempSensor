// started feb 7, finished feb 8

#include "DHT.h"
#include <LiquidCrystal.h>

#define DHTTYPE 11 // tell the program that this is dht11 and NOT dht22

int tempData = 12; // the temp data goes to this pin
int sensorVCC = 8;

// rs = tells if we are sending a command or char
// en = tells the lcd to look at dpins and process what happening
// d4-d7 = send a bit each, they are is 4-bit mode, so they send it twice really fast to send a byte (char)
const int rs = 10, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;  

DHT sensor(tempData, DHTTYPE); // create an instance of the class called <sensor>
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); // creates an instance of the class called <lcd>

void setup()
{
  Serial.begin(9600);
  sensor.begin();
  lcd.begin(16, 2);
  delay(1000); // let the lcd wake up

  pinMode(sensorVCC, OUTPUT);
  digitalWrite(sensorVCC, HIGH);
}

void loop()
{
  delay(2000); // wait 2s to save power

  // get info
  float temp = sensor.readTemperature();
  float humidity = sensor.readHumidity();

  // check if the input is valid
  if (isnan(temp) || isnan(humidity))
  {
    lcd.setCursor(0, 0);
    lcd.print("Error.");
    return; // break this iteration
  }

  // print the info
  lcd.setCursor(0, 0);
  lcd.print("Temp:     ");
  lcd.setCursor(6, 0);
  lcd.print(temp, 1);
  lcd.write(223);
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print("Humidity:    "); 
  lcd.setCursor(10, 1);
  lcd.print(humidity, 1);
  lcd.print("%");
}