// ARDUINO DS18S20 DATA READER //////////////////////////

#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#include <avr/pgmspace.h>
#include <SoftwareSerial.h>
#include <DS3231.h>
#include <Adafruit_BMP280.h>
#include <AM2320.h>
#include <SD.h>

const int SD_CS = 10;
char userInput;
DS3231 Clock;
AM2320 th;
Adafruit_BMP280 bmp;

const int UV_OUT = A0;
const int UV_3V3 = A1;

const int DUST_LED_PIN = 4;
const int DUST_OUT_PIN = A2;
const int DUST_SAMPLING_TIME = 280;
const int DUST_DELTA_TIME = 40;
const int DUST_SLEEP_TIME = 9680;

SoftwareSerial esp(3, 2);
const int CH_PD_PIN = 5;

bool Century=false;


int data = 0;
//char userInput;

#define ONE_WIRE_BUS_PIN 5
OneWire oneWire(ONE_WIRE_BUS_PIN);
DallasTemperature sensors(&oneWire);

// First sensor
DeviceAddress Probe01 = { 0x28, 0xFF, 0xD5, 0xE6, 0x86, 0x16, 0x05, 0x4E }; 
// Second sensor
DeviceAddress Probe02 = { 0x28, 0xFF, 0xB7, 0xE7, 0x86, 0x16, 0x05, 0x53 }; 
// Third sensor
DeviceAddress Probe03 = { 0x28, 0xFF, 0xF9, 0xAC, 0x8C, 0x16, 0x03, 0xDB }; 


void setup()
{
    Serial.end();
    Serial.begin(115200);
   
bmp.begin();
}
float ReadUV() {
  int uvLevel = averageAnalogRead(UV_OUT);
  int refLevel = averageAnalogRead(UV_3V3);
  float outputVoltage = 3.3 / refLevel * uvLevel;
  float uvIntensity = mapfloat(outputVoltage, 0.99, 2.9, 0.0, 15.0);

  return uvIntensity;
}
int averageAnalogRead(int pinToRead){
  byte numberOfReadings = 8;
  unsigned int runningValue = 0;

  for (int x = 0 ; x < numberOfReadings ; x++)
    runningValue += analogRead(pinToRead);
  runningValue /= numberOfReadings;
  return (runningValue);
}

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max){
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
String ReadTime() {
  bool h12, PM;
  int second = 0, minute = 0, hour = 0, date = 0, month = 0, year = 0;
  //String secondStr="",minuteStr="",hourStr="",dateStr="",monthStr="";

  second = Clock.getSecond();
  minute = Clock.getMinute();
  hour = Clock.getHour(h12, PM);
  date = Clock.getDate();
  month = Clock.getMonth(Century);
  year = Clock.getYear();

  /*if(second<10)
    secondStr=secondStr+"0"+second;
    else
    secondStr+=second;
    if(minute<10)
    minuteStr=minuteStr+"0"+minute;
    else
    minuteStr+=minute;
    if(hour<10)
    hourStr=hourStr+"0"+hour;
    else
    hourStr+=hour;
    if(date<10)
    dateStr=dateStr+"0"+date;
    else
    dateStr+=date;
    if(month<10)
    monthStr=monthStr+"0"+month;
    else
    monthStr+=month;*/

  // %20 表示“空格”，用在 url 中
 //%20 denotes "space" and is used in url
String time = (String)"20" + year + "/" + month + "/" + date + "%20" + hour + ":" + minute + ":" + second;

  return time;
}
void loop()
{    
  delay(500);
    // Wait for input from the serial device.
    //if (Serial.available() > 0) {
        // Read the input coming in.
      //  userInput = Serial.read();
        // Check the input for a particular value.
      //  if (userInput == 'z') {
//float t1 = th.t;
//float t2 = th.h;
//  Serial.print(t1);
//  Serial.print(" ");
//  Serial.print(t2);
            th.Read();
            float uv = ReadUV();
            float t = th.t;
            float h = th.h;
            float p = bmp.readPressure();
//            String datetime = ReadTime();
//           Serial.print(datetime);
            Serial.print(t);
            Serial.print(" ");
            Serial.print(h);
            Serial.print(" ");
            Serial.print(p);
            Serial.print(" ");
            Serial.print(uv);
            Serial.println(" ");
        }